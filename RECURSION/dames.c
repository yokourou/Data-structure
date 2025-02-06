#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct liste_solutions{
	int * placement;
	struct liste_solutions * next;
} liste_solutions;

liste_solutions *  addSolution(liste_solutions * liste,int * placement,int n)
{
	liste_solutions * nouvelle = (liste_solutions*)malloc(sizeof(liste_solutions));
	
	nouvelle->next=liste;

	nouvelle->placement=(int*)malloc(n*sizeof(int));
	for (int l=0;l<n;l++){
		nouvelle->placement[l]=placement[l];
	}
	return nouvelle;
}

// Pour visualiser l'échiquier correspondant à un placement donné.
// Le paramètre placement est une liste de n entiers entre 0 et n-1 correspondant au 
// numéro de colonne de chaque dame (sur chaque ligne).
// Si une valeur est négative, aucune dame ne sera placée sur la ligne.
void displayGame(int* placement, int n){
	for (int l = 0; l<n;l++){
		for (int c = 0; c<n;c++){
			if (c== placement[l]){
				printf("|*");
			}
			else{
				printf("|O");
			}
		}
		printf("|\n");
	}
}

int casePossible(int * placement,int l,int c){
	int OK = 1;
	for(int i=0;i<l;i++){
		if ( placement[i]==c || (i-l)==(placement[i]-c) || (l-i)==(placement[i]-c) ){
			OK=0;
		}
	}	
	return OK;
}


liste_solutions *  addAllSolutions(liste_solutions * l_sol, int * placement,int l,int n){
	if (l==n-1){
		for (int c = 0; c < n; c++) {
			if(casePossible(placement,l,c)==1 ){
			placement[l]=c;
			l_sol = addSolution(l_sol, placement, n);
        }
	}}
	else
	{
		for(int c=0;c<n;++c){
		if(casePossible(placement,l,c)==1 ){
			placement[l]=c;
			l_sol=addAllSolutions(l_sol,placement,l+1,n);
			}
	}
	}
	return l_sol;
}


void test_casePossible(){
	int placement[]={4,7,5,-1,-1,-1,-1,-1};
	displayGame(placement,8);

	for (int c=0;c<8;c++){
		int l=3;
		printf("casePosssible(%d , %d =%d )\n",l,c,casePossible(placement,l,c));
	}
	return ;
}


int nbSolutions(liste_solutions*l){
	if(l!=NULL){
		return 1+nbSolutions(l->next);
	}
	return 0;
}

void displaySolutions(liste_solutions*l,int n){
	if (l){
		printf("=======================\n");
		for (int ligne=0;ligne<n;ligne++){
			printf("%d ",l->placement[ligne]);
		}
		printf("\n");

		displayGame(l->placement,n);
		displaySolutions(l->next,n);
	}
}

int main(){
	
	liste_solutions * solutions=NULL;
	int n=8;
	
	int *placement = malloc(n * sizeof(int));

	solutions = addAllSolutions(solutions, placement, 0, n);
	printf("Nombre  de solutions : %d\n",nbSolutions(solutions));
	printf("Ensemble des solutions :\n");
	displaySolutions(solutions,n);
	free(solutions);
	return 0;

}