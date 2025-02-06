#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(int argc, char ** argv) {
	hashtable * h = hashtableCreate();
	printf("Hashtable vide :\n");
	hashtableDisplay(h);
	printf("Hashtable sans collision :\n");
	hashtableAdd(h, "Alice", "Dupont");
	hashtableAdd(h, "Bob", "Dupond");
	hashtableAdd(h, "Charles", "Dupon");
	hashtableDisplay(h);
	printf("Hashtaqble avec collision :\n");
	hashtableAdd(h, "David", "Duppont");
	hashtableDisplay(h);
	printf("Rehash à 5 :\n");
	h = hashtableRehash(h, 5);
	hashtableDisplay(h);
	printf("Rehash à 20 :\n");
	h = hashtableRehash(h, 20);
	hashtableDisplay(h);
	hashtableFree(h);
	return 0;
}
