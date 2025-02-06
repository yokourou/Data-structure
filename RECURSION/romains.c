#include <stdio.h>
#include <string.h>
#include "listes.h"


int chiffreRomainToDecimal(char chiffreRomain){
	char chiffres[]={'M','D','C','L','X','V','I','f'};
	int valeursDecimales[]={1000,500,100,50,10,5,1};
	int decimal=0;
	for (int i = 0; chiffres[i]!='f';i++){
		if (chiffres[i]==chiffreRomain){
			decimal=valeursDecimales[i];
		}
	}
	return decimal;
}



int nombreRomainToDecimal(char* strRomain){
	printf("Entree dans nombreRomainToDecimal ,  chiffreRomain=%s\n",strRomain);
	int decimal=0;
	int len=strlen(strRomain);
	if(len!=0){
		int cur=chiffreRomainToDecimal(strRomain[0]);
		int next=chiffreRomainToDecimal(strRomain[1]);
		if (cur>next)
			{ decimal=cur+(nombreRomainToDecimal(strRomain+1));}
		else{
			{ 
				decimal=next-cur+nombreRomainToDecimal(strRomain+2);
			}
		
		} 	
	}
	else {
		decimal=chiffreRomainToDecimal(strRomain[0]);
	}
	printf("Sortie de nombreRomainToDecimal ,  chiffreRomain=%s , valeur retournee :%d\n",strRomain,decimal);
	return decimal;
}

int main()
{
	char nombreRomain[200];
	printf("Entrez un nombre romain : ");
	scanf("%s",nombreRomain);
	printf("resultat juste : %d\n",nombreRomainToDecimal(nombreRomain));

	return 0;
}
