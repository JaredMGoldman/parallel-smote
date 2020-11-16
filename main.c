#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ratio 30.0F  // (number of majority elements / number of minority elements)

float rand_unif(){
  // generate a random float between 0 and 1
  float rand_int = (float) rand();
  float new_max = (float) RAND_MAX;
  float rand_float = rand_int / new_max;
  return rand_float;
}

void generateData(float** data, int N, int M){
  // create a dataset of minority elements to be used later
  int i,j;
  for(i = 0; i < N; i ++){
    for(j = 0; j < M-1; j ++){
      data[i][j] = rand_unif() * (1.0F + (float)j);
    }
    data[i][M-1] = 1.0F;
  }
}

int seqSMOTE(float** data, int N, int M){
  int total_new = (int) ((ratio - 1.0F) * (float) N) ;
  printf("\n--------------------------\nFor sequential SMOTE with:\nN = %d, M = %d, ratio = %4.2f\nThere are %d FLOPS.\n--------------------------\n\n", N, M, ratio, total_new + N*N);
  int i, j, k, idx;
  // initialize array to store the distane values for each pair of points 
   float** dist_arr = malloc(sizeof(float*) * N);
   for (idx = 0; idx < N; ++idx) {
     dist_arr[idx] = malloc(sizeof(float*) * N);
   }

   //  Calculate distance between all minority elements
   float dist, delta;
   for (i = 0; i < N; i++){
      for(j = i; j < N; j++){
         dist = 0;
         for(k = 0; k < M; k++){
            delta = pow(data[i][k] - data[j][k], 2);
            dist = dist +  delta;
         } 
         dist = sqrt(dist);
         dist_arr[i][j] = dist;
         dist_arr[j][i] = dist;
         }
      }

   printf("Calculated the distances...\n");
   // initialize array to house synthetic values 
   float** newVals = malloc(sizeof(float*) * total_new);
   for(idx = 0; idx < total_new; ++idx) {
     newVals[idx] = malloc(sizeof(float*) * M);
   }

   printf("Started smote...\n");
   // generate synthetic values and store in newVals. Store as csv upon completion.
   float rand_seed0, rand_seed1, val; 
   idx = 0;
   while(idx < total_new){
      for(i = 0; i < N; i++){
          for(j = i+1;idx < total_new && j < N; j++){
            rand_seed0 = rand_unif();
            dist = dist_arr[i][j];
            for(k = 0; k < M; k++){
                val = data[i][k] + rand_seed0 * dist;
                newVals[idx][k] = val;
            }
            idx ++;
            if(idx < total_new){
                rand_seed1 = rand_unif();
                for(k = 0; k < M; k++){
                  newVals[idx][k] = data[j][k] + rand_seed1 * dist;
                }
                idx ++;
            } 
            else {
                //writeCSV(newVals, total_new, M, "super-synth-smote.csv"); //store in csv
                printf("We made it!\n");
                return 0;}
          }
      }
   }
   printf("We made it!\n");
   return 0;
}

int main(){
   // create an array for generated minority data to be stored in 
   int N, i, j, k;
   int M = 10;
   for(N = 1000; N < 150000; N = N * 10){
     float** data = malloc(sizeof(float*) * N);
     for(i = 0; i < N; ++i){
       data[i] = malloc(sizeof(float) * M);
     }
     generateData(data, N, M);
     printf("Generated the data...\n");
   
     int rc = seqSMOTE(data, N, M);
   } 
}