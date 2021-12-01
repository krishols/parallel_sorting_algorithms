#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

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
   while (i<n/2) {
      tmp[ti] = X[i];
      ti++; i++;
   }
   while (j<n) {
      tmp[ti] = X[j];
      ti++; j++;
   }
   memcpy(X, tmp, n*sizeof(int));
}

void mergeSort(int *X, int n, int *tmp)
{
   if (n < 2) return;

   mergeSort(X, n/2, tmp);

   mergeSort(X+(n/2), n-(n/2), tmp + n/2);

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
        if (argc <= 1){
                size = 10;
                printf("Default 10\n");
        }
        else{
                size = atoi(argv[1]);
                printf("Custom Size\n");
        }
        int *unsorted = calloc(size, sizeof(int));
        int *tmp = calloc(size, sizeof(int));

        unsorted = generateArray(unsorted, size);
        StartTimer();
        mergeSort(unsorted, size, tmp);
        double runtime = GetTimer();
        isSorted(unsorted, size);
        printf("MY TIME total: %f s\n", runtime / 1000);

        free(unsorted);
        free(tmp);
        return (0);
}
