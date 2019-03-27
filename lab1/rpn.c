#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define STACK_DEPTH 10

int stack_ptr; // The stack pointer
double stack[STACK_DEPTH]; // An int array representing the rpn stack

void error(const char* err, int n)
{
	printf("Line %d: error at: %s\n",n , err);
	//printf("Stack pointer was %d\n", stack_ptr);
}

void push(double nbr)
{
	stack_ptr++;
	stack[stack_ptr]=nbr;
	//printf("Pushed %lf, current ptr is %d\n",nbr,stack_ptr);
}

double pop()
{
	double ret=stack[stack_ptr];
	stack_ptr--;
	//printf("Popped %lf, current ptr is %d\n",ret, stack_ptr);
	return ret;
}

bool rpnLine(int line)
{
	//TODO:t kinta works, fix the bugs 

	int c;
	int current=0;
	
	while(1){
		c=getchar();

		if(c==' '){
			if(stack_ptr==9){
				error("Stack full", line);
				return false;
			}
			push(current);
			current=0;
		} else if(isdigit(c)){
			current*=10;
			current+=(c-'0');
		} else if(c=='+'){
			if(stack_ptr<1){
				error("Not enough numbers on stack", line);
				return false;
			}
			push(pop()+pop());
		} else if(c=='-'){
			if(stack_ptr<1){
                                error("Not enough numbers on stack", line);
                                return false;
                        }
			double a=pop();
			push(pop()-a);
                } else if(c=='*'){
			if(stack_ptr<1){
                                error("Not enough numbers on stack", line);
                                return false;
                        }
			push(pop()*pop());
                } else if(c=='/'){
			if(stack_ptr<1){
                                error("Not enough numbers on stack", line);
                                return false;
                        }
			double a=pop();
			if(a==0){
				error("Cannot divide by 0", line);
				return false;
			}
			push(pop()/a);
                } else if(c=='\n'){

                        if(stack_ptr!=0){
                                error("\\n",line);
                        }
                        return false;
                } else if (c==EOF) {
			return true;
		}
	}
}
	
int main(int argc, char** argv)
{	
	int linecount=1;
	while(1){
		stack_ptr=-1;
		if(rpnLine(linecount)){
			break;
		}
		if(stack[0]-(int) stack[0]==0){
			printf("Line %d: %d\n",linecount , (int) stack[0]);
		} else {
			printf("Line %d: %lf\n",linecount , stack[0]);	
		}
		linecount++;
	}
}
