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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 284807
#define M 31
#define ratio 0.2F

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
        if (strcmp(token,"\"1\"") < 0) {
          val = 0;
        } else {
          val = 1;
          minorities[minInd] = n_idx;
          minInd++;
        }
      } else {
        val = atof(token);
        if(m_idx == 0){ 
          val = val/172792.0F;
        }
      }
      array[n_idx][m_idx] = val;
      m_idx++;
      token = strtok(NULL, ",");
    }
    n_idx++;
  }
  fclose(fptr);
  return minInd;

}

int writeCSV(float** array, int rows, int cols, char* filename) {

  FILE* fptr;
  fptr = fopen(filename, "w");
  if (fptr == NULL) {
    printf("Error\n");
    exit(1);
  }
  int i,j;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      char buffer[128];
      int ret = snprintf(buffer, sizeof buffer, "%f", array[i][j]);
      if (ret < 0) {
        printf("Error\n");
        exit(1);
      }
      if (ret >= sizeof buffer) {
        printf("%f",array[i][j]);
        exit(1);
      }
      fputs(buffer,fptr);
      if (j == cols - 1) {
        fputs("\n",fptr);
      } else {
        fputs(",",fptr);
      }
    }
  }
  fclose(fptr);
  return 0;

}

float r2()
{
  float rand_int = (float) rand();
  float new_max = (float) RAND_MAX;
  float rand_float = rand_int / new_max;
  return rand_float;
}

void generateData(float** data){
  float ub_f = (1.0F-ratio) * (float) N;
  int ub = (int) ub_f;

  int i,j;
  for(i = 0; i < ub; i ++){
    for(j = 0; j < M-1; j ++){
      data[i][j] = r2();
    }
    data[i][M-1] = 0.0F;
  }
  for(i = ub; i < N; i ++){
    for(j = 0; j < M-1; j ++){
      data[i][j] = r2() * (1.0F + (float)j);
    }
    data[i][M-1] = 1.0F;
  }
}

void loadDataFromCSV(){
   int idx;
   float** arr = malloc(sizeof(float*) * N);
   int* minorities = malloc(sizeof(int) * 142404);
   
   for (idx = 0; idx < N; ++idx) {
    arr[idx] = malloc(sizeof(float) * M);
   }
   int total_min = parseCSV(arr, minorities, "creditcard.csv");

}

int main(){

  // create an array for generated data to be stored in 
  float** data = malloc(sizeof(float*) * N);
  int i, j, idx, total_min;
  for(i = 0; i < N; ++i){
    data[i] = malloc(sizeof(float) * M);
  }
   
   // Generate array of data with minority element indicies stored in minorities
   
   int dist_size = total_min*total_min;
   float** dist_arr = malloc(sizeof(float*) * dist_size);
   for (idx = 0; idx < dist_size; ++idx) {
     dist_arr[idx] = malloc(sizeof(float*));
   }
   int i;
   int j;
   int k;
   int idx_0;
   int idx_1;
   float dist;
   float delta;
   
   //  Calculate distance between all minority elements
  
   for (i = 0; i < total_min; i++){
      idx_0 = minorities[i];
      for(j = i; j < total_min; j++){
         idx_1 = minorities[j];
         dist = 0;
         for(k = 0; k < 31; k++){
            delta = pow(arr[idx_0][k] - arr[idx_1][k], 2);
            dist = dist +  delta;
         } 
         dist = sqrt(dist);
         dist_arr[i][j] = dist;
         dist_arr[j][i] = dist;
         }
      }
   // generate new values between existing 
   int total_new = (int) ceil(N/2)-total_min ;
   float** newVals = malloc(sizeof(float*) * total_new);
   for(idx = 0; idx < total_new; ++idx) {
     newVals[idx] = malloc(sizeof(float*) * M);
   }
   
   float rand_seed0, rand_seed1, val; 
   idx = 0;
   while(idx < total_new){
      for(i = 0; i < total_min; i++){
          idx_0 = minorities[i];
          for(j = i+1;idx < total_new && j < total_min; j++){
            idx_1 = minorities[j];
            rand_seed0 = r2();
            rand_seed1 = r2();
            dist = dist_arr[i][j];
            for(k = 0; k < 30; k++){
                if(k == 0){val = arr[idx_0][0]*172792.0F + rand_seed0 * dist;}
                else {val = arr[idx_0][k] + rand_seed0 * dist;}
                newVals[idx][k] = val;
            }
            newVals[idx][30] = 1;
            idx ++;
            if(idx < total_new){
                for(k = 0; k < 30; k++){
                  newVals[idx][k] = arr[idx_1][k] + rand_seed1 * dist;
                }
                newVals[idx][30] = 1;
                idx ++;
            } 
            else {
              writeCSV(newVals, total_new, M, "smote.csv");
              return 0;}
          }
      }
   }
   return 0;
}