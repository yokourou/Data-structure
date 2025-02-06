#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_element {
	int value;
	struct queue_element * previous;
	struct queue_element * next;
} queue_element;

typedef struct queue {
	int size;
	struct queue_element * head;
	struct queue_element * tail;
} queue;

queue * queueCreate();
int queueIsEmpty(queue * q);
void queueAdd(queue * q, int v);
int queueGet(queue * q);
void queueRemove(queue * q);
void queueDestroy(queue * q);
int queueSize(queue * q);
void queueDisplay(queue * q);

#endif
