#include <stdio.h>
#include <stdlib.h>

typedef enum{FALSE=0,TRUE=1} Boolean;

typedef struct {
	int size;
	int top;
	int* stack;	
}stack;

//Create a stack
stack* createS(int size) {
	stack* s = (stack*)malloc(sizeof(stack));
	s->size = size;
	s->top = -1;
	s->stack = (int*)malloc(sizeof(int)*size);
	return s;
}

int stack_used(stack* s) {
	return s->top + 1;
}

int stack_unused(stack* s) {
	return s->size - s->top -1;
}

Boolean isFull(stack* s) {
	return (s->top == s->size-1)? TRUE:FALSE;
}

Boolean isEmpty(stack* s) {
	return (s->top == -1)? TRUE:FALSE;
}

void push(stack* s, int e) {
	if (isFull(s)) {
		fprintf(stderr,"[Push Err] Full\n");
		return;
	}
	s->top++;
	s->stack[s->top] = e;
}

int pop(stack* s) {
	if (isEmpty(s)) {
		fprintf(stderr,"[Pop Err] Empty\n");
		return -1;
	}
	return s->stack[s->top--];
}


//Empty a stack
void clearS(stack* s) {
	while(!isEmpty(s)) {
		pop(s);
	}
}

//Load a int array into stack. 
//The first elements of the array is at the bottom of the stack. 
void loadS(stack* s, int* elements, int length) {
	clearS(s);
	if (s->size < length) { 
		fprintf(stderr,"[Load Err] Array larger than stack\n");
	}
	int i=0;
	while (i<length) {
		push(s,elements[i]);
		i++;
	}
}

//Pour one stack into another
void pourS(stack* from,stack* to) {
	if (stack_unused(to) < stack_used(from)) {
		fprintf(stderr,"[Pour Err] Space not enough");
		return;
	} 
	while (!isEmpty(from)) {
		push(to,pop(from));
	}
}

//Return a copy of a stack
stack* copyS(stack* s) {
	stack* newstack = createS(s->size);
	stack* tmpstack = createS(s->size);
	pourS(s, tmpstack);
	while (!isEmpty(tmpstack)) {
		int e = pop(tmpstack);
		push(s,e);
		push(newstack,e);	
	}
	return newstack;
}

//Print out the graph representation of a stack
void printS(stack* s) {
	stack* tmp = copyS(s);
	printf("    \n");
	int i = 0;
	while (i < stack_unused(tmp)) {
		printf("|   |\n");
		i++;
	} 
	while (!isEmpty(tmp)) {
		printf("|%3d|\n",pop(tmp));
	}
	printf(" ---\n");
	free(tmp);
}


/* Test function */
void test() {
	//Initiate a stack
	stack* s = createS(5);
	int e1[] = {0,1,2,3,4};
	loadS(s,e1,5);
	pop(s);
	pop(s);
	printS(s);
	//Initiate anoter stack
	stack* ss = createS(5);
	int e2[] = {100,99,98,97,96};
	loadS(ss,e2,5);
	printS(ss);
	
	//Merge two stack into a large one
	stack* sr = createS(10);
	while (!isEmpty(s) || !isEmpty(ss)) {
		if (!isEmpty(s)) push(sr,pop(s));
		if (!isEmpty(ss)) push(sr,pop(ss));
	}
	printS(sr);
	//Pour merged stack into another
	stack* srr = createS(10);
	pourS(sr,srr);
	printS(srr);
	free(s);free(ss);free(sr);free(srr);
}
