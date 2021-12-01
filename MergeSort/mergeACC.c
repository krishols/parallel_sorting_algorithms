#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <omp.h>
#include <openacc.h>
#include "timer.h"
#define THR 10


//Function to test if the output is in asending order or not
void isSorted(int *a, int size){
   for(int i = 0; i < size - 1; i++)
      if(a[i] > a[i + 1])
        printf("Error in Sort\n");
   return;
}
/* Function to merge */
void merge(int arr[], int l, int m, int r);

// Utility function to find minimum of two integers
#pragma acc routine seq
int min(int x, int y) {
  return (x<y)? x :y;
}

/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
int curr_size;  // For current size of subarrays to be merged
               // curr_size varies from 1 to n/2
int left_start; // For picking starting index of left subarray
               // to be merged
#pragma acc data copy(arr[0:n])// pcopying (R[0:n2])
      {
  for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
 {
  #pragma acc parallel loop
   // Pick starting point of different subarrays of current size
   for (left_start=0; left_start<n-1; left_start += 2*curr_size)
   {
       // Find ending point of left subarray. mid+1 is starting
       // point of right
       int mid = left_start + curr_size - 1;

       int right_end = min(left_start + 2*curr_size - 1, n-1);

       // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
       if (mid < right_end) merge(arr, left_start, mid, right_end);
   }
 }
}}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[]
*/
 #pragma acc routine(merge) vector
 void merge(int arr[], int l, int m, int r)
{
int i, j, k;
int n1 = m - l + 1;
int n2 =  r - m;

/* create temp arrays */
int *L, *R;
 L = (int *)malloc(sizeof(int) * n1);
 R = (int *)malloc(sizeof(int) * n2);
/* Copy data to temp arrays L[] and R[] */
 #pragma acc loop independent
for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
 #pragma acc loop independent
for (j = 0; j < n2; j++)
    R[j] = arr[m + 1+ j];

/* Merge the temp arrays back into arr[l..r]*/
i = 0;
j = 0;
k = l;

while (i < n1 && j < n2)
{
    if (L[i] <= R[j]){
        arr[k] = L[i];
        i++;
    }
    else{
        arr[k] = R[j];
        j++;
    }
    k++;
}

/* Copy the remaining elements of L[], if there are any */
while (i < n1){
    arr[k] = L[i];
    i++;
    k++;
  }

/* Copy the remaining elements of R[], if there are any */
while (j < n2){
    arr[k] = R[j];
    j++;
    k++;
  }
free(L);
free(R);
}

/* Auxilary code to print out array for debugging */
void printArray(int A[], int size)
{
int i;
for (i=0; i < size; i++)
    printf("%d ", A[i]);
printf("\n");
}

//Auxilary code to generate arry to sort
int * generateArray(int *arr,int size){
  int *unsorted = calloc(size, sizeof(int));
  for (int i = 0; i < size; i++){
    unsorted[i] = rand() % 101;
  }
  return unsorted;
}

/* Driver program to test above functions */
int main(int argc, char *argv[])
 {
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
 acc_set_num_cores(numThreads);
 int *unsorted = calloc(size, sizeof(int));
 unsorted = generateArray(unsorted, size);
 StartTimer();
 mergeSort(unsorted,size);
 double runtime = GetTimer();
 printf("Runtime: %f (s)\n", runtime / 1000);
 isSorted(unsorted, size);
 return 0;
 }
