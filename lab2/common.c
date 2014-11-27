/*************************************************************************
    > File Name: common.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月27日 星期四 15时25分17秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include"common.h"

// Get goods weight, value from user
int getGoodsInformation(Goods *goods[])
{
    int n = 0;
    int i = 0;
    int ret;

    printf("Please input goods total number:");
    ret = scanf("%d", &n);
    while(n > GOODS_MAX_KIND || n <= 0 || ret != 1)
    {
        printf("Illegal total number!!\n");
        printf("Please input goods total number:");
        ret = scanf("%d", &n);
    }

    for(i = 0; i < n; i++)
    {
        Goods *temp = (Goods*)malloc(sizeof(Goods));
        if(temp == NULL)
            return -1;
        
        temp -> No = i+1;
        printf("Please input %dst goods' weight and value:", i+1);
        ret = scanf("%f%f", &(temp->Weight),&(temp->Value));
        if(temp->Weight <= 0.0 || temp -> Value <= 0.0 || ret != 2)
        {
            printf("Wrong input!!\n");
            i--;
            continue;
        }
        temp->Price = temp->Value / temp->Weight;

        goods[i] = temp;
    }

    return n;
}

// Sort goods array according to price
void sortByPrice(Goods *goods[], int realNum)
{
    int i = 0;
    int j = 0;
    Goods *temp = NULL;

    for(i = 0; i < realNum-1; i++)
    {
        for(j = 0; j < realNum-1-i; j++)
        {
            if(goods[j]->Price < goods[j+1]->Price)
            {
                temp = goods[j];
                goods[j] = goods[j+1];
                goods[j+1] = temp;
            }
        }
    }

    return;
}

// Output the result
int printResult(float fill[][2], int fillNum)
{
    int i = 0;
    float totalVal = 0;
    
    printf("The order is: [No, Weight]\n");
    for(i = 0; i < fillNum; i++)
    {
        printf("[%d, %.2f] ", (int)fill[i][0], fill[i][1]);
        totalVal += fill[i][0] * fill[0][1];
    }
    printf("\n");
    printf("Total value is %.2f\n", totalVal);

    return 0;
}

