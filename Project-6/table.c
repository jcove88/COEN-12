/*
 * Jillian Coveney
 * Coen 12 
 * W 2:15
 * Lab 6: Quick Sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <stdbool.h>
#include <assert.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

struct set
{
	int count;	//total elements 
	int length;	//length 
	void **data;	//data
	char *flags;	//array of flags for data
	int (*compare)();	//compare two elements
	unsigned(*hash)();
};

static int search(SET *sp, void *elt, bool *found);
static void quicksort(SET *sp, void **dataCopy, int lo, int hi);
static int partition(SET *sp, void **dataCopy, int lo, int hi);

//create a hashtable with an identifier array: O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned (*hash)())
{
	SET *sp;
	int i;
	sp = (SET*)malloc(sizeof(SET));	//create set pointer
	assert(sp != NULL);
	
	sp->count = 0;			//count is 0
	sp->length = maxElts;		//length is max number of elements
	sp->compare = compare;
	sp->hash = hash;

	sp->flags = malloc(sizeof(char)*maxElts);	//allocate array of flags
	assert(sp->flags != NULL);

	sp->data = malloc(sizeof(void *)*maxElts);	//allocate array of data
	assert(sp->data != NULL);
	
	for(i = 0; i < maxElts; i++)			//assign each data an 'E' flag for empty 
		sp->flags[i] = 'E';
	return sp;
}
//free data point, array and hashtable: O(n)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	free(sp->data);		//free data
	free(sp->flags);	//free flags
	free(sp);		//free set
	return;
}
//return the number of elements in set: O(1)
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}
//add a new element to set, increase count, change flag to F: O(1) average O(n) worst case
void addElement(SET *sp, void *elt)
{
	assert((sp != NULL) && (elt != NULL));
	bool found;
	int index = search(sp, elt, &found);
	if(!found)				//add element if it doesn't exist
	{	
		sp->data[index] = elt;
		sp->flags[index] = 'F';		//change flag to 'F' for filled
		sp->count++;
	}
	return;
}
//remove an element from set, decrease count, change flag to D: O(1) average O(n) worst case
void removeElement(SET *sp, void *elt)
{
	assert((sp != NULL) && (elt != NULL));
	bool found;
	int index = search(sp, elt, &found);	//search for element
	if(found)				//if the element is found, delete and set flag to 'D'
	{
		sp->flags[index] = 'D';
		sp->count--;
	}
	return;
}
//find and return a pointer to an element in set, if not found return NULL: O(1) average O(n) worst case
void *findElement(SET *sp, void *elt)
{
	assert((sp != NULL) && (elt != NULL));
	bool found;
	int index = search(sp, elt, &found);
	if(!found)
	{
		return NULL;
	}
	return sp->data[index];
}
//return a copy of elements in set: O(n)
void *getElements(SET *sp)
{
	assert(sp != NULL);
	void **dataCopy;
	dataCopy = malloc(sizeof(void *)*sp->count);
	assert(dataCopy != NULL);
	int i;
	int j = 0;
	for(i = 0, j = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == 'F')
		{
			dataCopy[j++] = sp->data[i];
		}
	}
	quicksort(sp, dataCopy, 0, sp->count-1); //calls quicksort for the copied array
	return dataCopy;
}
//search for element in set using hash function, linear probing: O(1) average O(n) worst case
static int search(SET *sp, void *elt, bool *found)
{
	assert((sp != NULL) && (elt != NULL));
	int index = (*sp->hash)(elt) % sp->length;
	int deleted = -1;
	int position;
	int i = 0;
	while(i < sp->length)
	{
		position = (index + i) % (sp->length);
		if(sp->flags[position] == 'D')
		{
			if(deleted == -1)	//save first deleted location, otherwise keep searching
				deleted = position;
		}
		else if(sp->flags[position] == 'E')	//stop searching
		{
			*found = false;
			if(deleted == -1)	//return the position of the deleted index 
				return position;
			return deleted;
		}
		else if((*sp->compare)(sp->data[position], elt) == 0)	//element found
		{
			*found = true;
			return position;				//return index
		}
		i++;
	}
	*found = false;
	return deleted;		//return the index of where the element would be inserted
}
//partition into sub arrays: O(n)
static int partition(SET *sp, void **dataCopy, int lo, int hi)
{
	assert(sp != NULL);
	void *pivot = dataCopy[hi];
	int smaller = lo -1;	//index of smaller elt
	int i;
	for(i = lo; i <= hi -1; i++){
		if((*sp->compare)(dataCopy[i], pivot) <= 0){ 	//swap if the elt is less than or equal to pivot
			smaller++;	//increment index
			void *temp = dataCopy[smaller];
			dataCopy[smaller] = dataCopy[i];
			dataCopy[i] = temp;
		}
	}
	void *swap = dataCopy[smaller + 1];	//swap next element from smaller and return the index
	dataCopy[smaller + 1] = dataCopy[hi];
	dataCopy[hi] = swap;
	return smaller + 1;	
}
//function for quicksort: O(n)
static void quicksort(SET *sp, void **dataCopy, int lo, int hi)
{
	assert(sp != NULL);
	if(lo < hi){
		int pIndex = partition(sp, dataCopy, lo, hi);
		quicksort(sp, dataCopy, lo, pIndex - 1);	//array is divided so one is lower than the partition index and another is higher. Now recursiviley partition the two arrays
		quicksort(sp, dataCopy, pIndex + 1, hi); 
	}
	return;
}
