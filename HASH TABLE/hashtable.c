#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"
#include <string.h>

list * listCreate()
{
return NULL ;
}

hashtable * hashtableCreate() {
	hashtable* tab1=malloc(sizeof(hashtable));
	tab1->n=10;
	int nb=tab1->n;
	tab1->tab=malloc(nb * sizeof(list*));
	int i=0;
	for(i=0;i<nb;++i)
	{
		tab1->tab[i]=listCreate();

	}
	
	return tab1;
}


int hash(char * key, int n) {
	int som=0;
	int i=0;
	while(key[i]!='\0'){
		som+=key[i];
		++i;
	}	
	som %=n;

	return som;
}

void listDisplay(list * l) {
	list*cour=l;
	
	while(cour!=NULL){
		printf("%s:%s\n ",cour->key,cour->value);
		cour=cour->next;
	}
}

void hashtableDisplay(hashtable * h) {
	int i=0;
	int nb=h->n;
	for(i=0;i<nb;i++){
		listDisplay(h->tab[i]);
	}
}

list * listAdd(list * l, char * newK, char * newV) {
	list * nouv=malloc(sizeof(list));
	nouv->value=newV;
	nouv->key=newK;
	nouv->next=l;
	return nouv;
}

char * listSearch(list * l, char * k) {
	list *cour1=l;
	char*res=NULL;
	res=NULL;
	while((cour1 !=NULL)&&(res==NULL)){
		if (strcmp(k,cour1->key)){
			res=cour1->value;		}
		cour1=cour1->next;
	}
	return res;
}

char * hashtableSearch(hashtable * h, char * key) {
	int i=0;
	char*res=NULL;
	while((i<h->n)&&(res==NULL)){
		res=listSearch(h->tab[i],key);
	}

	return res;
}

void hashtableAdd(hashtable * h, char * key, char * value) {
	int som=hash(key,h->n);
	list* ajout=h->tab[som];
	h->tab[som]=listAdd(ajout,key,value);

}

void listFree(list * l) {
		list*cou=l;
		list*temp=l;
		while(cou!=NULL){
			temp=cou->next;
			free(cou);
			cou=temp;
 		}
	free(cou);
	
	
}

void hashtableFree(hashtable * h) {
	int nb=h->n;
	int i;
	for (i=0;i<nb;i++){
		listFree(h->tab[i]);
	}
	free(h->tab);
	free(h);
}



hashtable * hashtableRehash(hashtable * h, int newN) {
	int nb=h->n;
	int newIndex=0 ;
	hashtable* tab1=malloc(sizeof(hashtable));
	tab1->n=newN;
	tab1->tab=malloc((tab1->n) * sizeof(list*));
	int i=0;
	for(i=0;i<tab1->n;++i){
		tab1->tab[i]=listCreate();
	}
	for (int i=0;i<nb;++i){
		list * currentList = h->tab[i];

		while(currentList !=NULL){
			newIndex = hash(currentList->key, newN);
            tab1->tab[newIndex] = listAdd(tab1->tab[newIndex], currentList->key, currentList->value);
            currentList = currentList->next;
		}
		
	}
	
	return tab1;

}
