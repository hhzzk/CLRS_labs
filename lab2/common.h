/*************************************************************************
    > File Name: common.h
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年11月27日 星期四 15时21分06秒
 ************************************************************************/

#ifndef COMMON_H
#define COMON_H

#define PACKAGE_CAPACITY 10 
#define GOODS_MAX_KIND 100

typedef struct Goods
{
    int No;
    float Weight;
    float Value;
    float Price;
}Goods;

void sortByPrice(Goods *goods[], int realNum);
int getGoodsInformation(Goods *goods[]);
int printResult(float fill[][2], int fillNum);
int printTotal(Goods *goods[], float fill[][2], int fillNum);

#endif //COMMON_H
