#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "huffman.h"

arbrepoids cree_arbrepoids(arbre a, int poids) {
  arbrepoids ap =  malloc(sizeof(struct arbrepoids));
  if (ap != NULL) {
    ap->element = a;
    ap->poids = poids;
  }
  return ap;
}

liste cree_liste(arbre a, int poids, liste suivant) {
  liste res = malloc(sizeof(struct liste));

  if (res != NULL) {
    arbrepoids ap = cree_arbrepoids(a, poids);
    if (ap != NULL) {
      res->data = ap;
      res->suivant = suivant;
    }
    
  }

  return res;
}

liste genere_liste(char* s) {
  int frequence[256]={0};
  int i=0;
  for(i=0; s[i] !='\0' ;i++){
    frequence[(unsigned char)s[i]]++ ;
  }
  liste resultat = NULL;
  for(i=0;i<256;i++){
    if (frequence[i]>0)
      {
        arbre nouv=feuille((char)i);
        resultat=cree_liste(nouv,frequence[i],resultat);
      }
  }
  return resultat;
}

arbrepoids extrait_min(liste *l) {
  if (*l == NULL) {
    return NULL;
  }

  liste res = *l;
  liste prec = NULL;
  liste cours = *l;
  liste prec_min = NULL;
  int min = res->data->poids;
  while(cours!=NULL){
      if(cours->data->poids < min){
        min=cours->data->poids;
        res=cours;
        prec_min=prec;
      }
      prec = cours;
      cours=cours->suivant;
    }
  if(res!=NULL){
    if(prec_min!=NULL){
      prec_min->suivant=res->suivant;
    }
    else{
      *l= res->suivant;
    }
  }
  arbrepoids mi=res->data;
  free(res);
  return mi;
}



arbre huffman(char* s) {
  liste re1=genere_liste(s);
  while(re1 != NULL && re1->suivant != NULL){
      arbrepoids feuille1=extrait_min(&re1) ;
      arbrepoids feuille2=extrait_min(&re1);
      arbre nouvel_arbre = noeud('*',feuille1->element, feuille2->element);
      re1=cree_liste(nouvel_arbre,feuille1->poids+feuille2->poids,re1);
      
    }

    if (re1== NULL) {
       return NULL;
    }
  
  arbre resultat = re1->data->element;
  free(re1->data);
  free(re1);
  return resultat ;
}
