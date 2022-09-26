/*
 * BINARY SEARCH TREE
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<time.h>

typedef struct node{
	int data;
	struct node *left, *right;
}node;

typedef struct{
	node *root;
	int size;
}bst;

typedef struct qnode
{
	node *nptr;
	struct qnode *next;
}qnode;

typedef struct queue
{
	qnode *front;
	qnode *rear;
	int size;
}queue;

//========================================================================================================================================================================
//	DECLARATIONS
//========================================================================================================================================================================

bst *init(void);
node *getNode(int data);

bool isEmpty(bst );
bool isFull(void);

void preOrder(bst );
void preorder(node *);
void inOrder(bst );
void inorder(node *);
void postOrder(bst );
void postorder(node *);

queue *initQ(void);
bool isEmptyQ(queue *);
bool isFullQ(void);
qnode *getQNode(node *);
void enqueue(queue *, node *);
node *dequeue(queue *);
void killQ(queue *qptr);
void levelOrder(bst);
void levelorder(node *);

void insert(bst *, int);
void iInsert(bst *, int);
node *rInsert(node *, int);

node *search(bst, int);
node *rSearch(node *, int);

void deleteTree(bst *);
void rDeleteTree(node *);

//========================================================================================================================================================================
//	DEFINATIONS
//========================================================================================================================================================================
//========================================================================================================================================================================
//INITIALIZATIONS
//========================================================================================================================================================================

bst *init(void)
{
	bst *newTree = NULL;
	if(!(newTree = (bst *)malloc(sizeof(bst))))
		return NULL;

	newTree->root = NULL;
	newTree->size = 0;

	return newTree;
}

node *getNode(int data)
{
	node *newNode = NULL;
	if(!(newNode = (node *)malloc(sizeof(node))))
		return NULL;

	newNode->data = data;
	newNode->left = newNode->right = NULL;

	return newNode;
}

bool isEmpty(bst tree)
{
	if(!tree.root)
		return true;
	return false;
}
bool isFull(void)
{
	node *tmp = NULL;
	if(!(tmp=(node *)malloc(sizeof(node))))
		return true;
	free(tmp);
	return false;
}

//========================================================================================================================================================================
//TRAVERSAL
//========================================================================================================================================================================

void preOrder(bst tree)
{
	if(isEmpty(tree))
		return;
	
	preorder(tree.root);
	printf("\n\n");
	
	return;
}
void preorder(node *root)
{
	if(root)
	{
		printf("%10d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
	return;
}
void inOrder(bst tree)
{
	if(isEmpty(tree))
		return;
	
	inorder(tree.root);
	printf("\n\n");
	
	return;
}
void inorder(node *root)
{
	if(root)
	{
		inorder(root->left);
		printf("%10d ", root->data);
		inorder(root->right);
	}
	return;
}
void postOrder(bst tree)
{
	if(isEmpty(tree))
		return;
	
	postorder(tree.root);
	printf("\n\n");
	
	return;
}
void postorder(node *root)
{
	if(root)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%10d ", root->data);
	}
	return;
}

queue *initQ(void)
{
	queue *headNode = NULL;
	if(!(headNode = (queue *)malloc(sizeof(queue))))
		return NULL;
	headNode->front=headNode->rear= NULL;
	headNode->size = 0;
	return headNode;
}

bool isEmptyQ(queue *qptr)
{
	if(!qptr || !(qptr->front))
		return true;
	return false;
}

bool isFullQ(void)
{
	qnode *tmp=NULL;
	if(!(tmp=(qnode*)malloc(sizeof(qnode))))
		return true;
	free(tmp);
	return false;
}

qnode *getQNode(node* nptr)
{
	qnode *newQNode=NULL;

	if(!(newQNode = (qnode *)malloc(sizeof(qnode))))
		return NULL;

	newQNode->nptr=nptr;
	newQNode->next = NULL;

	return newQNode;
}

void enqueue(queue *qptr, node *nptr)
{
	if(isFullQ() || !qptr)
		return ;
	qnode *newNode = getQNode(nptr);

	if(!qptr->front)
	{
		qptr->front = qptr->rear = newNode;
	}
	else
	{
		qptr->rear->next = newNode;
		qptr->rear = newNode;
	}

	qptr->size++;
	return ;
}

node *dequeue(queue *qptr)
{
	if(isEmptyQ(qptr))
		return NULL;

	qnode *tmp = qptr->front;
	qptr->front = tmp->next;

	node *nptr = tmp->nptr;

	free(tmp);
	qptr->size--;

	return nptr;
}

void killQ(queue *qptr)
{
	while(!isEmptyQ(qptr))
		dequeue(qptr);
	free(qptr);
	return;
}

void levelOrder(bst tree)
{
	if(isEmpty(tree))
		return ;
	levelorder(tree.root);
	printf("\n\n");
	return ;
}

void levelorder(node *root)
{
	if(!root)
		return ;
	
	queue *qptr=NULL;
	if(!(qptr = initQ()))
		return ;
	
	enqueue(qptr, root);
	node *nptr=NULL;
	
	while(!isEmptyQ(qptr))
	{
		nptr = dequeue(qptr);
		
		printf("%10d ", nptr->data);
		
		if(nptr->left)
			enqueue(qptr, nptr->left);
		if(nptr->right)
			enqueue(qptr, nptr->right);
	}

	killQ(qptr);
	return ;
}


//========================================================================================================================================================================
// INSERTION
//========================================================================================================================================================================

void iInsert(bst *tree, int val)
{
	node *root = tree->root;
	node *iptr=NULL, *jptr = NULL;

	if(isFull())
		return ;

	node *newNode = getNode(val);

	if(!root)
	{
		tree->root = newNode;
		tree->size++;
		return ;
	}

	iptr = root;
	jptr = NULL;

	while(iptr)
	{
		jptr = iptr;

		if(iptr->data < val)
			iptr = iptr->right;
		else if(iptr->data > val)
			iptr = iptr->left;
		else 
		{
			free(newNode);
			return ;
		}
	}

	if(jptr->data < val)
		jptr->right = newNode;
	else 
		jptr->left = newNode;
	
	tree->size++;
	return ;
}

node* rInsert(node *root, int val)
{
	if(!root)
	{
		node *newNode = getNode(val);
		return newNode;
	}

	if(root->data > val)
		root->left = rInsert(root->left, val);
	else
		root->right = rInsert(root->right, val);

	return root;
}

void insert(bst *tree, int val)
{
	if(isFull() || search(*tree, val))
		return ;

	tree->root = rInsert(tree->root, val);
	tree->size++;

	return ;
}
//========================================================================================================================================================================
// SEARCH
//========================================================================================================================================================================

node *rSearch(node *tree, int val)
{
	if(!tree || tree->data == val)
		return tree;
	if(tree->data < val)
		rSearch(tree->right, val);
	else
		rSearch(tree->left, val);
}

node *search(bst tree, int val)
{
	if(isEmpty(tree))
		return NULL;
	return rSearch(tree.root, val);
}

//========================================================================================================================================================================
// DELETE
//========================================================================================================================================================================

void deleteTree(bst *ptr)
{
	if(isEmpty(*ptr))
		return ;
	rDeleteTree(ptr->root);
	free(ptr);
	return ;
}

void rDeleteTree(node *root)
{
	if(!root)
		return ;
	
	rDeleteTree(root->left);
	rDeleteTree(root->right);
	free(root);
	return ;
	
}

//========================================================================================================================================================================
//
//========================================================================================================================================================================



//========================================================================================================================================================================
//
//========================================================================================================================================================================



//========================================================================================================================================================================
//
//========================================================================================================================================================================



//========================================================================================================================================================================
//
//========================================================================================================================================================================



//========================================================================================================================================================================
//	DIRVER
//========================================================================================================================================================================

int main(void)
{
	bst *p=NULL;
	p = init();
	srand(time(0));	
	
	for(int i=0; i<1024; i++)
		insert(p,rand() % 100000);
	
	inOrder(*p);
	deleteTree(p);
	return 0;
}
