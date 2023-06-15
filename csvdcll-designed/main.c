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
#define STRSIZE 1024

char legends[STRSIZE];

record *get_record(char *, unsigned int, float);
node *get_node(record *, unsigned int key); 
bool swap_record(node *, node *);
bool print_record(record *);

bool readcsv(list *, const char *);
bool writecsv(list *, const char *);

int main(const int argc, const char *argv[])
{
	list *base = NULL;
	base = init_list();
	readcsv(base, "data.csv");
	writecsv(base, "result.csv");
	delete_list(base);
	return 0;
}

bool swap_record(node *xnptr, node *ynptr)
{
	bool flag = false;
	node *tnptr;
	int tkey;
	if(xnptr && ynptr)
	{
		tnptr = xnptr->student;
		tkey = xnptr->key;

		xnptr->student = ynptr->student;
		ynptr->student = tnptr;

		xnptr->key = ynptr->key;
		ynptr->key = tkey;

		flag = true;
	}
	return flag;
}

bool print_record(record *rptr)
{
	bool flag = false;
	if(rptr)
	{
		printf("NAME	: %s\n", rptr->name);
		printf("MIS	: %u\n", rptr->mis); 
		printf("SCORE	: %3.2f\n", rptr->score);
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
	extern char legends[];
	unsigned int key;
	char strbuf[STRSIZE];
	char *name;
	float score;
	bool flag;
	FILE *fh = NULL;
	record *recptr = NULL;
	node *nodeptr = NULL;

	flag = false;
	if(lptr && (fh = fopen(filename, "r")))
	{
		fscanf(fh, "%s", legends); 
		while(fscanf(fh, "%s", strbuf) != EOF)
		{
			name = strtok(strbuf, ",");
			key = atoi(strtok(NULL, ","));
			score = atof(strtok(NULL, ","));

			recptr = get_record(name, key, score);
			nodeptr = get_node(recptr, key);
			lptr = append(lptr, nodeptr);
		}
		flag = true;
		fclose(fh);
	}
	return flag;
}

bool writecsv(list *lptr, const char *filename)
{
	bool flag = false;
	extern char legends[];
	char strbuf[STRSIZE], *cptr = NULL;
	node *nodeptr = NULL;
	record *recptr = NULL;
	FILE *fh = NULL;

	if(lptr && (fh = fopen(filename, "w")))
	{
		nodeptr = lptr->head;
		fprintf(fh, "%s\n", legends);

		if(nodeptr)
		{
			do
			{
				recptr = nodeptr->student;
				sprintf(strbuf,"%s,%d,%.2f\n",recptr->name,recptr->mis,recptr->score);
				fprintf(fh, "%s", strbuf);

				nodeptr = nodeptr->next;
			}while(nodeptr != lptr->head);
		}

		flag = true;
		fclose(fh);
	}
	return flag;
}
