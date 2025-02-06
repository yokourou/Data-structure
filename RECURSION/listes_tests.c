#include <stdio.h>
#include <string.h>
#include "listes.h"


list * liste_de_test(){
	list * l = listCreate();
	l =listAdd(NULL, 2 );
	l =listAdd(l,5 );
	l =listAdd(l,1 );
	l =listAdd(l,4 );
	l =listAdd(l,2);

return l;
}

void test_listDisplay(){

	list * l=liste_de_test();
	printf("Affichage de la liste : ");
	listDisplay(l);
	printf("\n");

	listFree(l);
}

void test_listInverseDisplay(){

	list * l=liste_de_test();
	printf("Affichage inverse de la liste : ");
	listInverseDisplay(l);
	printf("\n");

	listFree(l);
}

void test_listSearch()
{

	list * l=liste_de_test();
	int n=4;
	printf("Recherche de %d dans la liste : %d\n",n,listSearch(l , n));
	n=2;
	printf("Recherche de %d dans la liste : %d\n",n,listSearch(l , n));
	n=3;
	printf("Recherche de %d dans la liste : %d\n",n,listSearch(l , n));
	n=7;
	printf("Recherche de %d dans la liste : %d\n",n,listSearch(l , n));

	listFree(l);

}

int carres(int n){
	return n*n ;
}

void test_listMap(){

	list * l =liste_de_test();
	printf("Liste des carres : ");
	listDisplay(listMap(l,&carres));
	printf("\n");
	listFree(l);
}


int sup3(int n){
	return n>3;

}

void test_listFilter(){
	list * l =liste_de_test();
	printf("Liste filtree : ");
	listDisplay(listFilter(l,&sup3));
	printf("\n");
	listFree(l);

}

void test_listSum(){
	list * l =liste_de_test();
	int resultat = listSum(l);
	printf("Somme : %d\n",resultat);
	listFree(l);
}

void test_listProd(){
	list * l =liste_de_test();
	int resultat = listProd(l);
	printf("Produit : %d\n",resultat);
	listFree(l);
}
void test_listLen(){
	list * l =liste_de_test();
	int resultat = listLen(l);
	printf("Longueur : %d\n",resultat);
	listFree(l);
}
void test_listInverse(){
	list * l =liste_de_test();
	list * l2 =listInverse(l);
	printf("Inverse de la liste ");
	listDisplay(l2);
	printf("\n");

	listFree(l);
	listFree(l2);
	
}

int main()
{
	test_listDisplay();
	test_listInverseDisplay();
	test_listSearch();

	test_listMap();

	test_listFilter();

	test_listSum();
	test_listProd();
	test_listLen();

	test_listInverse();
}
