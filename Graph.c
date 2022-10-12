// GRAPHS USING ADJACENCY LIST REPRESENTATION

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>
#include<time.h>

typedef struct Node{
	int vertex;
	int weight;
	void *payload;
	struct Node *next;
}node;

typedef struct Edge{
	int src, dest, wt;
}edge;

typedef struct Graph{
	node **space;
	int edgeCnt;
	int vertexCnt;
}graph;

// DECLARATIONS
graph *initGraph(void);
bool deinitGraph(graph *);
void initGraphSpace(graph *, char *);
bool deinitGraphSpace(graph *);
void BreadthFirstSearch(graph *, int);
void DepthFirstSearch(graph *, int);
int getConnectedVertices(graph *, int);
int inDegree(graph*, int);
int outDegree(graph*, int);
bool isGraphValid(graph *);
bool isVertexValid(graph *, int);
bool isDirected(graph *);
void displayMatrix(graph *);
node *getNode(int vertex, int weight, void *payload);
// REQUIRED DATA STRUCTURES

//##########################################################################################################################
//                                                  Stack
//##########################################################################################################################
typedef struct StackNode
{
    int data;
    struct StackNode *next;
} snode;
snode *top = NULL;
int isEmptyStk(snode *st)
{
    return st ? 0 : 1;
}
int isFullStk()
{
    int r;
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    r = !t ? 1 : 0; // if t is NULL return 1 that is heap is full else return 0
    free(t);
    return r;
}
char StackTop(snode *st)
{
    if (st)
        return st->data;
    return -1;
}
void push(snode *st, int x)
{
    if (isFullStk())
    {
        printf("Stack Overflow!");
        return;
    }
    snode *t;
    t = (snode *)malloc(sizeof(snode));
    t->data = x;
    t->next = st;
    top = t;
}
int pop(snode *st)
{
    int x = -1;
    if (isEmptyStk(st))
    {
        printf("Stack Underflow!\n");
    }
    else
    {
	    snode *tmp;
	    tmp = top;
	    top = top->next;
	    x = st->data;
	    free(tmp);
    }
    return x;
}
int peek(snode *st, int index)
{
    int i;
    if (isEmptyStk(st)) // return -1 when stack is empty
        return -1;
    for (i = 0; i < index - 1 && st; i++) // move st until it reaches on index or st is is not null
        st = st->next;
    return st->data;
}
void KillStack(snode *st)
{
    if (!st)
        return;
    while (st)
    {
        pop(st);
    }
}
//##########################################################################################################################
//                                                  Queue
//##########################################################################################################################
typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
} qnode;
qnode *front = NULL, *rear = NULL;
int isEmptyQ()
{
    if (front == NULL)
        return 1;
    return 0;
}
int isFullQ()
{
    qnode *t;
    t = (qnode *)malloc(sizeof(qnode));
    if (!t)
        return 1;
    free(t);
    return 0;
}

void enqueue(int x)
{
    if (isFullQ())
    {
        printf("Queue Overflow!\n");
        return;
    }
    else
    {
        qnode *t;
        t = (qnode *)malloc(sizeof(qnode));
        t->data = x;
        t->next = NULL;
        if (front == NULL)
            front = rear = t;
        else
        {
            rear->next = t;
            rear = t;
        }
    }
}
int dequeue()
{
    int x = -1;
    if (isEmptyQ())
    {
        printf("Queue Underflow!\n");
        return x;
    }
    else
    {
        qnode *p;
        p = front;
        front = front->next;
        x = p->data;
        free(p);
    }
    return x;
}
void destroyQ()
{
    while (!isEmptyQ())
        dequeue();
} //##########################################################################################################################
//                                                      Heap
//##########################################################################################################################
// Min Heap
typedef struct
{
    edge *H;
    int size;
    int length;
} heap;
int isFull(heap *);
int isEmpty(heap *);
void initHeap(heap *, int);
void insert(heap *, edge);
edge returnMin(heap *);
void heapify(heap *, int);
void adjust(heap *);

void swap(edge *a, edge *b)
{
    edge temp = *a;
    *a = *b;
    *b = temp;
    return;
}
int isFull(heap *h)
{
    if (h->length == h->size - 1)
        return 1;
    return 0;
}
int isEmpty(heap *h)
{
    if (h->length == -1)
        return 1;
    return 0;
}
void initHeap(heap *h, int s)
{
    h->H = (edge *)malloc(sizeof(edge) * s);
    h->size = s;
    h->length = -1;
    return;
}

void insert(heap *h, edge x)
{
    // 1. Check if given heap is full.
    // 2. If not full then increment length and insert new value at length th index in heap.
    // 3. Now heapify until child is in rule (min/max) and parent is greater than root (0)

    if (isFull(h))
        return;
    int child = ++h->length;
    h->H[child] = x;
    heapify(h, child);
    return;
}
edge returnMin(heap *h)
{
    // 1. check if given heap is empty.
    // 2. if not empty then return the rule ele (min/max), swap 0th ele with h.length th ele and decrement length
    // 3. adjust the heap i.e. heapify from top to down
    edge x = {-1, -1, -1};
    if (isEmpty(h))
        return x;
    x = h->H[0];
    swap(&h->H[0], &h->H[h->length--]);
    adjust(h);
    return x;
}

void heapify(heap *h, int child)
{
    int parent = (child - 1) / 2;
    int n = h->H[child].wt;
    int pn = h->H[parent].wt;

    if (n < pn && (parent >= 0 && child <= h->length))
    {
        swap(&h->H[child], &h->H[parent]);
        heapify(h, parent);
    }
    return;
}
void adjust(heap *h)
{
    int parent = 0;
    int min;

    while (parent <= h->length)
    {
        int lc = parent * 2 + 1;
        int rc = parent * 2 + 2;
        int ln = h->H[lc].wt;
        int rn = h->H[rc].wt;

        if (lc <= h->length)
        {
            if (rc <= h->length) // right child exists
            {
                if (ln >= rn) // left node is greater than or equal to right node
                    min = rc;
                else // right node is greater than left node
                    min = lc;
            }
            else // only left child exists
                min = lc;

            if (h->H[parent].wt > h->H[min].wt)
            {
                swap(&h->H[parent], &h->H[min]);
                parent = min;
            }
            else
                return;
        }
        else // neither left nor right child exists
            return;
    }
    return;
}

void killHeap(heap *h)
{
    free(h->H);
    h->size = -1;
    h->length = 0;
    free(h);
    return;
}

// GRAPH FUNCTIONS
// DEFINATIONS
bool isGraphValid(graph *gptr)
{
	if(!gptr || !gptr->space)
		return false;
	return true;
}

bool isVertexValid(graph *gptr, int vertex)
{
	if(!isGraphValid(gptr))
		return false;
	else if(0 <= vertex && vertex < gptr->vertexCnt)
		return true;
	return false;
}

node *getNode(int vertex, int weight, void *payload)
{
	node *newNode = NULL;
	if(!(newNode = (node *)malloc(sizeof(node))));
	else
	{
		newNode->vertex = vertex;
		newNode->weight = weight;
		newNode->payload = payload;
		newNode->next = NULL;
	}
	return newNode;
}

graph *initGraph(void)
{
	graph *tmp=NULL;
	if(!(tmp = (graph*)malloc(sizeof(graph))))
		return NULL;
	
	tmp->space=NULL;
	
	tmp->vertexCnt = 0;
	tmp->edgeCnt = 0;
	return tmp;
}

bool deinitGraph(graph *gptr)
{
	if(!isGraphValid(gptr))
		return true;
	if(deinitGraphSpace(gptr))
	{
		free(gptr);
		return true;
	}
	return false;
}

bool deinitGraphSpace(graph *gptr)
{
	if(!gptr)
		return false;
	node *ptr=NULL, *tmp=NULL;
	
	for(int i=0;i<gptr->vertexCnt; i++)
	{
		ptr = gptr->space[i];
		while(ptr)
		{
			tmp = ptr;
			ptr = ptr->next;
			free(tmp);
		}
	}
	free(gptr->space);
	return true;
}

void initGraphSpace(graph *gptr, char *filename)
{
	if(!gptr)
		return ;
	FILE *fh = fopen(filename, "r");
	fscanf(fh, "%d", &(gptr->vertexCnt));
	int tmpVar = 0, edgeCnt = 0;
	if(!(gptr->space = (node **)malloc(sizeof(node *) * gptr->vertexCnt)))
			return ;
	for(int i = 0; i < gptr->vertexCnt; i++)
		gptr->space[i] = NULL;
	
	for(int i=0; i < gptr->vertexCnt; i++)
	{
		for(int j = 0; j < gptr->vertexCnt; j++)
		{
			fscanf(fh, "%d", &tmpVar);
			if(tmpVar)
			{
				edgeCnt++;
				node* newNode = getNode(j, tmpVar, NULL);
				newNode->next = gptr->space[i];
				gptr->space[i] = newNode;
			}
		}
	}
	gptr->edgeCnt = edgeCnt;
	fclose(fh);		
	return ;
}

void displayMatrix(graph *gptr)
{
	if(!isGraphValid(gptr))
		return ;

	node *tptr=NULL;
	int **matrix = NULL;
	
	if(!(matrix = (int **)malloc(sizeof(int*)* gptr->vertexCnt)))
		return ;
	for(int i = 0; i<gptr->vertexCnt; i++){
		if(!(matrix[i] = (int*)calloc(gptr->vertexCnt, sizeof(int )))){
			for(int j = 0; j<i;j++)
				free(matrix[j]);
			free(matrix);
			return ;
		}
	}

	for(int i=0;i<gptr->vertexCnt;i++)
	{
		tptr = gptr->space[i];
		while(tptr)
		{
			matrix[i][tptr->vertex] = tptr->weight;
			tptr = tptr->next;
		}
	}

	for(int j=0;j<gptr->vertexCnt;j++)
	{
		for(int k=0;k<gptr->vertexCnt;k++)
			printf("%5d ", matrix[j][k] );
		printf("\n");
	}
	for(int i=0;i<gptr->vertexCnt;i++)
		free(matrix[i]);
	free(matrix);
	printf("\n\n");
	return ;
}

int inDegree(graph *gptr, int vertex)
{
	int inDeg=0;
	if(!isGraphValid(gptr) || !isVertexValid(gptr, vertex));
	else
	{
		node *tptr = NULL;
		for(int i=0;i<gptr->vertexCnt;i++)
		{
			tptr = gptr->space[i];
			while(tptr)
			{
				if(tptr->vertex == vertex)
					inDeg++;
				tptr = tptr->next;
			}
		}
	}

	return inDeg;
}

int outDegree(graph *gptr, int vertex)
{
	int outDeg = 0;
	if(!isGraphValid(gptr) || !isVertexValid(gptr, vertex));
	else
	{
		node *tptr=NULL;
		tptr=gptr->space[vertex];
		while(tptr)
		{
			outDeg++;
			tptr = tptr->next;
		}
	}
	return outDeg;
}

int getConnectedVertices(graph *gptr, int vertex)
{
	if(!isGraphValid(gptr) || !isVertexValid(gptr, vertex))
		return 0;
	if(isDirected(gptr))
		return inDegree(gptr, vertex) + outDegree(gptr, vertex);
	return outDegree(gptr, vertex);
}

bool isDirected(graph *gptr)
{
	if(!isGraphValid(gptr))
		return false;
	node *pptr = NULL, *tptr = NULL;
	for(int i=0; i<gptr->vertexCnt; i++)
	{
		pptr=gptr->space[i];
		while(pptr)
		{
			tptr=gptr->space[pptr->vertex];
			while(tptr)
			{
				if(tptr->vertex == i)
					break;
				tptr=tptr->next;
			}
			if(!tptr)
				return true;
			pptr=pptr->next;
		}
	}
	return false;
}
// TRAVERSALS

void BreadthFirstSearch(graph *gptr, int start)
{
	if(!isGraphValid(gptr) || !isVertexValid(gptr, start))
		return;

	int x, *visited = NULL;
	node *nptr = NULL;
	if(!(visited = (int*)calloc(gptr->vertexCnt, sizeof(int))))
		return ;
	enqueue(start);
	visited[start] = 1;
	while(!isEmptyQ())
	{
		x = dequeue();
		printf("%5d ", x);
		nptr = gptr->space[x];
		while(nptr)
		{
			if(!visited[nptr->vertex])
			{
				visited[nptr->vertex] = 1;
				enqueue(nptr->vertex);
			}
			nptr = nptr->next;
		}

	}
	printf("\n\n");
	free(visited);
	destroyQ();
	return ;
}

void DepthFirstSearch(graph *gptr, int start)
{
	if(!isGraphValid(gptr) || !isVertexValid(gptr, start))
		return ;
	int x, *visited = NULL;
	node *nptr = NULL;
	if(!(visited = (int*)calloc(gptr->vertexCnt, sizeof(int))))
		return ;
	push(top, start);
	visited[start] = 1;

	while(!isEmptyStk(top))
	{
		x = pop(top);
		nptr = gptr->space[x];
		printf("%5d ", x);
		while(nptr)
		{
			if(!visited[nptr->vertex])
			{
				push(top, nptr->vertex);
				visited[nptr->vertex] = 1;
			}
			nptr= nptr->next;
		}
	}
	printf("\n\n");
	KillStack(top);
	free(visited);
	return ;
}

// DRIVER
int main(int argc,char **argv)
{
	char *filename =argv[1]; 
	graph *g=NULL;
	g = initGraph();
	initGraphSpace(g, filename);
	printf("Get Connected Vertices : %d\n", getConnectedVertices(g, 1));
	printf("In Degree : %d\n", inDegree(g, 1));
	printf("Out Degree : %d\n", outDegree(g, 1));
	printf("Is Graph Valid : %d\n", isGraphValid(g));
	printf("Is Vertex Valid : %d\n", isVertexValid(g, 123));
	printf("Is Graph Directed : %d\n", isDirected(g));
	displayMatrix(g);
	BreadthFirstSearch(g, 0);
	DepthFirstSearch(g, 0);
	deinitGraph(g);
	return 0;
}
