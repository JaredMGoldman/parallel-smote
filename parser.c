#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sample {
   int time;
   float V1;
   float V2;
   float V3;
   float V4;
   float V5;
   float V6;
   float V7;
   float V8;
   float V9;
   float V10;
   float V11;
   float V12;
   float V13;
   float V14;
   float V15;
   float V16;
   float V17;
   float V18;
   float V19;
   float V20;
   float V21;
   float V22;
   float V23;
   float V24;
   float V25;
   float V26;
   float V27;
   float V28;
   float amount;
   int class;
}   

int main(){
   sample[284807] data; 
   char* list = ["time", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9", "V10", "V11", "V12", "V13", "V14", "V15", "V16", "V17", "V18", "V19", "V20", "V21", "V22", "V23", "V24", "V25", "V26", "V27", "V28", "amount", "class"]; 
   FILE* stream = fopen("creditcard.csv", "r");
   
   int i;
   for(i = 0;i < 284807; i ++){ 
      char[1000] line;
      fgets(line, 1000, stream);
   # TODO: 
   #    1) parse csv into struct format
   #    2) implement smote algorithm sequentially
   #    3) implement algorithm in parallel
   #    4) compare performance
   # 
   # OPTIONAL:
   #    1) Implement machine learning model on un-'smote'd and 'smote'd data to demonstrate utility
      
   };










