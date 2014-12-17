/*************************************************************************  
    > File Name: question1.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年12月16日 星期二 21时55分13秒
 ************************************************************************/

#include<stdio.h>

#define TASK_COUNT 7
#define MAX_DEADLINE 6

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

// Sort the A according to deadline
void sortByDeadline(int count)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for(i = 0; i < count-1; i++)
    {
        for(j = 0; j < count-1-i; j++)
        {
            if(tasks[A[j]].deadline > tasks[A[j+1]].deadline)
            {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }

    return;
}

// Sort the tasks according to weight
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

// Get  independent subset A 
int greedy()
{
    int i = 0;
    int j = 0;
    int maxDeadline = MAX_DEADLINE;
    int recordCount[TASK_COUNT] = {0};
    int count = 0;
    int deadline = 0;
    int flag = 0;
    int tail = TASK_COUNT-1;

    sortByWeight();

    for(i = 0; i < TASK_COUNT; i++)
    {
        // Check if the task should be added into A[]
        deadline = tasks[i].deadline;
        flag = 0; 
        for(j = deadline; j <= maxDeadline; j++)
        {
            // Task can not added into A[]
            if(recordCount[j]+1 > j)
            {
                flag = 1;
                // Record the task in the tail of A[]
                A[tail--] = i;
                break;
            }
        }

        // Task can added into A[]
        if(!flag)
        {
            A[count++] = i;
            for(j = deadline; j < maxDeadline+1; j++)
            {
                recordCount[j]++;
            }
        }   
    }

    return count;
}

void print()
{
    int i = 0;

    printf("Task    : ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d  ", tasks[i].id);
    }
    printf("\n");

    printf("Deadline: ");
    for(i = 0; i< TASK_COUNT; i++)
    {
        printf("%d  ", tasks[i].deadline);
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
        printf("%d  ", tasks[A[i]].id);
    }
    printf("\n");

    return;
}

void main()
{
    int count = 0;

    count = greedy();
    sortByDeadline(count);
    print();

    return;
}
