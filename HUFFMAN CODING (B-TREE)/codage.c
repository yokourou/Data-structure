#include <stdlib.h>
#include <stdio.h>
#include "codage.h"

encodage cree_encodage(binaire data, encodage suivant) {
  encodage res = malloc(sizeof(struct listeBinaire));
  if (res != NULL) {
    res->data = data;
    res->suivant = suivant;
  }
  
  return res;
}

void imprime_encodage(FILE *f, encodage e) {
  encodage reste = e;
  while(reste != NULL) {
    fprintf(f, "%i", reste->data);
    reste = reste->suivant;
  }
  fprintf(f, "\n");
}


void libere_encodage(encodage* e) {
  if (*e != NULL) {
    libere_encodage(&(*e)->suivant);
    free(*e);
    *e = NULL;
  }
}

int code_char(arbre a, char c, encodage *e) {
    if (a == NULL) {
        return 0;
    }

    if (a->data == c) {
        return 1;
    }

    if (a->gauche != NULL) {
        if (code_char(a->gauche, c, e)) {
            *e = cree_encodage(0, *e);
            return 1;
        }
    }

    if (a->droite != NULL) {
        if (code_char(a->droite, c, e)) {
            *e = cree_encodage(1, *e);
            return 1;
        }
    }

    return 0;
}




encodage code_texte(arbre a, char* s) {
  if (s== NULL || a==NULL){
    return NULL ;
  }
  encodage res=NULL;
  encodage temp=NULL ;
  while(*s !='\0'){
    temp=NULL ;
    if(code_char(a,*s,&temp)){
      if(res == NULL){
        res=temp;
      }
      else{
        encodage cours=res;
        while(cours->suivant!=NULL){
          cours=cours->suivant ;
        }
        cours->suivant=temp;
        
      }
    }else{
      free(res);
      return NULL ;
    }
    s++;
  }

  return res ;
}


encodage decode_suivant(FILE* f, arbre a, encodage e) {
  if (a == NULL || e == NULL) {
    return NULL;
  }
  arbre cours = a;
  while (e != NULL && cours->data == '*' ) {
      if(e->data == 0) {
          cours = cours->gauche; 
      } else {
          cours = cours->droite;
      } 
      e=e->suivant;
    }
    fprintf(f, "%c", cours->data);

  return e;
}

void decode(FILE* f, arbre a, encodage e) {
  if (e != NULL) {
    decode(f, a, decode_suivant(f, a, e));
  }
}






