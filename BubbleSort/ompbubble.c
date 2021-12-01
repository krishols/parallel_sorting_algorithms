// C program for implementation of Bubble sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include<omp.h>   
#include<openacc.h>
clock_t start, end,start1,end1;
double cpu_time_used,timeu;
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}



void bubbleSort(int arr[], int n)
{
   int i;
   for (i = 0; i < n-1; i++){
	int f = i % 2;
	#pragma omp parallel for default(none) shared(arr, f, n)	
       	for (int j = f; j < n-1; j+=2){ 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
	}

   
   }
   }
}
int main()
{
	int arr[1000];
	start = clock();
	for (int i = 0; i < 1000; i++){
		arr[i] = rand() % 100;
	}
	end = clock();
	timeu = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("%f \n", timeu);
	int n = sizeof(arr)/sizeof(arr[0]);
	start1 = clock();
	bubbleSort(arr, n);
	end1 = clock();
	cpu_time_used = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
	printf("%f \n", cpu_time_used);
	return 0;
}




