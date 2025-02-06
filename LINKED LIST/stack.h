#ifndef STACK_H
#define STACK_H

typedef struct stack {
	int value;
	struct stack * next;
} stack;

stack * stackCreate();
int stackIsEmpty(stack * s);
stack * stackAdd(stack * s, int v);
int stackTop(stack * s);
stack * stackRemove(stack * s);
int stackSize(stack * s);
void stackDisplay(stack * s);
void stackFree(stack * s);

#endif
