#include <stdio.h>
#include <ctype.h>

#define STACK_DEPTH 10

int stack_ptr; // The stack pointer
double stack[STACK_DEPTH]; // An int array representing the rpn stack

void error(const char* err)
{
	printf("Error at: %s\n", err);
}

void push(double nbr)
{
	if(stack_ptr==STACK_DEPTH){
		error("Stack depth reached");
		return;
	}
	stack_ptr++;
	stack[stack_ptr]=nbr;
}

double pop()
{
	if(stack_ptr==0){
		error("Cannot pop an empty stack");
		return 0;
	}
	double ret=stack[stack_ptr];
	stack_ptr--;
	return ret;
}

void rpn()
{
	//TODO: implement as main rpn calculator function

	int c;
	int linecount = 1;
	
	while(1){
		c=getchar();
		if (c==EOF){
			return;
		} else if(c=='\n') {
			printf("Line %d: %lf\n",linecount,pop());
			linecount++;
		} else if(isdigit(c)){
			push(c-'0');
		} else if(c=='+') {
			push(pop()+pop());
		} else if(c=='-'){
			double a=pop();
			push(pop()-a);
		} else if(c=='*'){
			push(pop()*pop());
		} else if(c=='/'){
			double a=pop();
			push(pop()/a);
		} 	
	}
}
	
int main(int argc, char** argv)
{	
	rpn();
}
