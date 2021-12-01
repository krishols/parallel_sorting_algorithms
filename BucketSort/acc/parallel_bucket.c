/* Code originally from The Crazy Programmer https://www.thecrazyprogrammer.com/2017/02/bucket-sort-in-c.html
 *
 * Edited by Kristina Holsapple
 *
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"

struct bucket
{
    int count;
    int* value;
};

int compareIntegers(const void* first, const void* second)
{
    int x = *((int*)first), y =  *((int*)second);
    if (x == y)
    {
        return 0;
    }
    else if (x < y)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void bucketSort(int array[],int n)
{
    struct bucket buckets[3];
    int i, j, k;
    printf("Before pragma\n");
    {
	    printf("In first pragma\n");
    {
    for (int i = 0; i < 3; i++)
    {
        buckets[i].count = 0;
        buckets[i].value = (int*)malloc(sizeof(int) * n);
    }
    printf("In first loop\n");
#pragma acc data copy(buckets, array, n)
   {
#pragma acc parallel loop 
    for (int i = 0; i < n; i++)
    {
        if (array[i] < 0)
        {
            buckets[0].value[buckets[0].count++] = array[i];
        }
        else if (array[i] > 10)
        {
            buckets[2].value[buckets[2].count++] = array[i];
        }
        else
        {
            buckets[1].value[buckets[1].count++] = array[i];
        }
    }
   }
    printf("In second loop\n");
    }
    }
    for (k = 0, i = 0; i < 3; i++)
    {
        // now using quicksort to sort the elements of buckets
        qsort(buckets[i].value, buckets[i].count, sizeof(int), &compareIntegers);
        for (j = 0; j < buckets[i].count; j++)
        {
            array[k + j] = buckets[i].value[j];
        }
        k += buckets[i].count;
        free(buckets[i].value);

    }
printf("Done\n");
    return;
}

int main(int am, char *arg[]) {
    int size;
    size = atoi(arg[1]);
    printf("0: %d\n", size);
    //int array[100] = { 5, -34, 10, 1, -42, 123, 2, 395, 5, 4, 1234, 7 };
    int array[size];
    for (int i = 0; i < size; i++) {
	array[i] = rand();
    }
    int i = size,j,k,n;

    n=i;
    /*
    printf("Before Sorting\n");
    for (j = 0; j<i; j++)
    {
        printf("%d ", array[j]);
    }
*/
    StartTimer();
    bucketSort(array, n);
    double runtime = GetTimer();
    printf("Total: %f s \n", runtime / 1000);

    /*
   *
   *
    printf("\n After Sorting\n");
    for (k = 0; k<i; k++)
        printf("%d ", array[k]);

*/
    return 0;
}
