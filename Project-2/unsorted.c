/*
 * Jillian Coveney
 * Coen 12 Project 2
 * W 2:15
 * unsorted.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

struct set{
	int count; 	//number of elements in array
	int length;	//max length of array
	char** data;	//address of char in array
};

typedef struct set SET;

static int search(SET *sp, char *elt);

SET *createSet(int maxElts){	//create a set
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);	//assert the set and check that pointer exists
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);	//assert the chars
	return sp;
}
void destroySet(SET *sp){	//destroy the set: O(n)
	int i;
	assert(sp != NULL);
	for(i = 0; i < sp->count; i++){
		free(sp->data[i]);	//free every string in the set
	}
	free(sp->data);		//free char pointer
	free(sp);		//free the entire set
	return;
}
int numElements(SET *sp){	//returns the number of elements in the set: O(1)
	assert(sp != NULL);
	return sp->count;
}
void addElement(SET *sp, char *elt){	//insert a new element into the set: O(1)
	assert((sp != NULL) && (elt != NULL) && (sp->length > sp->count));;	//count must be smaller than size of array
	int position = search(sp, elt);
	char * newElt;
	if(position < 0){	//allocates memory for element if it is a unique word in the set
		newElt = strdup(elt);
		sp->data[sp->count++] = newElt;	//allocates memory in the last spot in count
	}
	return;
}
void removeElement(SET *sp, char *elt){  //delete an element from the set: O(n)
	assert(sp != NULL && elt != NULL);	
	int position = search(sp, elt);		//find the index of target element
	if(position != -1){
		free(sp->data[position]);
		sp->data[position] = sp->data[--sp->count];	//move last element to index of deleted element
	}
	return;
}
char *findElement(SET *sp, char *elt){	 //search for an element in the set: O(n)
	assert(sp != NULL && elt != NULL);
	int position = search(sp, elt);
	if(position < 0){
		return NULL;	//returns NULL if no element found
	}
	return sp->data[position];	//returns found element
}
char **getElements(SET *sp){	//allocate memory for and return an array of elements in the set pointed to by a pointer: O(n)
	assert(sp != NULL);
	char** dataCopy = malloc(sizeof(char*) * sp->length);
	assert(dataCopy != NULL);
	int i;
	for(i = 0; i < sp->count; i++)
		dataCopy[i] = sp->data[i];	//copy elements from original data
	return dataCopy;
}
static int search(SET *sp, char *elt){		//returns location of an element within the array: O(n)
	assert(sp !=NULL && elt != NULL);
	int i; 
	for(i = 0; i < sp->count; i++){
		if (strcmp(sp->data[i], elt) == 0)	//returns position if found
			return i;
	}
	return -1;	//element not found
}

