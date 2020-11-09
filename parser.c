#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 284807
#define M 31

/* struct sample {
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
}   */


void parseCSV(float** array, char* filename) {

  //create buffer, counter
  //while file hasnextline
  //read line into buffer
  //parse line by comma
  //populate that line of the array with parsed line
  //increment counter


  int n_idx, m_idx;
  FILE *fptr;
  fptr = fopen(filename,"r");
  if (fptr == NULL) {
    printf("Error\n");
    exit(1);
  }

  int bufferSize = 1000;
  char buffer[bufferSize];
  n_idx = 0;
  fgets(buffer, sizeof(buffer), fptr); // clear header line
  while (fgets(buffer, sizeof(buffer), fptr)) {
    m_idx=0;
    char* token = strtok(buffer, ",");
    while (token != NULL) {
      float val;
      if (m_idx == 30) {
        if (strcmp(token,"0")) {
          val = 0;
        } else {
          val = 1;
        }
      } else {
        val = atof(token);
      }
      //printf("Attempting to populate array[%d][%d] with %f\n",n_idx,m_idx,val);
      array[n_idx][m_idx] = val;
      //printf("Populated array[%d][%d]\n",n_idx,m_idx);
      m_idx++;
      token = strtok(NULL, ",");
    }
    n_idx++;
    //printf("%d\n",n_idx);
  }

  fclose(fptr);

}


int main(){
   //sample[284807] data; 
 /*  char* list = ["time", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9", "V10", "V11", "V12", "V13", "V14", "V15", "V16", "V17", "V18", "V19", "V20", "V21", "V22", "V23", "V24", "V25", "V26", "V27", "V28", "amount", "class"]; */

   float** arr = malloc(sizeof(float*) * N);
   int idx;
   for (idx = 0; idx < N; ++idx) {
     arr[idx] = malloc(sizeof(float) * M);
   }
   parseCSV(arr,"creditcard.csv");
   return 0;
   //FILE* stream = fopen("creditcard.csv", "r");
   
   //int i;
   //for(i = 0;i < 284807; i ++){ 
   //   char[1000] line;
   //   fgets(line, 1000, stream);
   //};
   /* TODO: four functions:                                                                                          */ 
   /*    1) parse csv into array format - Mahler                                                              */
   /*    2) implement smote algorithm sequentially - Jared                                                    */
   /*    3) implement algorithm in parallel - both                                                          */
   /*    4) compare performance  - both                                                                     */
   /*       - use smaller subsets of total data to determine relative improvement                     */
   /*                                                                                                 */
   /* OPTIONAL:                                                                                       */
   /*    1) implement machine learning model on un-'smote'd and 'smote'd data to demonstrate utility  */
 

   /* Assuming that we have parsed all of the data already... */
   
      /* here begins sequential SMOTE */
     
         /* identify minority classes (sample.class == 1) */

         /* calculate the euclidean distance (sqrt(dx_0^2 + ... + dx_n^2)) between each element in minority class where n is total minority class elements */

         /* randomly select N elements for each x_minority from their set of neighbors where (N  = n_majority/n_minority) */
            /* create N new samples for each minority element using the formula : (x_new = x_old + rand(0,1)*|x_old - x_rand|) */  
   };










