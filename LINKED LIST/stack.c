#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack * stackCreate() {
	stack *stack1=malloc(sizeof(*stack1));
	stack1= NULL;
	
	
	return NULL;
}

int stackIsEmpty(stack * s) {
	
	int code=0;
	if (s!=NULL) {
		code=1;
	}
	return code;
}

stack * stackAdd(stack * s, int v) {
	stack *stack1=malloc(sizeof(*stack1));
	stack1->value=v;
	stack1->next=s;

	
	return stack1;
}

int stackTop(stack * s) {
	int val ;
	val=s->value;
	
	return val;
}

stack * stackRemove(stack * s) {
	
		stack* temp=s;
		s= s->next;
		free(temp);

	return s;
}

int stackSize(stack * s) {
	int nb =0 ;
	stack* cours=s;
	while(cours!=NULL){
		nb++;
		cours=cours->next;
	}
	return nb;
}

void stackDisplay(stack * s) {
	stack* cours=s;
	while(cours!=NULL){
		printf("%d",cours->value);
		cours=cours->next;
	}
}

void stackFree(stack * s) {
	stack* cours=s;
	while(cours!=NULL){
		cours=stackRemove(cours);

	}
	
}
