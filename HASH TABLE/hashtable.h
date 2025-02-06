#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct list {
	char * key;
	char * value;
	struct list * next;
} list;

typedef struct {
	int n;
	list ** tab;
} hashtable;

list * listCreate();
hashtable * hashtableCreate();
int hash(char * key, int n);
void listDisplay(list * l);
void hashtableDisplay(hashtable * h);
list * listAdd(list * l, char * newK, char * newV);
char * listSearch(list * l, char * k);
char * hashtableSearch(hashtable * h, char * key);
void hashtableAdd(hashtable * h, char * key, char * value);
void listFree(list * l);
void hashtableFree(hashtable * h);
hashtable * hashtableRehash(hashtable * h, int newN);

#endif
