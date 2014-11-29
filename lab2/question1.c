/*************************************************************************
    > File Name: question1.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月29日 星期六 15时48分49秒
 ************************************************************************/

#include<stdio.h>
#include"common.h"

// Record goods which was filled in
static int gFill[GOODS_MAX_KIND] = {0};
static int gCount = -1;

int maxValue(int W, Goods *goods[],int start, int end)
{
    int value1 = 0;
    int value2 = 0;
    int weight = 0;

    // Bag is full
    if(W <= 0 || start > end)
        return 0;

    weight = goods[start]->Weight;

    // The lastest goods
    if(start == end && W >= weight)
    {
        return goods[end]->Value;
    }

    // Goods can not put in to the bag 
    if(W < weight)
    {
        return maxValue(W, goods, start+1, end);
    }
    // Judge the max value
    else
    {
        value1 = goods[start]->Value + maxValue(W-weight, goods, start+1, end);
        value2 = maxValue(W, goods, start+1, end);
        
        if(value1 >= value2)
        {
            gFill[++gCount] = start+1;
            return value1;
        }
        return value2;
    }

    return 0;
}

int main()
{
    int i = 0;
    int realNum = 0;
    int fillNum = 0;
    float W = PACKAGE_CAPACITY;
    Goods *goods[GOODS_MAX_KIND] = {NULL};

    realNum = getGoodsInformation(goods);

   // sortByPrice(goods, realNum);

    fillNum = maxValue(W, goods, 0, realNum-1);
    printf("The total is %d\n",fillNum);
    
    for(i = 0; i<=gCount;i++)
    {
        printf("%d ",gFill[i]);
    }
    printf("\n");

    return 0;
}
