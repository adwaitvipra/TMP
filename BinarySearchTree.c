/*
 * BST TO STORING PERSONAL INFORMATION 
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

typedef struct
{
	unsigned long int UID;
	char NAME[256];
	char SEX;
	char DOB[9]; //DDMMYYYY\0 
	unsigned long int CONTACT;
	char ADDRESS[1024];
}payload;


typedef struct Node
{
	int key;
	payload *person;
	struct Node *leftChild;
	struct Node *rightChild;
}node;

typedef struct
{
	node *root;
	int size;
}database;

//DECLARATIONS

database *initDatabase(void);
node *getNode(const int,const payload *)
payload *initPerson(const int, const char *, const char, const char *, const unsigned long int, const char *);

//DEFINATIONS
database *initDatabase(void)
{
	database *newDB=NULL;
	if(!(newDB = (database *)malloc(sizeof(database))))
		return NULL;

	newDB->root = NULL;
	newDB->size = 0;

	return newDB;
}

node *getNode(const int key, const payload *person)
{
	node *newNode=NULL;

	if(!(newNode = (node *)malloc(sizeof(node))))
		return NULL;

	newNode->key = key;
	newNode->person = person;
	newNode->leftChild = newNode->rightChild = NULL;

	return newNode;
}

payload *initPerson(const int uid, const char *name, const char sex, const char *DOB,const unsigned long int contact, const char *addr)
{
	payload *newPerson=NULL;

	if(!(newPerson = (payload*)malloc(sizeof(payload))))
		return NULL;

	newPerson->UID = uid;
	strcpy(newPerson->NAME, name);
	newPerson->SEX = sex;
	strcpy(newPerson->DOB, DOB);
	newPerson->CONTACT = contact;
	strcpy(newPerson->ADDRESS, addr);

	return newPerson;
}

