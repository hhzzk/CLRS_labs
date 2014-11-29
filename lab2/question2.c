/*************************************************************************
    > File Name: qustion2.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月27日 星期四 02时16分05秒
 ************************************************************************/

#include<stdio.h>
#include"common.h"

int greedy(float W, Goods *goods[], int realNum, float fill[][2])
{
    int i = 0;
    int count = 0;

    for(i = 0; i < realNum;i++)
    {
        // Check how many goods can current packet fill in
        if(goods[i]->Weight <= W)
        {
            fill[i][0] = goods[i] -> No;
            fill[i][1] = goods[i] -> Weight;
            W = W - goods[i] -> Weight;
            count++;
        }
        else
        {
            fill[i][0] = goods[i] -> No;
            fill[i][1] = W;
            count++;
            return count;
        }
    }

    return count;
}

int main()
{
    int realNum = 0;
    int fillNum = 0;
    float W = PACKAGE_CAPACITY;
    float fill[GOODS_MAX_KIND][2] = {{0}};
    Goods *goods[GOODS_MAX_KIND] = {NULL};

    realNum = getGoodsInformation(goods);

    sortByPrice(goods, realNum);

    fillNum = greedy(W, goods, realNum, fill);
    
    printResult(fill, fillNum);

    printTotal(goods, fill, fillNum);

    return 0;
}
