#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

// Driver code
int main() {
  int ch, data;
  struct rbNode * rbt;
  rbt = NULL;
  while (1) {
    printf("1. Insertion\t2. Deletion\n");
    printf("3. Traverse\t4. Exit");
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch) {
      case 1:
        printf("Enter the element to insert:");
        scanf("%d", &data);
        rbt = rbtInsert(rbt, data);
        break;
      case 2:
        printf("Enter the element to delete:");
        scanf("%d", &data);
        rbt = rbtDelete(rbt, data);
        break;
      case 3:
        rbtDisplay(rbt);
        printf("\n");
        break;
      case 4:
        exit(0);
      default:
        printf("Not available\n");
        break;
    }
    printf("\n");
  }
  return 0;
}
