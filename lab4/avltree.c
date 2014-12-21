#include<stdio.h>
#include<stdlib.h>

#define COUNT 11

typedef struct avlTree
{
	int             key;
	int             height;
	struct avlTree *left;
	struct avlTree *right;
}avlTree;

avlTree* createNode(int key)
{
	avlTree* p = malloc(sizeof(avlTree));
    if(p = NULL)
        return NULL;

	p->key = key;
	p->height = 0;
	p->left = NULL;
	p->right = NULL;

	return p;
}

int Height(avlTree* node)
{
	if(node == NULL)
        return -1;
    
    return node->height;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

avlTree* rrRotate(avlTree* node)
{
	avlTree* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	node->height = max(Height(node->left), Height(node->right)) + 1;
	temp->height = max(Height(temp->left), node->height) + 1;
	return temp;
}

avlTree* llRotate(avlTree* node)
{
	avlTree* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	node->height = max(Height(node->left), Height(node->right)) + 1;
	temp->height = max(Height(temp->right), node->height) + 1;
	return temp;
}

avlTree* lrRotate(avlTree* node)
{
	node->left = llRotate(node->left);
	return rrRotate(node);
}

avlTree* rlRotate(avlTree* node)
{
	node->right = rrRotate(node->right);
	return llRotate(node);
}

// Insert new node to the tree
avlTree* avlInsert(avlTree *node, avlTree* newNode)
{
    if(newNode == NULL)
        return;

	if(node == NULL)
    {
		node = newNode;
        return node;
    }

    if(newNode->key < node->key)
		node->left = avlInsert(node->left, newNode);
	else
		node->right = avlInsert(node->right, newNode);
	
	node->height = max(Height(node->left), Height(node->right)) + 1;
	if(Height(node->left) - Height(node->right) == 2)
	{
		if(newNode->key < node->left->key)
			node = rrRotate(node);
		else
			node = lrRotate(node);
	}
	else if(Height(node->right) - Height(node->left) == 2)
	{
		if(newNode->key < node->right->key)
			node = rlRotate(node);
		else
			node = llRotate(node);
	}
	return node;
}

// Delete node from the tree
avlTree* avlDelete(avlTree *node, int key)
{
    avlTree *temp = NULL;

	if(node == NULL)
		return NULL;

	if(key == node->key)
	{
        // right child is null, delete derectly
		if(node->right == NULL)
		{
			temp = node;
			node = node->left;
			free(temp);
			return node;
		}
        // right child not null
		else
		{
			temp = node->right;
			while(temp->left)
				temp = temp->left;

			node->key = temp->key;
			node->right = avlDelete(node->right, temp->key);
		}
	}
	else if(key < node->key)
		node->left = avlDelete(node->left, key);
	else
		node->right = avlDelete(node->right, key);
	
	node->height = max(Height(node->left), Height(node->right)) + 1;
	if(Height(node->right) - Height(node->left) == 2)
	{
		if(Height(node->right->right) >= Height(node->right->left))
			node = llRotate(node);
		else
			node = rlRotate(node);
	}
	else if(Height(node->left) - Height(node->right) == 2)
	{
		if(Height(node->left->left) >= Height(node->left->right))
			node = rrRotate(node);
		else
			node = lrRotate(node);
	}

	return node;
}

void visit(avlTree* node)
{
    if(node == NULL)
        return;

	visit(node->left);
	printf("%d[%d] ", node->key, node->height);
	visit(node->right);
	
    return;
}

void main(int argc, char* argv[])
{
    int i = 0;
    avlTree* root = NULL;
    avlTree *node = NULL;
	int keys[] = {13,6,19,3,8,16,20,1,5,10};

	for(i = 0; i< COUNT;i++)
    {
        node = createNode(keys[i]);
        if(node == NULL)
            return;
		root = avlInsert(root, node);
    }

    printf("Insert order: ");
    for(i = 0; i < COUNT; i++)
    {
        printf("%d ", keys[i]);
    }
    printf("\n");
    
    printf("After Insert: ");
    visit(root);
    printf("\n");

    root = avlDelete(root, 10);
    printf("After delete 10:");
    visit(root);

	return;
}
