#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

void mainStack();
void mainQueue();

int main(int argc, char ** argv) {
	mainStack();
	mainQueue();
	return 0;
}

void mainStack() {
	int i;
	stack * s = stackCreate();
	for (i=0; i<10; i++) {
		s = stackAdd(s, i+1);
	}
	stackDisplay(s);
	stackFree(s);
}

void mainQueue() {
	int i;
	queue * q = queueCreate();
	for (i=0; i<10; i++) {
		queueAdd(q, i+1);
	}
	queueDisplay(q);
	for (i=0; i<5; i++) {
		queueRemove(q);
	}
	queueAdd(q, 100);
	queueDisplay(q);
	queueDestroy(q);
}
