#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define STACK_DEPTH 10


int line; // Current line number
int stack_ptr; // The stack pointer
double stack[STACK_DEPTH]; // An int array representing the rpn stack. It grows downwards.

void fail(const char* error, int c)
{
	printf("Line %d: error at %s with character %c\n", line, error, c);
	while(c!='\n'){
		c=getchar();
	}
}

void success(double result)
{
	if(result-(int) result==0){
		printf("Line %d: %d\n",line,(int) result);
	} else {
		printf("Line %d: %lf\n",line,result);
	}
}

void push(double nbr, int c)
{
	stack_ptr--;
	stack[stack_ptr]=nbr;
	printf("Pushed %lf, stack_ptr is %d\n",nbr, stack_ptr);
}

double pop(int c)
{
	double a=stack[stack_ptr];
	stack_ptr++;
	printf("Popped %lf, stack_ptr is %d\n",a, stack_ptr);
	return a;
}

bool canpush(int c)
{
	if(stack_ptr==0){
		fail("Stack depth reached", c);
		return 0;
	}
	return 1;
}

bool canpop(int c)
{
	if(stack_ptr==10){
		fail("Tried to pop empty stack", c);
		return 0;
	}
	return 1;
}

void rpnLine()
{
	int current = 0;
	int c = 0;

	while(1){
		c=getchar();
			
		while(isdigit(c)){
				current*=10;
				current+=(c-'0');
				c=getchar();
				if(!isdigit(c)){
					if(!canpush(c)){
						return;
					}
					push(current, c);
					current=0;
				}
		}
			
		if(c==EOF){
			exit(0);
		}
		
		if(c=='\n'){
			if(stack_ptr==9){
				success(pop(c));
				return;
			} else {
				fail("\\n", c);
				return;
			}
		}
		
		if(c=='+'){
			if(!canpop(c)){
				return;
			}
			int a=pop(c);
			
			if(!canpop(c)){
				return;
			}
			int b=pop(c);
			
			current=a+b;
			
			push(current, c);
			if(!canpush(c)){
				return;
			}
			
			current=0;
			
		} else if(c=='-'){
			
			if(!canpop(c)){
				return;
			}
			int a=pop(c);
			
			if(!canpop(c)){
				return;
			}
			int b=pop(c);
			
			current=b-a;
			
			push(current, c);
			if(!canpush(c)){
				return;
			}
			
			current=0;
		} else if(c=='*'){
			
			if(!canpop(c)){
				return;
			}
			int a=pop(c);
			
			if(!canpop(c)){
				return;
			}
			int b=pop(c);
			
			current=a*b;
			
			push(current, c);
			if(!canpush(c)){
				return;
			}
			
			current=0;
		} else if(c=='/'){
			
			if(!canpop(c)){
				return;
			}
			int a=pop(c);
			
			if(!canpop(c)){
				return;
			}
			int b=pop(c);
			
			if(a==0){
				fail("Division by 0", c);
				return;
			} 
			current=b/a;
			
			push(current, c);
			if(!canpush(c)){
				return;
			}
			
			if(stack_ptr==0){
				fail("Stack depth reached", c);
				return;
			}
			current=0;
		} else if(isspace(c)) {
		
		} else {
			fail("Invalid character", c);
			return;
		}		
	}
}


int main(int argc, char** argv)
{
	line=1;
	
	while(1){	
		stack_ptr=10;
		rpnLine();
		line++;
	}
}
