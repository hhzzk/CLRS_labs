/*************************************************************************
    > File Name: common.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月27日 星期四 15时25分17秒
 ************************************************************************/

#include<stdio.h>
#include"common.h"

// Get goods weight, value from user
int getGoodsInformation(Goods *goods[])
{
    int n = 0;
    int i = 0;

    printf("Please input goods total number:");
    scanf("%d", &n);
    while(n > GOODS_KIND || n <= 0)
    {
        printf("Illegal total number!!\n");
        printf("Please input goods total number:");
        scanf("%d", &n)
    }


    for(i = 0; i < n; i++)
    {
        goods[i]->No = i+1;
        printf("Please input %dst goods' weight and value:", i+1);
        scanf("%f%f", goods[i]->Weight,goods[i]->Value);
        goods[i]->Price = goods[i]->Value / goods[i]->Weight;
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
            if(goods[j]->Price < goods->Price[j+1])
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
void printResult(float **fill, int fillNum)
{
    int i = 0;
    
    printf("The order is: [No, Weight]\n");
    for(i = 0; i < fillNum; i++)
    {
        printf("[%d, %f] ", fill[i][0], fill[i][1]);
    }

    return;
}

