#include "lzw.h"
using namespace std;

int main(int arsc, char *arsv[])
{
// prepare from cmd
     string input(arsv[2]);
     string outputPath(arsv[3]);

     int info;

      {
          char key1[] = "-i";
          char key2[] = "-d";
          char key3[] = "-ind";
          if (strcmp(arsv[1],key1)==0) info = 0;
          else if (strcmp(arsv[4],key2)==0) info = 1;
          else if (strcmp(arsv[4],key3)==0) info = 2;
          else {
               cout << "Info false!!";
              return 0;
          }
     }

     int act;

     {
          char key1[] = "-e";
          char key2[] = "-d";
          if (strcmp(arsv[1],key1)==0) act = 1;
          else if (strcmp(arsv[1],key2)==0) act = 2;
          else {
               cout << "Action false!!";
               return 0;
          }
     }

//---------------------------------------------------

     //int info = 2;
     //int act = 2;
//----------------------------------------------------
     if (act==1){
         // string input("test.txt");
          //string outputPath("Compressed.lzw");
          encode(input,outputPath,info);
     }
     if (act==2){
          //string outputPath("test1.txt");
          //string input("Compressed.lzw");
          decode(input,outputPath,info);
     }

}
//a.exe -e "D:\c++ source\codeblock\LZW COMPRESSION\test.txt" "D:\c++ source\codeblock\LZW COMPRESSION\Compress.lzw" -d
//a.exe -d "D:\c++ source\codeblock\LZW COMPRESSION\Compress.lzw" "D:\c++ source\codeblock\LZW COMPRESSION\test1.txt" -d
