#include <bits/stdc++.h>

using namespace std;

struct Node{
     int key=-1;
     vector <Node*> Next_ascii;
};

Node* create_node(int data){
     Node*p = new Node;
     p->key = data;
     for (int i=0; i<257; i++)
          p->Next_ascii.push_back(nullptr);
     return p;
}

int Insert_savetree(Node*&root, string &st,int vt,int sizedict){
     if (st.length()==vt) return -1;
     if (root->Next_ascii[(int) st[vt]] == nullptr){
          root->Next_ascii[(int) st[vt]] = create_node(sizedict);
          return root->key;
     }
     else{
          return Insert_savetree(root->Next_ascii[(int) st[vt]],st,vt+1,sizedict);
     }
}

int file_size(string st){
    ifstream mySource;
    mySource.open(st, ios_base::binary);
    mySource.seekg(0,ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    return size;
}

void outputinfo(int info,vector<string> dict,string sinput,string soutputPath){
     if (info==0 || info == 2){
          int size_test = file_size(sinput);
          int size_outputPath = file_size(soutputPath);
          cout << "Input size: " << size_test << " bits\n";
          cout << "Output size: " << size_outputPath << " bits\n";
          cout << "Space saved: " << 100 - (double)size_outputPath/size_test*100 << '\n';
     }

     if (info==1 || info == 2)
          for (int i=0; i<dict.size(); i++)
               cout << dict[i] << ": " << i+256 << '\n';
}

void saveSettings(ofstream &outputPath, uint16_t last){
    char* block;
    block = reinterpret_cast<char*>(&last);
    outputPath.write(block, sizeof(uint16_t));
}

void encode(string &sinput,string &soutputPath,int info){
     ifstream input(sinput);
     ofstream outputPath(soutputPath,ios::binary|ios::out);

     vector<string> dict;

     Node* root = create_node(-1);
      for (int i=0; i<256; i++)
          root->Next_ascii[i] = create_node(i);

     char x;
     string st="";
     int last =-1;
     while (input.get(x)){
          st = st + x; // add characters to string
          if (st.length() > 1)
               last = Insert_savetree(root, st,0,dict.size() + 256); //last = -1 (this string already in dict)
                                                                     // last != 1 (this string not in dict).
          if (last != -1){                                           // last is the number of last string in dict
               if (st.length() > 1)
                    dict.push_back(st);
               st = st[st.length()-1];
               //outputPath << last << " ";
               uint16_t c = last;
               saveSettings(outputPath,c);
              // cout << last << '\n';
          }
     }
     //outputPath << (int) x;
     uint16_t c = (int) x;
     saveSettings(outputPath,c);
     //cout << c << '\n';
     //outputPath.write((char*)&x,2);
     outputPath.close();
     input.close();
     outputinfo(info,dict,sinput,soutputPath);
}

int loadSettings(ifstream &input){
     uint16_t n;
     if (!input.read(reinterpret_cast<char *>(&n), sizeof(uint16_t)))
          return -1;
     return n;
}

void decode(string &sinput,string &soutputPath,int info){
     ifstream input(sinput,ios::binary);
     ofstream outputPath(soutputPath);

     vector<string> dict;
     Node* root = create_node(-1);
     for (int i=0; i<256; i++)
          root->Next_ascii[i] = create_node(i);
     string st = "";
     int k=-1;
     while (true){
          k=loadSettings(input); if (k==-1) break;

          if (k<256){
               st = st + (char)k;
          }
          else if (dict.size()-1 < k-256){
               st = st + st[0];
          }
          else{
               st = st + dict[k-256][0];
          }

          if (st.length() > 1)
          {
               Insert_savetree(root,st,0,dict.size());
               dict.push_back(st);
          }

          if (k<256) st = (char)k;
          else st = dict[k-256];
          if (k<256) outputPath << (char)k;
          else outputPath << dict[k-256];
     }
     input.close();
     outputPath.close();
     outputinfo(info,dict,sinput,soutputPath);
}

