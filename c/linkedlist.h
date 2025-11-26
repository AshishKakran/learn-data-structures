/* This header files implements linked list ADT
 * The linkedlist can be ordered or random(chronological)
 * This file implements ordered linkedlist
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//list ADT type definitions

typedef int (*compare_cb) (void*, void*);

typedef struct node
{
	void* dataPtr;
	struct node* link;
} NODE;

typedef struct {
	int count;
	NODE* pos;
	NODE* head;
	NODE* rear;
	compare_cb cmp;
} LIST;

// prototype declarations

LIST* createList(compare_cb);
LIST* destroyList(LIST*);

int addNode(LIST* pList, void* dataInPtr);
bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr);
bool searchList(LIST* pList, void* pArgu, void** pDataOut);
bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr);
bool traverse(LIST* pList, int fromWhere, void** dataOutPtr);

int listCount(LIST* pList);
bool emptyList(LIST* pList);
bool fullList(LIST* pList);


static bool _insert(LIST* pList,NODE* pPre, void* dataInPtr);
static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);




/*==============================createList=======================
 * Allocates dynamic memory for a list head node and returns 
 * its address to the caller
 * pre	callback function to compare list items is given as input
 * post returns pointer to list head node or null if overflow
 */

LIST* createList(compare_cb cmp)
{
	//local definitions
	LIST* list;

	//statements
	list = (LIST*) malloc(sizeof(LIST));
	if(list)
	{
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;
		list->count = 0;
		list->cmp = cmp;
	}

	return list;
}//createList

/*==============================destroyList========================
 * Deletes all data in the list and recycles memory
 * Pre	A pointer to valid list is given as input
 * Post	All data and head structure is deleted
 * Returns null head pointer 
 */

LIST* destroyList(LIST* pList)
{
	//local definitions
	NODE* deletePtr;

	//statements
	if(pList)
	{
		while(pList->count > 0)
		{
			//first delete data
			free(pList->head->dataPtr);

			// Now delete node
			deletePtr = pList->head;
			pList->head = pList->head->link;
			pList->count--;
			free(deletePtr);
		}//while
	
		free(pList);
	}//if

	return NULL;
}//destroyList
 

int addNode(LIST* pList, void* dataInPtr)
{
	//local definitions 
	bool found;
	bool success;

	NODE* pPre;
	NODE* pLoc;

	//statements
	found = _search(pList, &pPre, &pLoc, dataInPtr);
	if(found)
		//duplicate keys not allowed
		return (+1);

	success = _insert(pList,pPre,dataInPtr);
	if(!success)
		//overflow
		return (-1);

	return (0);
}//addNode
 

static bool _insert(LIST* pList,NODE* pPre, void* dataInPtr)
{
	//local definitions
	NODE* pNew;

	//statements
	if(!(pNew = (NODE*)malloc(sizeof(NODE))))
		return false;
	
	pNew->dataPtr = dataInPtr;
	pNew->link = NULL;

	if(pPre == NULL)
	{
		//adding before first node or to empty list
		pNew->link = pList->head;
		pList->head = pNew;
		if(pList->count == 0)
			//adding to empty list, set rear
			pList->rear = pNew;
	}
	else
	{
		//adding in middle or at end
		pNew->link = pPre->link;
		pPre->link = pNew;

		//now check for add at the end of the list
		if(pNew->link == NULL)
			pList->rear = pNew;
	}

	(pList->count)++;
	return true;
}// _insert
 

bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr)
{
	//local definitions
	bool found;
	NODE* pPre;
	NODE* pLoc;

	//statements
	found = _search(pList, &pPre, &pLoc, keyPtr);
	if(found)
		_delete(pList, pPre, pLoc, dataOutPtr);

	return found;
}//removeNode
 
void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr)
{
	//statements
	*dataOutPtr = pLoc->dataPtr;
	if(pPre == NULL)
		pList->head = pLoc->link;
	else
		pPre->link = pLoc->link;

	if(pLoc->link == NULL)
		pList->rear = pPre;

	(pList->count)--;
	free(pLoc);
	return;
}//_delete
 
bool searchList(LIST* pList, void* pArgu, void** pDataOut)
{
	//local definitions
	bool found;

	NODE* pPre;
	NODE* pLoc;
	
	//statements
	found = _search(pList, &pPre, &pLoc, pArgu);
	if(found)
		*pDataOut = pLoc->dataPtr;
	else
		*pDataOut = NULL;
	return found;
}// searchList
 

bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu)
{
#define COMPARE \
	(((*pList->cmp) (pArgu, (*pLoc)->dataPtr)))

#define COMPARE_LAST \
	((*pList->cmp)(pArgu, pList->rear->dataPtr))

	//local definitions
	int result;

	//statements
	*pPre = NULL;
	*pLoc = pList->head;
	if(pList->count == 0)
		return false;

	//test for argument > last node in list
	if(COMPARE_LAST > 0)
	{
		*pPre = pList->rear;
		*pLoc = NULL;
		return false;
	}

	while( (result = COMPARE) > 0)
	{
		*pPre = *pLoc;
		*pLoc = (*pLoc)->link;
	}

	if(result == 0)
		return true;
	else
		return false;
}// _search 
 

bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr)
{
	//local definitions 
	bool found;

	NODE* pPre;
	NODE* pLoc;

	//statements
	found = _search(pList, &pPre, &pLoc, pArgu);
	if(found)
	{
		*dataOutPtr = pLoc->dataPtr;
		return true;
	}
	*dataOutPtr = NULL;
	return false;
}// retrieveNode
 
bool emptyList(LIST* pList)
{
	return (pList->count == 0);
}

bool fullList(LIST* pList)
{
	//local definitions
	NODE* temp;

	//statements
	if((temp = (NODE*)malloc(sizeof(*(pList->head)))))
	{
		free(temp);
		return false;
	}

	return true;
}// fullList
 

int listCount(LIST* pList)
{
	//statements
	return pList->count;
}

bool traverse(LIST* pList, int fromWhere, void** dataPtrOut)
{
	//statements
	
	if(pList->count == 0)
		return false;

	if(fromWhere == 0)
	{
		//start from first node
		pList->pos = pList->head;
		*dataPtrOut = pList->pos->dataPtr;
		return true;
	}
	else
	{
		if(pList->pos->link == NULL)
			return false;
		else
		{
			pList->pos = pList->pos->link;
			*dataPtrOut = pList->pos->dataPtr;
			return true;
		}//if else
	}// if fromwhere else

}//traverse




