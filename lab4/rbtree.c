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
    if(gNIL == NULL)
        return;
    
    gNIL->color = BLACK;
    gNIL->key   = -1;
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
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->right = x;
    x->p = y;

    return;
}

void leftRotate(rbTree *x)
{
    rbTree *y = NULL;

    if(x == NULL)
        return;

    y = x->right;
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
            else 
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rightRotate(z->p->p);
            }
        }
        else if(z->p == z->p->p->right)
        {
             y = z->p->p->left;

            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else 
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                leftRotate(z->p->p);
            }
        }
    }

    gT->color = BLACK;  

    return;
}

void rbInsert(rbTree *z)
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

void rbDeleteFixup(rbTree *x)
{
    rbTree *w = NULL;

    if(x = NULL)
        return;

    while(x != gT && x->color == BLACK)
    {
        if(x == x->p->left)
        {
            w = x->p->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(x->p);
                w = x->p->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else if(w->right->color == BLACK)
            {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = x->p->right;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->right->color = BLACK;
            leftRotate(x->p);
            x = gT;
        }
        else
        {
            w = x->p->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                leftRotate(x->p);
                w = x->p->left;
            }

            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else if(w->left->color == BLACK)
            {
                w->right->color = BLACK;
                w->color = RED;
                leftRotate(w);
                w = x->p->left;
            }
            w->color = x->p->color;
            x->p->color = BLACK;
            w->left->color = BLACK;
            rightRotate(x->p);
            x = gT;
        }
    }

    x->color = BLACK;
}

rbTree* treeMinmum(rbTree *x)
{
    if(x == NULL)
        return;

    while(x->left != gNIL)
        x = x->left;

    return x;
}

void rbTransplant(rbTree *u, rbTree *v)
{
    if(u == NULL || v ==NULL)
        return;

    if(u->p == gNIL)
        gT = v;
    else if(u == u->p->left)
        u->p->left = v;
    else
    {
        u->p->left == v;
        v->p = u->p;
    }

    return;
}

// Delete node z from tree
void rbDelete(rbTree *z)
{
    rbTree *y = NULL;
    rbTree *x = NULL;
    int yOriCol = 0;

    if(z == NULL)
        return;
    
    y = z;
    yOriCol = y->color;
    if(z->left == gNIL)
    {
        x = z->right;
        rbTransplant(z, z->left);
    }
    else if(z->right == gNIL)
    {
        x = z->left;
        rbTransplant(z, z->left);
    }
    else
    {
        y = treeMinmum(z->right);
        yOriCol = y->color;
        x = y->right;
        if(y->p == z)
        {
            x->p = y;
        }
        else
        {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rbTransplant(y, y->right);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if(yOriCol == BLACK)
    {
        rbDeleteFixup(x);
    }

    return;
}

void visit(rbTree *x)
{
    if(x == gNIL)
        return;
    visit(x->left);
    printf("%d[%d] ",x->key, x->color);
    visit(x->right);

    return;
}

void main()
{
    rbTree *node = NULL;
    int keys[COUNT] = {11, 2, 14, 1, 7, 15, 5, 8, 4};
    int i = 0;

    printf("Insert sort is: ");
    for(i = 0; i < COUNT; i++)
    {
        printf("%d ", keys[i]);
    }
    printf("\n");

    treeInit();
    for(i = 0; i < COUNT; i++)
    {
        node = createNode(keys[i], RED);
        if(node == NULL)
            return;

        rbInsert(node);
    }
    
    printf("Afer Insert: ");
    visit(gT);
    printf("\n");

    rbDelete(node);
    printf("Delete node 4: ");
    visit(gT);
    printf("\n");

    return;
}
