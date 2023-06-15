#include<stdbool.h>

typedef struct{
	char name[128];
	unsigned int mis;
	float score;
}record;

typedef struct node{
	unsigned int key;
	record *student;
	struct node *prev, *next;
}node;

typedef struct list{
	node *head;
	unsigned int size;
}list;

list *init_list(void);
void traverse(list *);
void rTraverse(list *);
list *push(list *, node *);
list *append(list *, node *);
list *insert(list *, int, node *);
record *pop(list *);
record *Remove(list *, int);
list *merge(list *, list *);
list *merge_sort(list *);
void delete_list(list *);
bool print_record(record *);
