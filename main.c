/*
   Write a program that Reads a CSV file with columns Name, MISID, Marks.
   Creates a doubly circular linked list of all the entries from the file.
   Then sorts this doubly linked list on MISID.
   Then Reads another CSV file with same columns,
   and inserts the entries from the second CSV file into the doubly linked
   list in Sorted order.
   The code should be properly divided into functions and a DCLL data type.
   */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"dcll.h"


record *get_record(char *, unsigned int, float);
bool print_record(record *);
node *get_node(record *, unsigned int key); 

bool readcsv(list *, const char *);

int main(const int argc, const char *argv[])
{
	list *base = NULL;
	base = init_list();

	return 0;
}

bool print_record(record *rptr)
{
	bool flag = false;
	if(rptr)
	{
		printf("%64s\n", rptr->name);
		printf("%10u\n", rptr->mis); 
		printf("%3.2f\n", rptr->score);
		flag = true;
	}
	return flag;
}

record *get_record(char *str, unsigned int mis, float score)
{
	record *newrec = NULL;
	if((newrec = (record*)malloc(sizeof(record))))
	{
		strcpy(newrec->name, str);
		newrec->mis = mis;
		newrec->score = score;
	}
	return newrec;
}

node *get_node(record *student, unsigned int key) 
{
	node *newnode = NULL;
	if((newnode = (node*)malloc(sizeof(node))))
	{
		newnode->student = student;
		newnode->key = key;
		newnode->prev = newnode->next = NULL;
	}
	return newnode;
}

bool readcsv(list *lptr, const char *filename)
{
	unsigned int key;
	char strbuf[1024];
	bool flag;
	FILE *fh = NULL;
	record *recptr = NULL;
	node *nodeptr = NULL;

	flag = false;
	if((fh = fopen(filename, "r")))
	{
		fscanf(fh, "%s", strbuf); 
		while(fscanf(fh, "%s", strbuf) != EOF)
		{
			recptr = get_record(strtok(strbuf, ", "),
					(key = atoi(strtok(NULL, ","))),
					atof(strtok(NULL, ",")));
			nodeptr = get_node(recptr, key);
		}
		flag = true;
	}
	return flag;
}

