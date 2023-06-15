/*
 * Doubly Circular Linked List
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"dcll.h"
#define DCLL list

//INIT
DCLL *init_list(void)
{
	DCLL *metadata = NULL;
	if((metadata = (DCLL *)malloc(sizeof(DCLL))))
	{
		metadata->size = 0;
		metadata->head = NULL;
	}
	return metadata;
}

//TRAVERSE

void traverse(DCLL *hptr)
{
	if(!hptr || !hptr->size)
	{
		printf("%p\n", NULL);
		return ;
	}
	node *ptr=NULL;
	ptr = hptr->head;
	do
	{
		print_record(ptr->student);
		ptr=ptr->next;
	}while(ptr != hptr->head);
	printf("\n");
	return;
}

void rTraverse(DCLL *hptr)
{
	if(!hptr || !hptr->size)
		return ;
	node *ptr=NULL;
	ptr = hptr->head->prev;
	do{
		print_record(ptr->student);
		ptr = ptr->prev;
	}while(ptr != hptr->head);
	return ;
}

//INSERT
DCLL *push(DCLL *hptr, node *newNode)
{
	if(!hptr)
		hptr = init_list();
	if(!hptr->head)
	{
		newNode->next = newNode;
		newNode->prev = newNode;
	}
	else
	{
		if(hptr->size==1)
		{
			newNode->next = hptr->head;
			newNode->prev = hptr->head;
			hptr->head->next = newNode;
			hptr->head->prev = newNode;	
		}
		else
		{
			newNode->next = hptr->head;
			newNode->prev = hptr->head->prev;
			hptr->head->prev->next = newNode;
			hptr->head->prev = newNode;
		}
	}
	hptr->size++;		
	hptr->head = newNode;
	return hptr;
}

DCLL *append(DCLL *hptr, node *newNode)
{
	if(!hptr)
		hptr=init_list();
	if(!hptr->head)
	{
		newNode->next = newNode->prev = newNode;
		hptr->head = newNode;
	}
	else
	{
		if(hptr->size==1)
		{
			newNode->prev = hptr->head;
			hptr->head->next = newNode;
			newNode->next = hptr->head;
			hptr->head->prev = newNode;
		}
		else
		{
			newNode->prev = hptr->head->prev;
			newNode->next = hptr->head;
			newNode->prev->next = newNode;
			hptr->head->prev = newNode;
		}
	}
	hptr->size++;
	return hptr;
}

DCLL *insert(DCLL *hptr, int idx, node *newNode)
{
	if(idx<0 || idx>hptr->size)
		return hptr;
	if(!idx)
		hptr = push(hptr, newNode);
	else if(idx == hptr->size)
		hptr = append(hptr, newNode);
	else
	{
		node *tmp = NULL;
		tmp = hptr->head;

		for(int i=0; tmp && i<idx-1;i++)
			tmp = tmp->next;
		newNode->prev = tmp;
		newNode->next = tmp->next;
		newNode->next->prev = newNode;
		tmp->next = newNode;

		hptr->size++;
	}
	return hptr;
}

//DELETE
record *pop(DCLL *hptr)
{
	record *rptr = NULL;
	if(!hptr || !hptr->size)
		return rptr;
	else if(hptr->size==1)
	{
		rptr = hptr->head->student;
		free(hptr->head);
		hptr->head = NULL;
	}
	else
	{
		node *tmp = hptr->head;
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		hptr->head = tmp->next;
		rptr = tmp->student;
		free(tmp);
	}
	hptr->size--;

	return rptr;
}

record *Remove(DCLL *hptr, int idx)
{
	record *rptr = NULL;
	if(!hptr || !hptr->size)
		return rptr;
	if(idx<0 || idx>=hptr->size)
		return rptr;
	if(!idx)
		rptr = pop(hptr);
	else
	{
		node *tmp = NULL;
		tmp = hptr->head;

		for(int i=0;i<idx;i++)
			tmp = tmp->next;

		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		rptr = tmp->student;
		free(tmp);
		hptr->size--;
	}
	return rptr;

}

void delete_list(DCLL *hptr)
{
	if(!hptr)
		return;
	node *tmp = NULL;
	node *ptr=NULL;
	hptr->head->prev->next = NULL;
	ptr= hptr->head;
	while(ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp->student);
		free(tmp);
	}
	free(hptr);
	return ;
}

//MERGE

DCLL *merge(DCLL *xlptr, DCLL *ylptr)
{
	DCLL *nlptr = NULL;

	if(xlptr || ylptr)
	{
		if(!xlptr)
			return ylptr;
		if(!ylptr)
			return xlptr;
		if((nlptr = (DCLL *)malloc(sizeof(DCLL))))
		{

		}
	}
}
