/*************************************************************************
    > File Name: normal_quicksort.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月17日 星期一 19时37分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define COUNT 400000

int Array1[COUNT] = {0};
int Array2[COUNT] = {0};

// Normal quick sort
normal_quicksort(int* Array, int p, int  r)
{
    int q = 0;
    if(p < r)
    {
        q = normal_partition(Array, p, r);
        normal_quicksort(Array, p, q-1);
        normal_quicksort(Array, q+1, r);
    }
}

// Normal partition
int normal_partition(int* Array, int p, int r)
{
    int x = 0;
    int i = 0;
    int j = 0;
    int temp = 0;

    x = Array[r];
    i = p - 1;
    for(j = p; j < r; j++)
    {
        if(Array[j] <= x)
        {
            i = i + 1;
            temp = Array[i];
            Array[i] = Array[j];
            Array[j] = temp;
        }
    }
    temp = Array[i+1];
    Array[i+1] = Array[r];
    Array[r] = temp;

    return i+1;
}

// Random quick sort
random_quicksort(int* Array, int p, int  r)
{
    int q = 0;
    if(p < r)
    {
        q = random_partition(Array, p, r);
        random_quicksort(Array, p, q-1);
        random_quicksort(Array, q+1, r);
    }
}

// Random partition
int random_partition(int* Array, int p, int r)
{
    int temp = 0;
    int value = 0;
    
    value = rand() % (r+1-p) + p;
    temp = Array[r];
    Array[r] = Array[value];
    Array[value] = temp;

    return normal_partition(Array, p, r);
}

main()
{
    int i = 0;
    int interval = COUNT/10;
    int n_start = 0;
    int n_end = 0;
    int r_start = 0;
    int r_end = 0;
    int value = 0;

    // Generate random numbers
    srand((unsigned)time(NULL));  
    for( i = 0; i < COUNT;i++ )
    {
        value = rand()%COUNT;
        Array1[i] = value;
        Array2[i] = value;
     
     //   Array1[i] = i;
     //   Array2[i] = i;
    }

    printf("The array count is %d\n", COUNT);

    // Print 10 number before sort
    printf("Before sort: \n");
    for( i = 0; i < COUNT; )
    {
        printf("%d ",Array1[i]);  
        i = i + interval;
    }
    printf("\n");
    
    // Normal sort and record time
    n_start = clock();
    normal_quicksort(Array1, 0, COUNT-1);
    n_end = clock();

    // Random sort and record time
    r_start = clock();
    random_quicksort(Array2, 0, COUNT-1);
    r_end = clock();

    // Print 10 number after sort
    printf("After sort: \n");
    printf("Normal sort: \n");
    for( i = 0; i < COUNT; )
    {
        printf("%d ",Array1[i]);  
        i = i + interval;
    }
    printf("\n");

    printf("Random sort: \n");
    for( i = 0; i < COUNT; )
    {
        printf("%d ",Array2[i]);  
        i = i + interval;
    }
    printf("\n");

    printf("Normal sort type use %d ms\n", n_end-n_start);
    printf("Random sort type use %d ms\n", r_end-r_start);

}
