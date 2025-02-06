#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listes.h"

list * listCreate() {
    return NULL;
}

list * listAdd(list * l,int n){
    list * plist=(list *) malloc(sizeof(list));
    if (plist==NULL) return NULL;

    plist->value=n;
    plist->next=l;
    return plist;
}



void listDisplay(list * l){
    list* tete=l;
    list* queue=l;
    if (tete!=NULL){
        queue=tete->next ;
        if(queue != NULL){
        listDisplay(queue);
      }
        printf("%d ",tete->value);
   
    }   
}


void listInverseDisplay(list * l){
    list* tete = l; 
    if(tete != NULL){
        printf("%d ",tete->value);
        listInverseDisplay(tete->next);
    }

}



int listSearch(list * plist, int n){
    int code=0;
    if(plist !=NULL){
        if(plist->value == n){
            code=1;
        }
        else{
            code+=listSearch(plist->next,n);
        }
    }
    return code ;
}



list * listMap(list* l , int (*f)(int)){
    list *nouv=listCreate();
    if(l!=NULL){
        int val=(*f)(l->value);
        nouv=listAdd(listMap(l->next,f),val);}
    return nouv;

}

list * listFilter(list* l , int (*p)(int)){
    list *nouv=listCreate();
    if(l!=NULL){
        int code=(*p)(l->value);
        if (code==1){
            nouv=listAdd(listFilter(l->next,p),l->value);
        }
        else{
            nouv=listFilter(l->next,p);
        }
    }
    
    return nouv;

}

int listFold(list* l , int (*op)(int,int),int base){
    int res=0;
    if(l !=NULL){
        base=(*op)(l->value,base);
        res=listFold(l->next,op,base);
    }
    else{
        res=base;
    }
      return res;
}



int  opSum(int n1,int n2){
    return n1+n2;
}


int listSum(list* l ){

    return listFold(l,&opSum,0);
}

int opProd(int n1 ,int n2){
    return n1*n2;
}

int listProd(list* l ){
      return listFold(l,&opProd,1);
}

int opLen(int n1, int n2){
    return n2+1;

}
int listLen(list* l ){
      return listFold(l,&opLen,0);
}

// concatene à l1 l'inverse de l2
list * ajouteInverse(list * l1,list * l2){
    if(l2 != NULL){
        l1=listAdd(l1,l2->value);
        l1=ajouteInverse(l1,l2->next);
    }
      return l1;
}

list* listInverse(list *l){
    list* nouv=listCreate();
    if(l!=NULL){
        nouv=ajouteInverse(nouv,l);
    }
      return nouv;
}

void listFree(list * plist){
    if(plist!=NULL){
        listFree(plist->next);
    }
    free(plist);
    
}