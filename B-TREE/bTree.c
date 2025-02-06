
#include <stdio.h>
#include <stdlib.h>
#include "bTree.h"

//#define MAX 3
//#define MIN 2


struct BTreeNode *root;

void addValToNode(int item, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    int i = node->count;
    while (i > pos) {
        node->item[i] = node->item[i - 1];
        node->linker[i + 1] = node->linker[i];
        i--;
    }
    node->item[pos] = item;
    node->linker[pos + 1] = child;
    node->count++;
}

// Split the node
void splitNode(int item, int *pval, int pos, struct BTreeNode *node, struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, i, j;
    struct BTreeNode *right;

    addValToNode(item, pos, node, child);

    median = (MAX + 1) / 2;
    *pval = node->item[median];

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    right = *newNode;

    node->count = median;
    right->count = MAX - median;

    for (i = 0, j = median + 1; i < right->count; i++, j++) {
        right->item[i] = node->item[j];
        right->linker[i] = node->linker[j];
    }
    right->linker[i] = node->linker[j];
}

// Node creation
struct BTreeNode *bTreeCreateNode(int item, struct BTreeNode *child) {
    struct BTreeNode *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    newNode->item[0] = item;
    newNode->linker[0] = root;
    newNode->linker[1] = child;
    newNode->count = 1;
    return newNode;
}

// Set the value in the node
int setValueInNode(int item, int *pval, struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = item;
        *child = NULL;
        return 1;
    }

    if (item < node->item[0]) {
        pos = 0;
    } else {
        for (pos = node->count - 1; (item < node->item[pos] && pos > 0); pos--);
        if (item == node->item[pos]) {
            printf("Duplicates not allowed\n");
            return 0;
        }
        pos++;
    }

    if (setValueInNode(item, pval, node->linker[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insertion operation
void bTreeInsert(int item) {
    int flag;
    int i;
    struct BTreeNode *child;
    struct BTreeNode *newNode;

    flag = setValueInNode(item, &i, root, &child);

    if (flag) {
        newNode = bTreeCreateNode(i, child);
        root = newNode;
    }
}




// Remove the value
void removeVal(struct BTreeNode *myNode, int pos) {
    for (int i = pos; i < myNode->count - 1; i++) {
        myNode->item[i] = myNode->item[i + 1];
        myNode->linker[i + 1] = myNode->linker[i + 2];
    }
    myNode->count--;
}


// Do right shift
void rightShift(struct BTreeNode *myNode, int pos) {
    for (int i = myNode->count; i > pos; i--) {
        myNode->item[i] = myNode->item[i - 1];
        myNode->linker[i + 1] = myNode->linker[i];
    }
    myNode->linker[pos + 1] = myNode->linker[pos];
    myNode->count++;
}

// Do left shift
void leftShift(struct BTreeNode *myNode, int pos) {
    for (int i = pos; i < myNode->count - 1; i++) {
        myNode->item[i] = myNode->item[i + 1];
        myNode->linker[i] = myNode->linker[i + 1];
    }
    myNode->linker[myNode->count - 1] = myNode->linker[myNode->count];
    myNode->count--;
}

// Merge the nodes
void mergeNodes(struct BTreeNode *myNode, int pos) {
   void mergeNodes(struct BTreeNode *myNode, int pos) {
    struct BTreeNode *child1 = myNode->linker[pos];
    struct BTreeNode *child2 = myNode->linker[pos + 1];

    // Ajouter l'élément médian de myNode à child1
    child1->item[child1->count] = myNode->item[pos];
    child1->count++;

    // Ajouter tous les éléments et les liens de child2 à child1
    for (int i = 0; i < child2->count; i++) {
        child1->item[child1->count] = child2->item[i];
        child1->linker[child1->count] = child2->linker[i];
        child1->count++;
    }
    child1->linker[child1->count] = child2->linker[child2->count];

    // Supprimer l'élément de myNode
    removeVal(myNode, pos);

    // Libérer la mémoire de child2
    free(child2);
}

}

// Adjust the node
void adjustNode(struct BTreeNode *myNode, int pos) {
    // TODO : question 9
}

// Copy the successor
void copySuccessor(struct BTreeNode *myNode, int pos) {
  struct BTreeNode *dummy;
  dummy = myNode->linker[pos];

  for (; dummy->linker[0] != NULL;)
    dummy = dummy->linker[0];
  myNode->item[pos] = dummy->item[1];
}

// Delete a value from the node
int delValFromNode(int item, struct BTreeNode *myNode) {
  int pos, flag = 0;
  if (myNode) {
    if (item < myNode->item[1]) {
      pos = 0;
      flag = 0;
    } else {
      for (pos = myNode->count; (item < myNode->item[pos] && pos > 1); pos--)
        ;
      if (item == myNode->item[pos]) {
        flag = 1;
      } else {
        flag = 0;
      }
    }
    if (flag) {
      if (myNode->linker[pos - 1]) {
        copySuccessor(myNode, pos);
        flag = delValFromNode(myNode->item[pos], myNode->linker[pos]);
        if (flag == 0) {
          printf("Given data is not present in B-Tree\n");
        }
      } else {
        removeVal(myNode, pos);
      }
    } else {
      flag = delValFromNode(item, myNode->linker[pos]);
    }
    if (myNode->linker[pos]) {
      if (myNode->linker[pos]->count < MIN)
        adjustNode(myNode, pos);
    }
  }
  return flag;
}

// Delete operaiton
void bTreeDelete(int item, struct BTreeNode *myNode) {
    if (!delValFromNode(item, myNode)) {
        printf("La clé %d n'existe pas dans l'arbre.\n", item);
    }
}


void searching(int item, int *pos, struct BTreeNode *myNode) {
  if (!myNode) {
    return;
  } ;

  if (item < myNode->item[1]) {
    *pos = 0;
  } else {
    for (*pos = myNode->count;
       (item < myNode->item[*pos] && *pos > 1); (*pos)--)
      ;
    if (item == myNode->item[*pos]) {
      printf("%d present in B-tree", item);
      return;
    }
  }
  searching(item, pos, myNode->linker[*pos]);
  return;
}
void bTreeInorderTraversal(struct BTreeNode *myNode) {
    if (!myNode) {
        return;
    }
    int i;
    for (i = 0; i < myNode->count; i++) {
        bTreeInorderTraversal(myNode->linker[i]);
        printf("%d ", myNode->item[i]);
    }
    bTreeInorderTraversal(myNode->linker[i]);
}


