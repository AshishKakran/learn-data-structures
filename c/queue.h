/* This header file exposes a queue ADT */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//Queue ADT type declarations

typedef struct node
{
	void* dataPtr;
	struct node* next;
}QUEUE_NODE;

typedef struct
{
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
	int count;
}QUEUE;

//prototype declarations
QUEUE* createQueue(void);
QUEUE* destroyQueue(QUEUE* queue);

bool enqueue(QUEUE* queue, void* itemPtr);
bool dequeue(QUEUE* queue, void** itemPtr);

bool queueFront(QUEUE* queue, void** itemPtr);
bool queueRear(QUEUE* queue, void** itemPtr);
int queueCount(QUEUE* queue);

bool emptyQueue(QUEUE* queue); 
bool fullQueue(QUEUE* queue);


/*=========================createQueue============================
 * Allocates memory for a queue head node from dynamic memory and 
 * returns its address to the caller
 * Pre 	No input required
 * Post	head has been allocated and initialized
 * Return head if successful; null if overflow
 */

QUEUE* createQueue(void)
{
	//local definitions
	QUEUE* queue;

	//statements
	queue = (QUEUE*) malloc(sizeof(QUEUE));
	if(queue)
	{
		queue->front =NULL;
		queue->rear = NULL;
		queue->count = 0;
	}

	return queue;
}

/*=========================destroyQueue============================
 * Deletes all data from a queue and recycles its memory
 * then deletes and recycles queue head
 * Pre a valid queue is given as input
 * Post all data have been deleted and recycled
 * Return null  
 */

QUEUE* destroyQueue(QUEUE* queue)
{
	//local definitions
	QUEUE_NODE* deletePtr;

	//statements
	if(queue)
	{
		while(queue->front != NULL)
		{
			free(queue->front->dataPtr);
			deletePtr = queue->front;
			queue->front = queue->front->next;
			free(deletePtr);
		}
		free(queue);
	}//if

	return NULL;
}//destroyQueue
 

/*===============================enqueue============================
 * This algorithm inserts data in a queue
 * Pre a pointer to queue and data has been given as input
 * Post data is inserted at the rear
 * Return true if successful, false if overflow
 */

bool enqueue(QUEUE* queue, void* itemPtr)
{
	//local definitions
	QUEUE_NODE* newNodePtr;

	//statements
	if(!(newNodePtr = (QUEUE_NODE*) malloc(sizeof(QUEUE_NODE))))
		return false;

	newNodePtr->dataPtr = itemPtr;
	newNodePtr->next = NULL;

	if(queue->count == 0)
		//inserting into null queue
		queue->front  = newNodePtr;
	else
		queue->rear->next = newNodePtr;

	(queue->count)++;
	queue->rear = newNodePtr;
	return true;
}//enqueue
 
/*===============================dequeue============================
 * This algorithm deletes data from  a queue
 * Pre a pointer to queue and a reference to location for outgoing
 * 	data is given
 * Post data is deleted from front
 * Return true if successful, false if underflow
 */

// call to dequeue must cast pointer to void
// e.g dequeue(queue, (void*)&dataPtr)

bool dequeue(QUEUE* queue, void** itemPtr)
{
	//local definitions
	QUEUE_NODE* deleteLoc;

	//statements
	if(!queue->count)
		return false;

	*itemPtr = queue->front->dataPtr;
	deleteLoc = queue->front;
	if(queue->count == 1)
		//deleting only item in queue
		queue->rear = queue->front = NULL;
	else
		queue->front = queue->front->next;
	
	(queue->count)--;
	free(deleteLoc);

	return true;
}//dequeue
 
/*============================queueFront============================
 * This algorithm retrieves data at front of the queue without
 * changing the queue contents.
 * Pre	queue is pointer to an initialized queue
 * Post itemPtr passed back to an initialized queue
 * Return true if successful, false if undeflow
 */

bool queueFront(QUEUE* queue, void** itemPtr)
{
	//statements
	if(!queue->count)
		return false;

	*itemPtr = queue->front->dataPtr;
	return true;
}//queueFront
 
/*============================queueRear============================
 * This algorithm retrieves data at rear of the queue without
 * changing the queue contents.
 * Pre	queue is pointer to an initialized queue
 * Post itemPtr passed back to an initialized queue
 * Return true if successful, false if underflow
 */

bool queueRear(QUEUE* queue, void** itemPtr)
{
	//statements
	if(!queue->count)
		return false;

	*itemPtr = queue->rear->dataPtr;
	
	return true;
}

bool emptyQueue(QUEUE* queue)
{
	return (queue->count == 0);
}

bool fullQueue(QUEUE* queue)
{
	//local definitions
	QUEUE_NODE* temp;

	//statements
	temp = (QUEUE_NODE*)malloc(sizeof(*(queue->rear)));

	if(temp)
	{
		free(temp);
		return false;
	}
	//heap full
	return true;
} //fullqueue

int queueCount(QUEUE* queue)
{
	return queue->count;
}

