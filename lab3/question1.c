/*************************************************************************  
    > File Name: question1.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年12月16日 星期二 21时55分13秒
 ************************************************************************/

#include<stdio.h>

#define TASK_COUNT 7

typedef struct task
{
    int id;
    int deadline;
    int weight;
}task;


task tasks[TASK_COUNT] = {{1, 4, 70}, {2, 2, 60}, \
                          {3, 4, 50}, {4, 3, 40}, \
                          {5, 1, 30}, {6, 4, 20}, \
                          {7, 6, 10}
                         };
int A[TASK_COUNT] = {0};


void sortByWeight()
{
    int i = 0;
    int j = 0;
    task temp = {};

    for(i = 0; i < TASK_COUNT-1; i++)
    {
        for(j = 0; j < TASK_COUNT-1-i; j++)
        {
            if(tasks[j].weight < tasks[j+1].weight)
            {
                memcpy(&temp, &tasks[j], sizeof(task));
                memcpy(&tasks[j], &tasks[j+1], sizeof(task));
                memcpy(&tasks[j+1], &temp, sizeof(task));
            }
        }
    }

    return;
}

// This function will make array A be a right task scheduling 
void greedy()
{
    int i = 0;
    int j = 0;
    int count = 1;
    int maxDeadline = 0;
    int tempDeadline = 0;
    int isExist = 0;
    int tail = TASK_COUNT-1;

    for(i = 1; i < TASK_COUNT; i++)
    {
        // Check if has same deadline task in A[]
        isExist = 0;
        for(j = 0; j < count; j++)
        {
            if(tasks[A[j]].deadline == tasks[i].deadline)
            {
                isExist = 1;
                A[tail--] = i;
                break;
            }
        }
        if(isExist)
            continue;
        
        // If current task's deadline bigger than the max deadline in A[]
        // than add crrent task to A[]
        if(tasks[A[count-1]].deadline < tasks[i].deadline)
        {
            A[count++] = i;
            continue;
        }
       
        // Cheak if current task can add into A[]
        count++;
        if(tasks[A[count-1]].deadline >= count)
        {
            // Insert task to A[], check from tail to top
            for(j = count-1; j >= 0; j--)
            {
                if(tasks[A[j]].deadline > tasks[i].deadline )
                {
                    A[j+1] = A[j];
                }
                else
                {
                    A[j] = i;
                    break;
                }
            }
        }
        else
        {
            A[tail--] = i;
            count--;
        }
    }
}

void print()
{
    int i = 0;

    printf("Task    : ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d ", tasks[i].id);
    }
    printf("\n");

    printf("Deadline: ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d ", tasks[i].deadline);
    }
    printf("\n");

    printf("Weight  : ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d ", tasks[i].weight);
    }
    printf("\n");
        
    printf("Sequence: ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d ", tasks[A[i]].id);
    }
    printf("\n");

    return;
}

void main()
{
    sortByWeight();
    
    greedy();
    
    print();

    return;
}
