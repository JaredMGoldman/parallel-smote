#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 284807
#define M 31
#define RAND_MAX = 1;

int parseCSV(float** array, int* minorities,char* filename) {

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
  int minInd = 0;
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
          minorities[minInd] = n_idx;
          minInd ++;
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
  return minInd;

}


int main(){

   // Generate array of data with minority element indicies stored in minorities
   float** arr = malloc(sizeof(float*) * N);
   int* minorities = malloc(sizeof(int) * 142404);
   int idx;
   for (idx = 0; idx < N; ++idx) {
     arr[idx] = malloc(sizeof(float) * M);
   }
   total_min = parseCSV(arr, minorities, "creditcard.csv");
   
   float** dist_arr = malloc(sizeof(float*) * total_min);
   int i;
   int j;
   int k;
   idx_0;
   idx_1;
   
   //  Calculate distance between all minority elements

   for (i = 0; i < total_min; i++;){
      idx_0 = minorities[i];
      for(j = 0; j < total_min - i && j != i; j++;){
         idx_1 = minorities[j];
         int dist = 0;
         for(k = 0; k < 31; k ++){
            dist = dist +  pow(arr[idx_0][k] - arr[idx_1][k], 2);
         } 
         dist = sqrt(dist);
         dist_arr[i][j] = dist;
         dist_arr[j][i] = dist;
         }
      }
   }

   // generate new values between existing 
   float** newVals = malloc(sizeof(float*) * (ceil(N/2)-total_min));
   double ratio = ceil(N/total_min);
   for(i = 0; i < total_min); i ++){
      idx_0 = minorities[i];
      for(j = 0; j < ratio + 1 - i && j != i; j ++;){
         idx_1 = minorities[j];
         float rand_seed0 = rand();
         float rand_seed1 = rand();
         dist = dist_arr[i][j];
         for(k = 0; k < 31; k ++;){
            newVals[i][k] = arr[idx_0][k] + rand_seed0 * dist;
            newVals[ceil(N/2)-total_min-i-1][k] = arr[idx_1][k] + rand_seed1 * dist;
         }
       }
    }

   return 0;

   /* TODO: four functions:                                                                           */ 
   /*    1) parse csv into array format - Mahler                                                      */
   /*    2) implement smote algorithm sequentially - Jared                                            */
   /*    3) implement algorithm in parallel - both                                                    */
   /*    4) compare performance  - both                                                               */
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










