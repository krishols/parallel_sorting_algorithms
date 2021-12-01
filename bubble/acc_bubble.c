// by Jayson Morgado 
void bubbleSort(int arr[], int n)
{
   int i;
   #pragma acc parallel copyin(arr)
   {
   #pragma acc loop independent
   for (i = 0; i < n-1; i++){
        int f= i % 2;
        #pragma acc loop independent
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
