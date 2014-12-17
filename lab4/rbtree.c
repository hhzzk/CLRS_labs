/*************************************************************************
    > File Name: rbtree.c
    > Author: king
    > Mail: wangjinrui2013@gmail.com 
    > Created Time: 2014年12月17日 星期三 19时56分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define BLACK 0 
#define RED   1
#define COUNT 9

typedef struct rbTree
{
    int           color;
    int           key;
    struct rbTree *left;
    struct rbTree *right;
    struct rbTree *p;
}rbTree;

// NIL node
rbTree *gNIL = NULL; 
// Root node
rbTree *gT = NULL;

// Generate a red-black tree node
rbTree *createNode(key, color)
{
    rbTree *node = NULL;

    node = (rbTree*)malloc(sizeof(rbTree));
    if(node == NULL)
        return NULL;
    
    node->color = color;
    node->key   = key;
    node->left  = gNIL;
    node->right = gNIL;
    node->p     = gNIL;

    return node;
}

void treeInit()
{   
    // Generate NIL node
    gNIL = (rbTree*)malloc(sizeof(rbTree));
    if(gNIL = NULL)
        return;
    
    gNIL->color = BLACK;
    gNIL->key   = 0;
    gNIL->left  = NULL;
    gNIL->right = NULL;
    gNIL->p     = NULL;

    // Init root node
    gT = gNIL;

    return;    
}

void rightRotate(rbTree *x)
{
    rbTree *y = NULL;

    if(x == NULL)
        return;

    y = x->left;
    x->left = y->right;

    if(y->right != gNIL)
    {
        y->right->p = x;
    }
    y->p = x->p;

    if(x->p == gNIL)
        gT = y;
    else if(x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;

    y->right = x;
    x->p = y;

    return;
}

void leftRotate(rbTree *x)
{
    rbTree *y = NULL;

    if(x == NULL)
        return;

    y = x->left;
    x->right = y->left;

    if(y->left != gNIL)
    {
        y->left->p = x;
    }
    y->p = x->p;

    if(x->p == gNIL)
        gT = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->left = x;
    x->p = y;

    return;
}

void rbInsertFixup(rbTree *z)
{
    rbTree *y = NULL;

    if(z == NULL)
        return;

    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left)
        {
            y = z->p->p->right;

            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if(z == z->p->right)
            {
                z = z->p;
                leftRotate(z);
            }
            else
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
        }
        else
        {
             y = z->p->p->left;

            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if(z == z->p->left)
            {
                z = z->p;
                rightRotate(z);
            }
            else
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }

    gT->color = BLACK;  

    return;
}

void treeInsert(rbTree *z)
{
    rbTree *y = gNIL;
    rbTree *x = gT;
    
    if(z == NULL)
        return;

    while(x != gNIL)
    {
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;
    if(y == gNIL)
    {
        gT = z;
    }
    else
    {
        if(z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }

    z->left = gNIL;
    z->right = gNIL;
    z->color = RED;
    rbInsertFixup(z);

    return;
}

void main()
{
    rbTree *node = NULL;
    int keys[COUNT] = {1, 2, 5, 4, 8, 7, 11, 14, 15};
    int i = 0;

    treeInit();
    for(i = 0; i < COUNT; i++)
    {
        node = createNode(keys[i], RED);
        if(node == NULL)
            return;

        treeInsert(node);
    }

    return;
}
