/* Header file for binary search tree.Contains structural and prototypes for BST*/
#include<stdbool.h>
#include<stdlib.h>

//structure declarations

typedef struct node {
	void* dataPtr;
	struct node* left;
	struct node* right;
}NODE;

typedef struct {
	int count;
	int (*compare) (void* arg1, void* arg2);
	NODE* root;
} BST_TREE;

//prototype declarations

BST_TREE* BST_Create(int (*compare)(void* arg1, void* arg2));
BST_TREE* BST_Destroy(BST_TREE* tree);

bool BST_Insert(BST_TREE* tree, void* dataPtr);
bool BST_Delete(BST_TREE* tree, void* dltKey);
void* BST_Retrieve(BST_TREE* tree, void* keyPtr);
void BST_Traverse(BST_TREE* tree, void (*process)(void*dataPtr));

bool BST_Empty(BST_TREE* tree);
bool BST_Full(BST_TREE* tree);
int BST_Count(BST_TREE* tree);

static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newPtr);
static NODE* _delete(BST_TREE* tree, NODE* root, void* dataPtr, bool* success);
static void* _retrieve(BST_TREE* tree , void* dataPtr, NODE* root);
static void _traverse(NODE* root, void (*process) (void* dataPtr));
static void _destroy(NODE* root);

BST_TREE* BST_Create(int (*compare)(void* arg1, void* arg2))
{
	//local definitions
	BST_TREE* tree;

	//statements
	tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if(tree)
	{
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}//if

	return tree;
}



bool BST_Insert(BST_TREE* tree, void* dataPtr)
{
	//local definitions
	NODE* newPtr;

	//statements
	newPtr = (NODE*)malloc(sizeof(NODE));
	if(!newPtr)
		return false;

	newPtr->right = NULL;
	newPtr->left = NULL;
	newPtr->dataPtr = dataPtr;

	if(tree->count == 0)
		tree->root = newPtr;
	else
		_insert(tree, tree->root, newPtr);
	
	(tree->count)++;
	return tree;
}//BST_Insert
 

static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newPtr)
{
	//statements
	if(!root)
		return newPtr;

	//local null subtree for insertion
	if(tree->compare(newPtr->dataPtr, root->dataPtr) < 0)
	{
		root->left = _insert(tree, root->left,newPtr);
		return root;
	}
	else
	{
		root->right = _insert(tree, root->right, newPtr);
		return root;
	}
	return root;
}// _insert
 

bool BST_Delete(BST_TREE* tree, void* dltKey)
{
	//local definitions
	bool success;
	NODE* newRoot;

	//statements
	newRoot = _delete(tree, tree->root, dltKey, &success);
	if(success)
	{
		tree->root = newRoot;
		(tree->count)--;
		if(tree->count == 0)
			tree->root = NULL;
	}

	return success;
}


static NODE* _delete(BST_TREE* tree, NODE* root, void* dataPtr, bool* success)
{
	//local definitions
	NODE* dltPtr;
	NODE* exchPtr;
	NODE* newRoot;
	void* holdPtr;

	//statements
	if(!root)
	{
		*success = false;
		return NULL;
	}

	if(tree->compare(dataPtr, root->dataPtr) < 0)
		root->left = _delete(tree, root->left, dataPtr, success);
	else if(tree->compare(dataPtr, root->dataPtr) > 0)
		root->right = _delete(tree, root->right, dataPtr, success);
	else
	{
		//delete node found -- test for leaf node
		dltPtr = root;
		if(!root->left)
			//no left subtree
		{
			free(root->dataPtr);
			newRoot = root->right;
			free(dltPtr);
			*success = true;
			return newRoot;
		}// if true
		else
			if(!root->right)
				//no right subtree
			{
				free(root->dataPtr);
				newRoot = root->left;
				free(dltPtr);
				*success = true;
				return newRoot;
			}
			else
			{
				//delete node has two subtrees
				exchPtr = root->left;
				//find predecessor (largest node on left subtree)
				while(exchPtr->right)
					exchPtr = exchPtr->right;
				//exchange data
				holdPtr = root->dataPtr;
				root->dataPtr = exchPtr->dataPtr;
				exchPtr->dataPtr = holdPtr;
				root->left = _delete(tree, root->left,
						exchPtr->dataPtr, success);
			}//else

	}// node found
	
	return root;
}// _delete
 

void* BST_Retrieve(BST_TREE* tree, void* keyPtr)
{
	//statements
	if(tree->root)
		return _retrieve(tree, keyPtr, tree->root);
	else
		return NULL;
}

void* _retrieve(BST_TREE* tree , void* dataPtr, NODE* root)
{
	//statements
	if(root)
	{
		if(tree->compare(dataPtr, root->dataPtr) < 0 )
			return _retrieve(tree, dataPtr, root->left);
		else if (tree->compare(dataPtr, root->dataPtr) > 0 )
			return _retrieve(tree, dataPtr, root->right);
		else
			//found equal key
			return root->dataPtr;
	}//if root
	else
		return NULL; //data not in tree
			     
}//_retrieve
 
void BST_Traverse (BST_TREE* tree, void (*process) (void* dataPtr))
{
	_traverse(tree->root, process);
	return ;
}


static void _traverse(NODE* root, void (*process) (void* dataPtr))
{
	if(root)
	{
		_traverse(root->left, process);
		process(root->dataPtr);
		_traverse(root->right, process);
	}
	return;
}

bool BST_empty(BST_TREE* tree)
{
	return (tree->count == 0);
}

bool BST_Full(BST_TREE* tree)
{
	//local definitions
	NODE* newPtr;

	//statements
	newPtr = (NODE*) malloc(sizeof(*(tree->root)));
	if(newPtr)
	{
		free(newPtr);
		return false;
	}
	else
		return true;
}//BST_full
 
int BST_Count(BST_TREE* tree)
{
	return (tree->count);
}

BST_TREE* BST_Destroy(BST_TREE* tree)
{
	if(tree)
		_destroy(tree->root);
	free(tree);
	return NULL;
}

void _destroy(NODE* root)
{
	if(root)
	{
		_destroy(root->left);
		free(root->dataPtr);
		_destroy(root->right);
		free(root);
	}
	return;
}

