#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void main() {
	int e[] = {1,2,3,4};
	int ee[] = {100,99,98,97,96,95};
	stack* s = createS(10);
	stack* ss = createS(10);
	loadS(ss,ee,6);
	loadS(s,e,4);
	printS(s);
	printS(ss);
	//push(s,0);
	pop(ss);
	pourS(ss,s);
	printS(s);
}

