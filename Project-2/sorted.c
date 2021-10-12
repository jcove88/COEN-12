/*
 * Jillian Coveney
 * Coen 12 Project 2
 * W 2:15
 * sorted.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<stdbool.h>
#include "set.h"

struct set{
	int count;	//number of elements in array
	int length;	//max length of array
	char** data;	//address of char in array
};

typedef struct set SET;

static int search(SET *sp, char *elt, bool *found);

SET *createSet (int maxElts){ 	//create a set
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);	//assert the set and check that pointer exists
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*) * maxElts);
	assert(sp->data != NULL);	//assert the chars
	return sp;
}
void destroySet(SET *sp){	//destroy the set: O(n)
	assert(sp != NULL);
	int i;
	for(i = 0; i < sp->count; i++)
		free(sp->data[i]);	//free every string in the set
	free(sp->data);		//free char pointer
	free(sp); 		//free the entire set
	return;
}
int numElements(SET *sp){	//returns the number of elements in the set: O(1)
 	assert(sp != NULL);
	return sp->count;
}
void addElement(SET *sp, char *elt){	//insert a new element into the set: O(n)
	assert((elt != NULL)  && (sp != NULL) && (sp->length > sp->count));	//count must be smaller than size of array
	char * newElt;
	int position;
	int i;
	bool found;
	position = search(sp, elt, &found);
	if(!found)	//if not found then add
	{
		newElt = strdup(elt); 		//ensures the element has memory and allocates memory with malloc; duplicates the string and returns a pointer
		assert(newElt != NULL);	
		for(i = sp->count; i > position; i--)
			sp->data[i] = sp->data[i-1];	//shift the elements down to make room
		sp->data[position] = newElt;		//add element
		sp->count++;	//increment counter
	}
	return;
}
void removeElement(SET *sp, char *elt){		//delete an element from the set: O(n)
	assert((sp != NULL) && (elt != NULL));
	int position;
	int i;
	bool found;
	position = search(sp, elt, &found);	//find the index of the element to remove
	if(found){
		free(sp->data[position]);
		for(i = position+1; i < sp->count; i++)		//shift the elements up to close the gap
			sp->data[i-1] = sp->data[i];
		sp->count--;	//decrease counter
	}
	return;
}
char *findElement(SET *sp, char *elt){	//search for an element in the set: O(logn)
	assert((sp != NULL) && (elt != NULL));
	int position;
	bool found;
	position = search(sp, elt, &found);
	if(!found)
	{
		return NULL;
	}
	return sp->data[position];
}
char **getElements(SET *sp){	//allocate memory for and return an array of elements in the set pointed to by a pointer: O(n)
	assert(sp != NULL);
	char** dataCopy;
	dataCopy = malloc(sizeof(char *) * sp->length);
	assert(dataCopy != NULL);
	int i;
	for(i = 0; i < sp->count; i++)
	{
		dataCopy[i] = sp->data[i];
	}
	return dataCopy;
}
static int search(SET *sp, char *elt, bool *found){	//returns the location of an element within the array: O(logn)
	int lo, hi, mid, diff;
	lo = 0;
	hi = sp->count - 1;	//set high value equal to the max index
	while(lo <= hi)
	{
		mid = (lo + hi)/2;
		diff = strcmp(elt, sp->data[mid]);
		if(diff < 0)		//if the element is less than 0 sets new high value to look at lower half of data
		{
			hi = mid - 1;
		}
		else if(diff > 0)	//if the element is more than 0 sets new low value to look at higher half of data
		{
			lo = mid + 1;
		}
		else			//sets found to true and returns the index of the element
		{
			*found = true;	
			return mid;
		}
	}
	*found = false;		//if its not found then it will return the index where insertion should start
	return lo;
}
