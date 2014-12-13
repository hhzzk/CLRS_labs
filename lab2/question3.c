/*************************************************************************
    > File Name: question3.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月29日 星期六 15时48分49秒
 ************************************************************************/

#include<stdio.h>

// Record goods max value 
static int gMaxValue[11][13];

int maxValue(int *weights, int *values, int bagCap, int num)
{
    int value1 = 0;
    int value2 = 0;
    int maxVal = 0;
    int weight = 0;
    
    if(gMaxValue[bagCap][num] != 0)
        return gMaxValue[bagCap][num];

    if(num <= 0)
        return 0;
    // Only one goods
    if(num == 1)
    {
        if(bagCap >= weights[num-1])
            maxVal = values[num-1];
    }
    else
    {
        weight = weights[num-1];

        // Goods can not put in to the bag 
        if(bagCap < weight)
        {
            maxVal = maxValue(weights, values, bagCap, num-1);
        }
        // Judge the max value
        else
        {
            value1 = values[num-1] + maxValue(weights, values, bagCap-weight, num-1);
            value2 = maxValue(weights, values, bagCap, num-1);
        
            maxVal = value1 > value2 ? value1 : value2;
        }
    }
    gMaxValue[bagCap][num] = maxVal;

    return maxVal;
}

// Get the selected goods
int getGoods(int *weights, int *values, int flag[], int num)
{
    int i = 10;
    int j = num;

    while(gMaxValue[i][j] != 0)
    {
        if(gMaxValue[i][j]-values[j-1] == gMaxValue[i-weights[j-1]][j-1])
        {
            flag[j] = 1;
            i = i-weights[j-1];
            j = j-1;
        }
        else
        {
            j--;
        }
    }

    return 0;
}

int main()
{
    int i = 0;
    int n = 3;
    int j = 0;
    int maxVal = 0;
    int realNum = 0;
    int W = 10;
    int weight[3] = {3,4,5};
    int value[3] = {15,28,10};
    int weights[12] = {0};
    int values[12] = {0};
    int flag[13] = {0};
    int fill[3] = {0};

    for(i=0; i < n; i++ )
    {
        for(j=0; j<weight[i]; j++)
        {
            weights[realNum] = 1;
            values[realNum++] = value[i]/weight[i];
        }
    }

    maxVal = maxValue(weights, values, W, realNum);
    
    getGoods(weights, values, flag, realNum);

    realNum = 0;
    for(i=0; i<n; i++)
    {
        for(j=0; j<weight[i]; j++)
        {
            realNum++;
            if(flag[realNum] == 1)
                fill[i]++;
        }
    }

    printf("The goods weight is: ");
    for(i=0; i<n; i++)
    {
        printf("%d ", weight[i]);
    }
    printf("\n");

    printf("The goods value is: ");
    for(i=0; i<n; i++)
    {
        printf("%d ", value[i]);
    }
    printf("\n");

    printf("[No. weight]:\n");
    for(i=0; i<n; i++)
    {
        printf("[%d  %d]  ,", i+1, fill[i]);
    }
    printf("\n");

    printf("The total is %d\n",maxVal);

    return 0;
}
