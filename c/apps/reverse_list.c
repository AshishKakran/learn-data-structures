/* This program generates a random sequence and prints that sequence in reverse
 *
 */

#include"dbg.h"
#include"../stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//global definitions
#define len 20

void generate_seq(int* , int);
void reverse_seq(int*, int);
void print_arr(int*, int);

int main(void)
{
	//local declarations
	int seq[len];

	//statements
	generate_seq(seq, len);	
	printf("Before reversal: ");
	print_arr(seq,len);
	reverse_seq(seq, len);
	printf("After reversal: ");
	print_arr(seq,len);

	return 0;
}

/* ===================generate_seq===================================
 *  This function generates a sequence of pseudo-random integers
 *  pre pointer to sequence and its required size is given 
 *  post: random integers are stored in the sequence
 */

void generate_seq(int* seq_arr, int seq_size)
{
	//statements
	srand(time(NULL));

	for(int i = 0; i<seq_size; i++)
		seq_arr[i] = rand() % 100;

}

/*============================reverse_seq============================
 * This function reverses the sequence given
 * pre sequence and its size is given
 * post: sequence is reversed
 */

void reverse_seq(int* seq_arr, int seq_size)
{
	//local declarations
	STACK* stack;
	int* temp = NULL;
	int i;

	//statements
	
	stack = createStack();	
	
	check_mem(stack); //zed's awesome macro

	for(i = 0; i < seq_size; i++)
	{
		temp = (int*) malloc(sizeof(int));
		*temp = seq_arr[i];
		pushStack(stack, temp );
	}

	for(i =0; i < seq_size; i++)
	{
		temp = (int*)popStack(stack);
		seq_arr[i] = *temp;
		free(temp); // comment this line and run under valgrind
	}

	destroyStack(stack);
	return;
error: 
	exit(1);
	
}

void print_arr(int* seq_arr, int seq_size)
{
	//statements
	for(int i = 0; i < seq_size; i++)
		printf(" %d ", seq_arr[i]);

	printf("\n");
}
