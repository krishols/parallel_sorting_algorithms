#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "timer.h"

#define TASK_SIZE 50

void merge(int *X, int n, int *tmp) {
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i<n/2 && j<n) {
      if (X[i] < X[j]) {
         tmp[ti] = X[i];
         ti++; i++;
      } else {
         tmp[ti] = X[j];
         ti++; j++;
      }
   }
   while (i<n/2) { /* finish up lower half */
      tmp[ti] = X[i];
      ti++; i++;
   }
   while (j<n) { /* finish up upper half */
      tmp[ti] = X[j];
      ti++; j++;
   }
   memcpy(X, tmp, n*sizeof(int));
}

void mergeSort(int *X, int n, int *tmp)
{
   if (n < 2) return;

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergeSort(X, n/2, tmp);

   #pragma omp task shared(X) if (n > TASK_SIZE)
   mergeSort(X+(n/2), n-(n/2), tmp + n/2);

   #pragma omp taskwait
   merge(X, n, tmp);
}

//Auxilary Function used to help print an array for debugging
void printArray(int *a, int size){
   for(int i = 0; i < size; i++)
       printf("%d ", a[i]);
   printf("\n");
}

//Auxilary function will print if the list is not properly sorted
void isSorted(int *a, int size){
   for(int i = 0; i < size - 1; i++)
      if(a[i] > a[i + 1]){
        printf("List not sorted");
      }
}

//Auxilary function used to generate the array to sort
int * generateArray( int *arr, int size){
  int *unsorted = calloc(size, sizeof(int));
  for (int i = 0; i < size; i++){
    unsorted[i] = rand() % 101;
  }
  return unsorted;
}

int main(int argc, char *argv[]) {
        srand(123456);
        int size;
        int numThreads;
        if (argc <= 1){
                size = 10;
                numThreads = 2;
                printf("Default 10\n");
        }
        else{
                size = atoi(argv[1]);
                numThreads = atoi(argv[2]);
                printf("Custom Size\n");
        }
        int *unsorted = calloc(size, sizeof(int));
        int *tmp = calloc(size, sizeof(int));

        omp_set_dynamic(0);              /** Explicitly disable dynamic teams **/
        omp_set_num_threads(numThreads); /** Use N threads for all parallel regions **/

        unsorted = generateArray(unsorted, size);
        StartTimer();
        #pragma omp parallel
        {
            #pragma omp single
            mergeSort(unsorted, size, tmp);
        }
        double runtime = GetTimer();
        printf("Time: %fs\n",runtime / 1000);
        isSorted(unsorted, size);

        free(unsorted);
        free(tmp);
        return (0);
}
