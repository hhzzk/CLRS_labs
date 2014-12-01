/*************************************************************************
    > File Name: question1.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月29日 星期六 15时48分49秒
 ************************************************************************/

#include<stdio.h>
#include"common.h"

// Record goods max value 
static int gMaxValue[PACKAGE_CAPACITY+1][GOODS_MAX_KIND+1];

int maxValue(Goods *goods[], int bagCap, int goodsNum)
{
    int value1 = 0;
    int value2 = 0;
    int maxVal = 0;
    int weight = 0;
    
    if(gMaxValue[bagCap][goodsNum] != -1)
        return gMaxValue[bagCap][goodsNum];

    if(goodsNum <= 0)
        return 0;
    // Only one goods
    if(goodsNum == 1)
    {
        if(bagCap >= goods[goodsNum-1] -> Weight)
            maxVal = goods[goodsNum-1] -> Value;
    }
    else
    {
        weight = goods[goodsNum-1]->Weight;

        // Goods can not put in to the bag 
        if(bagCap < weight)
        {
            maxVal = maxValue(goods, bagCap, goodsNum-1);
        }
        // Judge the max value
        else
        {
            value1 = goods[goodsNum-1]->Value + maxValue(goods, bagCap-weight, goodsNum-1);
            value2 = maxValue(goods, bagCap, goodsNum-1);
        
            maxVal = value1 > value2 ? value1 : value2;
        }
    }
    gMaxValue[bagCap][goodsNum] = maxVal;

    return maxVal;
}

int main()
{
    int i = 0;
    int j = 0;
    int realNum = 0;
    int maxVal = 0;
    float W = PACKAGE_CAPACITY;
    Goods *goods[GOODS_MAX_KIND] = {NULL};

    for(i=0; i <= W; i++ )
    {
        for(j=0; j<=GOODS_MAX_KIND; j++)
            gMaxValue[i][j] = -1;
    }

    realNum = getGoodsInformation(goods);

   // sortByPrice(goods, realNum);

    maxVal = maxValue(goods, W, realNum);
    printf("The total is %d\n",maxVal);

    return 0;
}
