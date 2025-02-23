/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Yaire Aguilar
 * Email: aguilary@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct properties{
	void * value;
	int priority;
};
struct pq{
	struct dynarray* array;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* p_queue = malloc(sizeof(struct pq));
	p_queue->array = dynarray_create();
	return p_queue;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	if (pq != NULL){
	dynarray_free(pq->array);
	free(pq);
	}
}
/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise...
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	if(dynarray_size(pq->array) == 0){	
		return 1;
	}
	else return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

//helper function for pq_insert
//essentially we will sawp the parent and curr 
//later be called when parent does have a greater priority than curr
void reorder(struct pq* pq, int parent, int current){
	struct properties* temp;
	struct properties* temp_2;

	temp = dynarray_get(pq->array, parent);
    temp_2 = dynarray_get(pq->array, current);

	dynarray_set(pq->array, parent, temp_2);
    dynarray_set(pq->array, current, temp);
}

void pq_insert(struct pq* pq, void* value, int priority) {
	struct properties* element = malloc(sizeof(struct properties));
	element->value = value;
	element->priority = priority;
	dynarray_insert(pq->array, element); 	//put what we got into the priority queue


	//make our indexes to compare
	int curr_index = dynarray_size(pq->array) - 1;
	int parent_index = (curr_index - 1) / 2;

	while (curr_index != 0){
		struct properties* parent = dynarray_get(pq->array, parent_index);
		struct properties* curr = dynarray_get(pq->array, curr_index);

		//were gonna compare to see if the parent priority is greater
		if (parent->priority > curr->priority){
			reorder(pq, parent_index, curr_index);
		}
		//after all this we need to fix our indexes
		curr_index = parent_index;
		parent_index = (curr_index - 1) / 2;
	}
	//Note: This function needs to be O(logn)
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	struct properties* element = dynarray_get(pq->array, 0);
	return element->value;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	struct properties* element = dynarray_get(pq->array, 0);
	return element->priority;


	//Note: This function needs to be O(1)
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

//helper function for pq_remove_first
void percolate(struct pq* pq, int index)
{
	//the indexes of each children below it
	int C_left = (index * 2) + 1; 
    int C_right = (index * 2) + 2; 
    int min_priority = index;

	// check if left child index is valid
    if (C_left < dynarray_size(pq->array)) { 
        struct properties* leftElement = dynarray_get(pq->array, C_left);
        struct properties* minElement = dynarray_get(pq->array, min_priority);

        if (leftElement->priority < minElement->priority) {
            min_priority = C_left;
        }
    }
	
// check if right child index is valid too
    if (C_right < dynarray_size(pq->array)) { 
        struct properties* rightElement = dynarray_get(pq->array, C_right);
        struct properties* minElement = dynarray_get(pq->array, min_priority);

        if (rightElement->priority < minElement->priority) {
            min_priority = C_right;
        }
    }

// reorder if there was a change in minimum priority
    if (min_priority != index) { 
        reorder(pq, index, min_priority);
        percolate(pq, min_priority); //continue down with reccur
    }
}

void* pq_remove_first(struct pq* pq)
{
	if (pq != NULL && pq->array != NULL && dynarray_size(pq->array) > 0) { // Check for valid pq and non-empty array
        int lastChild = dynarray_size(pq->array) - 1;
        struct properties* firstElementVal = dynarray_get(pq->array, 0);
        void* firstValue = firstElementVal->value; // Save value before freeing the element

        struct properties* lastElementVal = dynarray_get(pq->array, lastChild);

        dynarray_set(pq->array, 0, lastElementVal);
        dynarray_remove(pq->array, lastChild);
    	percolate(pq, 0);

        free(firstElementVal); // Free the element after retrieving the value

        return firstValue;
    }
    return NULL; // Return NULL if pq is NULL, pq->array is NULL, or pq->array is empty
}
