/* 
 * Jillian Coveney
 * COEN 12
 * Term Project
 * MWF 11:45am 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct node{
	void **data;
	int first;
	int qCount;	//total count of all elts in specific queue
	int length;
	struct node *next, *prev;
}NODE;

typedef struct list{
	int listCount;	//total count of all elts in list
	NODE *head, *tail;
}LIST;

NODE *addNode(int length);

//creates the list by allocating memory for the structure with head and tail pointer: O(1)
LIST *createList(void){
	LIST *lp = malloc(sizeof(LIST));
	lp->head = lp->tail = addNode(10);	//create first head node with array size 10
	lp->listCount = 0;
	return lp;
}
//traverse the list structure and free the data from each node, then free the node pointer and the list pointer: O(n)
void destroyList(LIST *lp){
	assert(lp != NULL);
	NODE *pDel, *pNext;
	pNext = lp->head;
	while(pNext != NULL){
		pDel = pNext;
		pNext = pDel->next;
		free(pDel->data); //void ptr..what should i free??
		free(pDel);	//freeing the 
	}
	free(lp);
}
//return the total number of items in the list: O(1)
int numItems(LIST *lp){
	assert(lp != NULL);
	return (lp->listCount);
}
//add an item to the front of the list: O(1)
void addFirst(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	if(lp->head->qCount ==  lp->head->length){	//if the first node is full, then create a new node before it 
		NODE *new = addNode(lp->head->length*2);
		new->next = lp->head;	//put the new node before the head
		lp->head->prev = new;
		lp->head = new;
	}
	int index = ((lp->head->first + lp->head->length-1) % lp->head->length);
	lp->head->data[index] = item;
	lp->head->first = index;
	lp->head->qCount++;
	lp->listCount++;
}
//add an item to the last spot in the list: O(1)
void addLast(LIST *lp, void *item){
	assert(lp != NULL && item != NULL);
	if(lp->tail->qCount == lp->tail->length){	//if the last node is full, then create a new node with 2x length
		NODE *new = addNode(lp->tail->length*2);
		new->prev = lp->tail;
		lp->tail->next = new;
		lp->tail = new;;
	}
	int index = ((lp->tail->first + lp->tail->qCount) % lp->tail->length); //index of where last item should go
	lp->tail->data[index] = item;
	lp->tail->qCount++;
	lp->listCount++;
}
//remove the first item in the list: O(1)
void *removeFirst(LIST *lp){
	assert(lp != NULL);
	if(lp->head->qCount == 0){	//if the array is empty, the free the node and data
		NODE *pDel = lp->head;
		lp->head = lp->head->next;
		free(pDel->data);
		free(pDel);
		lp->head->prev = NULL;
	}
	int index = lp->head->first;
	int nextIndex = (index + 1) % lp->head->length;	//save the index of the next elt
	lp->head->first = nextIndex;			//make first point to the next elt
	void *copy = lp->head->data[index];
	lp->head->qCount--;
	lp->listCount--;
	return copy;
}
//remove the last item in the list: O(1)
void *removeLast(LIST *lp){
	assert(lp != NULL);
	if(lp->tail->qCount == 0){	//if the array is empty, then free the node and data
		NODE * pDel = lp->tail;
		lp->tail = lp->tail->prev;
		lp->tail->next = NULL;
		free(pDel->data);
		free(pDel);
	}
	int index = ((lp->tail->first + lp->tail->qCount) & lp->tail->length);	//index for the last item
	void *copy = lp->tail->data[index];
	lp->tail->qCount--;
	lp->listCount--;
	return copy;
}
//check that index is correct and returns a copy of the of the node at the given index: O(logn)
void *getItem(LIST *lp, int index){
	assert(lp != NULL);
	assert(index > -1 && index < lp->listCount);
	NODE* np = lp->head;
	while(index >= np->qCount){	//traverse the list and decrement index if greater than qCount
		index -= np->qCount;
		np = np->next;
	}
	void *copy = np->data[(np->first + index) % np->length];
	return copy;
}
//check that the index is correct and then updates the item at the index: O(logn)
void setItem(LIST *lp, int index, void *item){
	assert(lp != NULL && item != NULL);
	assert(index > -1  && index < lp->listCount);	
	NODE *np = lp->head;
	while(index >= np->qCount){	//traverse the list and decrement index if greater than qCount
		index -= np->qCount;
		np = np->next;
	}
	int i = ((np->first + index) % np->length);
	np->data[i] = item;
}
//allocates memory for a new node with a circular queue array: O(1)
NODE *addNode(int length){
	NODE *np = malloc(sizeof(NODE));
	assert(np != NULL);
	np->data = malloc(sizeof(void**) *length);
	np->first = 0;	
	np->qCount = 0;
	np->length = length;
	np->next = NULL;
	np->prev = NULL;
	return np;
}

