#include <stdio.h>
#include <ctype.h>

#define STACK_DEPTH 10

double stack[STACK_DEPTH]; // A double array representing the rpn stack
int stack_ptr; // The stack pointer

void error(const char* err)
{
	printf("Error at %s\n", err);
}

void push(int nbr)
{
	if(stack_ptr>9){
		error("Stack depth reached");
		return;
	}
	stack[stack_ptr]=nbr;
	stack_ptr++;
}

int pop()
{
	if(stack_ptr==0){
		error("Cannot pop an empty stack");
		return 0;
	}
	stack_ptr--;
	return stack[stack_ptr+1];
}

double rpn()
{
	//TODO: implement as main rpn calculator function
}
	
int main(int argc, char** argv)
{
	stack_ptr=0;
	rpn();
}
