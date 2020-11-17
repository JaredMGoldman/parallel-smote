#include <omp.h>
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
    for(j = 0; j < M; j ++){
      data[i][j] = rand_unif() * (1.0F + (float)j);
    }
  }
}

int max(int a, int b){
   if(a > b){return a;}
   return b;
}
int min(int a, int b){
   if(a > b){return b;}
   return a;
}

int seqSMOTE(float** data, int N, int M){
  int total_new = (int) ((ratio - 1.0F) * (float) N) ;

  int i, j, k, idx;
  // initialize array to store the distane values for each pair of points 
   float** dist_arr = malloc(sizeof(float*) * N);
   for (idx = 0; idx < N; ++idx) {
     dist_arr[idx] = malloc(sizeof(float*) * N);
   }

   //  Calculate distance between all minority elements
   float dist, delta;
   for (i = 0; i < N; i++){
      for(j = i+1; j < N; j++){
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

   // initialize array to house synthetic values 
   float** newVals = malloc(sizeof(float*) * total_new);
   for(idx = 0; idx < total_new; ++idx) {
     newVals[idx] = malloc(sizeof(float*) * M);
   }

   // generate synthetic values and store in newVals. Store as csv upon completion.
   float rand_seed0, rand_seed1, val; 
   idx = 0;
   while(idx < total_new){
      for(i = 0; i < N; i++){
          for(j = i+1;idx < total_new && j < N; j++){
            rand_seed0 = rand_unif();
            dist = dist_arr[i][j];
            for(k = 0; k < M; k++){
                newVals[idx][k] = data[i][k] + rand_seed0 * dist;
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
                return 0;}
          }
      }
   }
   return 0;
}

int parSMOTE(float** data, int N, int M, int p) {
  omp_set_num_threads(p);
  int total_new = (int) ((ratio - 1.0F) * (float) N) ;
  int i, j, k, idx;

// initialize array to store the distance values for each pair of points 
  float** dist_arr = malloc(sizeof(float*) * N);
  for (idx = 0; idx < N; ++idx) {
    dist_arr[idx] = malloc(sizeof(float*) * N);
  }

//  Calculate distance between all minority elements
  float dist, delta;
  #pragma omp parallel for private(i,j) shared(data) schedule(auto)
  for (i = 0; i < N/2; i++){
    for(j = i+1; j < N; j++){
      dist = 0;
      for(k = 0; k < M; k++){
        delta = (data[i][k] - data[j][k]) * (data[i][k] - data[j][k]);
        dist = dist +  delta;
      }
      dist = sqrt(dist);
      dist_arr[i][j] = dist;
    }
    int new_i = (N-1) - i;
    for (j = new_i + 1; j < N; ++j) {
      dist = 0;
      for(k = 0; k < M; k++){
        delta = (data[new_i][k] - data[j][k]) * (data[new_i][k] - data[j][k]);
        dist = dist +  delta;
      }
      dist = sqrt(dist);
      dist_arr[new_i][j] = dist;
    }
  }
// initialize array to house synthetic values 
  float** newVals = malloc(sizeof(float*) * total_new);
  for(idx = 0; idx < total_new; ++idx) {
    newVals[idx] = malloc(sizeof(float*) * M);
  }

   // generate synthetic values and store in newVals. Store as csv upon completion.
  float rand_seed0, rand_seed1, val;
  idx = 0;
  int numGenerated = ratio - 1;
  int tot;
  #pragma omp parallel for private(i,j,k,tot, val, idx, dist, rand_seed0) shared(numGenerated, data, p, dist_arr, newVals, M, N) schedule(auto)
  for(i = 0; i < p; ++i){
    for(j =i* (int) (N/p); j < (i+1)* (N/p); j ++){
      for(tot = 0; tot < numGenerated; ++tot){
        idx = (int) (rand_unif() * N / p + i * N / p);
        rand_seed0 = rand_unif();
        dist = dist_arr[min(j, idx)][max(j, idx)];
        for(k = 0; k < M; k++){
            val = data[j][k] + rand_seed0 * dist;
            newVals[j*numGenerated+tot][k] = val;
          }
        }
    }
  }
  return 0;
}

int main(){
   // create an array for generated minority data to be stored in 
   int idx0, idx1, i, j, k;
   int M = 10;
   //int Ns[] = {20000};
   int Ps[] = {1,5,10,15,20};
   int Ns[] = {60,300,600,3000,6000,12000,18000,21000,30000,60000};
   int len = sizeof(Ns)/sizeof(Ns[0]);
   for(idx0 = 0; idx0 < len; idx0++){
     for(idx1 = 0; idx1 < 5; idx1 ++){
      int N = Ns[idx0]; 
      int p = Ps[idx1];
      float** data = malloc(sizeof(float*) * N);
      for(i = 0; i < N; ++i){
        data[i] = malloc(sizeof(float) * M);
      }
      generateData(data, N, M);
      printf("N=%d,M=%d\n",N,M);
      //printf("Generated the data...\n");
      
      double t1,t2, t1s,t2s;
      t1s = omp_get_wtime();
      int rc = seqSMOTE(data, N, M);
      t2s = omp_get_wtime();
      printf("Sequential: %.5g sec\n",t2-t1);
  
      t1 = omp_get_wtime();
      int foo = parSMOTE(data, N, M, p);
      t2 = omp_get_wtime();
      printf("%d,%d,%.5g,&.g;\n",N,p,t2-t1, t2s-t1s); 
     }   
  } 
}
