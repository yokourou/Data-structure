#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue * queueCreate() {
	queue * tete=malloc(sizeof(queue));
	tete->head=NULL;
	tete->tail=NULL;
	tete->size=0;
	return tete;
}

int queueIsEmpty(queue * q) {
	int code=0;
	int nb=q->size;
	if (nb>0){ 
		code=1;
	}
	return code;
}

void queueAdd(queue * q, int v) {
	queue_element *new=malloc(sizeof(new));
	new->value = v;
    new->next = NULL;
    new->previous = NULL;
	if (queueIsEmpty(q)==1) 
	{
		new->next=q->head;
		q->head->previous=new;
		q->head=new;
		new->previous=q->tail;

		
		
	}
	else{
		q->head=new;
		q->tail=new;
		new->previous=new;
		new->next=new;
	}
	q->size=q->size+1;
}

int queueGet(queue * q) {
	int val;
	val=q->tail->value;
	return val;
}

void queueRemove(queue * q) {
	 queue_element *toRemove = q->tail;

    if (q->tail == q->head) {
        q->tail = q->head = NULL;
    } else {
        q->tail = toRemove->previous;
        q->head->previous = q->tail; 
        q->tail->next = q->head; 
    }

    q->size--; 
    free(toRemove);
	
}
void queueDestroy(queue * q) {
	while(queueIsEmpty(q)==1){
		queueRemove(q);
	}
	free(q);
}

int queueSize(queue * q) {
	int len=0;
	len=q->size;
	return len;
}

void queueDisplay(queue * q) {
    queue_element *cours = q->head;
    int len = queueSize(q); 
    int i = 0;
    for (i = 0; i < len && cours != NULL; ++i) {
        printf("%d ", cours->value);
        cours = cours->next;
    }
}

