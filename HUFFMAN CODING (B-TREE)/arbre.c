#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre.h"

arbre feuille(char c){
  arbre new=malloc(sizeof(arbre));
  new->data=c;
  new->droite=NULL;
  new->gauche=NULL;
  return new;
}

arbre noeud(char c, arbre g, arbre d){
  arbre newn=malloc(sizeof(arbre));
  newn->data=c;
  newn->droite=d;
  newn->gauche=g;
  return newn;
}

int est_feuille(arbre a) {
  return (a != NULL && a->gauche == NULL && a->droite == NULL);
}

void libere_arbre(arbre *a) {
    if (*a != NULL) {
        libere_arbre(&((*a)->droite));
        libere_arbre(&((*a)->gauche));
        free(*a);
        *a = NULL; }
}

void infixe_inverse(FILE *f, arbre a) {
  if(a!=NULL){
    infixe_inverse(f,a->droite);
     if (!est_feuille(a)) {
          fprintf(f, "%c\n", a->data);
        }
    infixe_inverse(f,a->gauche);
  }

}

void imprime_blancs(FILE *f, int niveau, int est_droit) {
  if(niveau>0){
    for (int i = 0; i < 3* niveau ; i++) {
        fprintf(f," ");
    } 
    if (est_droit) {
        fprintf(f, "/-");
    } else {
        fprintf(f, "\\-");
    }
  }
}



void imprime_avec_blancs(FILE *f, arbre a, int niveau, int est_droit) {
    if (a != NULL) {
        imprime_avec_blancs(f,a->droite, niveau + 1, 1);
        imprime_blancs(f, niveau, est_droit);
        fprintf(f, "%c\n", a->data);
        imprime_avec_blancs(f,a->gauche, niveau + 1, 0);
    }
}


void imprime_arbre(FILE *f, arbre a){
  if (a!=NULL ){
  imprime_avec_blancs(f,a,0,0);
}
}



