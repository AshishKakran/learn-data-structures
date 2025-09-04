/****************** STACK ADT ****************************
 * 	This header file contains implementation of 
 * 	abstract data type for stack structure. 
 * 	Usage: 
 * 		step 1: import using include"stack.h"
 * 		step 2: create stack
 * 		step 3: Data allocation is done by user
 *
 */

//imports

#include<stdlib.h>
#include<stdbool.h>

//global declarations

typedef struct node
{
	void* dataPtr;
	struct node* link;
} STACK_NODE;

typedef struct 
{
	int count;
	STACK_NODE* top;
}STACK;



/* =========================createStack=====================================
 * This algorithm creates an empty stack
 * Precondition 	None
 * Postcondition	Returns pointer to a null stack
 * 			-or- NULL if overflow
 */

STACK* createStack(void)
{
	//local definitions
	STACK* stack;

	//statements
	stack = (STACK*) malloc(sizeof(STACK));

	if(stack)
	{
		stack->count = 0;
		stack->top = NULL;
	}

	return stack;
}//createStack
 

/* =========================pushStack=====================================
 * This function pushes an item onto the stack
 * Pre	pointer to stack and data is given
 * Post data is inserted into stack
 * Return true if successful, false otherwise
 */

bool pushStack(STACK* stack, void* dataInPtr)
{
	//local definitions
	STACK_NODE* newPtr;

	//statements
	newPtr = (STACK_NODE*) malloc(sizeof(STACK_NODE));

	if(!newPtr)
		return false;

	newPtr->dataPtr = dataInPtr;
	newPtr->link = stack->top;
	stack->top = newPtr;

	(stack->count)++;
	return true;
}//pushStack
 

/* =========================popStack=====================================
 * This function pops item on the top of the stack
 * pre pointer to stack is given
 * post return pointer to user data if successful
 * 	NULL if underflow
 */

void* popStack(STACK* stack)
{
	//local definitions
	void* dataOutPtr;
	STACK_NODE* temp;

	//statements
	if(stack->count == 0)
		return NULL;

	temp = stack->top;
	dataOutPtr = stack->top->dataPtr;
	stack->top = stack->top->link;
	free(temp);
	(stack->count)--;

	return dataOutPtr;
}//popStack
 

/* =========================stackTop=====================================
 * Retrieves data from the top of stack without changing the stack
 * Pre stack is a pointer to the stack
 * Post Returns data pointer if successful
 * 		null pointer if stack empty
 */

void* stackTop(STACK* stack)
{
	//statements
	if(stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
} //stackTop
  
/* =========================emptyStack=====================================
 *  This function determines if a stack is empty
 *  Pre 	stack is pointer to a stack
 *  Post	returns 1 is empty; 0 if data in stack
 */

bool emptyStack(STACK* stack)
{
	//statements
	return (stack->count == 0);
}//empty stack
 


/* =========================fullStack=====================================
 *  This function determines if a stack is full.
 *  Full is defined as heap full
 *  Pre		stack is pointer to a stack head node
 *  Post	return true if heap full, false otherwise
 */


bool fullStack(STACK* stack)
{
	//local definition
	STACK_NODE* temp;

	//statements
	if((temp = (STACK_NODE*)malloc(sizeof(*(stack->top)))))
	{
		free(temp);
		return false;
	}//if
	 
	//malloc failed
	return true;
}//fullstack
 

/* =========================stackCount=====================================
 *  Returns number of elements in stack.
 *  Pre		 stack is a pointer to the stack
 *  Post	 Post count returned
 */

int stackCount(STACK* stack)
{
	//statements
	return stack->count;
}//stackCount
 

/* =========================destroyStack=====================================
 * This function releases all nodes to the heap
 * 	Pre  pointer to stack is given
 * 	Post returns null pointer
 */

STACK* destroyStack(STACK* stack)
{
	//local definitions
	STACK_NODE* temp;

	//statements
	if(stack)
	{
		//delete all nodes in stack
		while(stack->top != NULL)
		{
			//delete data entry
			free(stack->top->dataPtr);

			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		}//while
		 
		//stack now empty. Destory stack head node
		free(stack);
	}//if stack
	
	return NULL;
}


