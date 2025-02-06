#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

// Create a red-black tree
struct rbNode * rbtCreateNode(int data) {
  struct rbNode * new= malloc(sizeof( struct rbNode)) ;
  new->data=data ;
  new->color=0;
  new->link[0]=NULL;
  new->link[1]=NULL;
  return new ;  
}



struct rbNode* rbright(struct rbNode *x) {
    struct rbNode *new = x->link[0];
    x->link[0] = new->link[1];
    new->link[1] = x;
    return new;
}

// Left rotation
struct rbNode* rbleft(struct rbNode *x) {
    struct rbNode *new = x->link[1];
    x->link[1] = new->link[0];
    new->link[0] = x;
    return new;
}



struct rbNode* rbtInsert(struct rbNode *root, int data) {
    struct rbNode *stack[100], *ptr, *newnode, *xPtr, *yPtr;
    int dir[100], ht = 0, index;

    ptr = root;
    if (!root) {
        root = rbtCreateNode(data);
        root->color = BLACK; // Root is always black
        return root;
    }

    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL) {
        if (ptr->data == data) {
            printf("Duplicates Not Allowed!!\n");
            return root;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }

    stack[ht - 1]->link[index] = newnode = rbtCreateNode(data);

    while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
        int parentIndex = dir[ht - 2];
        yPtr = stack[ht - 2]->link[!parentIndex];

        if (yPtr != NULL && yPtr->color == RED) {
            // Case 1: Both parent and uncle are red
            stack[ht - 2]->color = RED;
            stack[ht - 1]->color = BLACK;
            yPtr->color = BLACK;
            ht -= 2;
        } else {
            // Case 2 and 3: Either uncle is black or NULL
            if (dir[ht - 1] != dir[ht - 2]) {
                // Case 2: Inside rotation
                stack[ht - 1] = (dir[ht - 2] == 0) ? rbright(stack[ht - 1]) : rbleft(stack[ht - 1]);
                stack[ht - 2]->link[dir[ht - 2]] = stack[ht - 1];
                ht--;
            }
            // Case 3: Outside rotation
            xPtr = (dir[ht - 2] == 0) ? rbleft(stack[ht - 2]) : rbright(stack[ht - 2]);
            xPtr->color = BLACK;
            xPtr->link[!dir[ht - 2]]->color = RED;
            if (ht == 3) {
                root = xPtr;
            } else {
                stack[ht - 3]->link[dir[ht - 3]] = xPtr;
            }
            break;
        }
    }

    root->color = BLACK;
    return root;
}

    

// Utility to fix double black scenarios
struct rbNode* rbtFixDoubleBlack(struct rbNode *root, struct rbNode *parent, struct rbNode *x, int dir, struct rbNode *stack[], int ht) {
    struct rbNode *sibling;
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (dir == 0) { // x is left child
            sibling = parent->link[1];
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                parent = rbleft(parent);
                sibling = parent->link[1];
            }
            if ((sibling->link[0] == NULL || sibling->link[0]->color == BLACK) &&
                (sibling->link[1] == NULL || sibling->link[1]->color == BLACK)) {
                sibling->color = RED;
                x = parent;
                dir = (x == parent->link[0]) ? 0 : 1;
                parent = (ht > 1) ? stack[ht - 2] : NULL;
            } else {
                if (sibling->link[1] == NULL || sibling->link[1]->color == BLACK) {
                    if (sibling->link[0] != NULL) sibling->link[0]->color = BLACK;
                    sibling->color = RED;
                    sibling = rbright(sibling);
                    parent->link[1] = sibling;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->link[1] != NULL) sibling->link[1]->color = BLACK;
                parent = rbleft(parent);
                break;
            }
        } else { // x is right child
            sibling = parent->link[0];
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                parent = rbright(parent);
                sibling = parent->link[0];
            }
            if ((sibling->link[0] == NULL || sibling->link[0]->color == BLACK) &&
                (sibling->link[1] == NULL || sibling->link[1]->color == BLACK)) {
                sibling->color = RED;
                x = parent;
                dir = (x == parent->link[0]) ? 0 : 1;
                parent = (ht > 1) ? stack[ht - 2] : NULL;
            } else {
                if (sibling->link[0] == NULL || sibling->link[0]->color == BLACK) {
                    if (sibling->link[1] != NULL) sibling->link[1]->color = BLACK;
                    sibling->color = RED;
                    sibling = rbleft(sibling);
                    parent->link[0] = sibling;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->link[0] != NULL) sibling->link[0]->color = BLACK;
                parent = rbright(parent);
                break;
            }
        }
    }
    if (x != NULL) x->color = BLACK;
    return root;
}

// Delete a node
struct rbNode* rbtDelete(struct rbNode *root, int data) {
    struct rbNode *stack[100], *ptr, *xPtr, *yPtr;
    int dir[100], ht = 0, diff;

    if (!root) {
        printf("Tree not available\n");
        return root;
    }

    ptr = root;
    while (ptr != NULL) {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->link[diff];
    }

    if (ptr == NULL) {
        printf("Data not found in tree\n");
        return root;
    }

    if (ptr->link[0] == NULL || ptr->link[1] == NULL) {
        // Node with only one child or no child
        if (ptr->link[0] == NULL) {
            xPtr = ptr->link[1];
        } else {
            xPtr = ptr->link[0];
        }

        if (ht == 0) {
            root = xPtr;
        } else {
            stack[ht - 1]->link[dir[ht - 1]] = xPtr;
        }

        if (ptr->color == BLACK) {
            if (xPtr != NULL && xPtr->color == RED) {
                xPtr->color = BLACK;
            } else {
                root = rbtFixDoubleBlack(root, stack[ht - 1], xPtr, dir[ht - 1], stack, ht);
            }
        }
        free(ptr);
    } else {
        // Node with two children
        yPtr = ptr->link[1];
        stack[ht] = ptr;
        dir[ht++] = 1;

        while (yPtr->link[0] != NULL) {
            stack[ht] = yPtr;
            dir[ht++] = 0;
            yPtr = yPtr->link[0];
        }

        ptr->data = yPtr->data;
        stack[ht - 1]->link[dir[ht - 1]] = yPtr->link[1];

        if (yPtr->color == BLACK) {
            if (yPtr->link[1] != NULL && yPtr->link[1]->color == RED) {
                yPtr->link[1]->color = BLACK;
            } else {
                root = rbtFixDoubleBlack(root, stack[ht - 1], yPtr->link[1], dir[ht - 1], stack, ht);
            }
        }
        free(yPtr);
    }

    if (root != NULL) root->color = BLACK;
    return root;
}

// Print the inorder traversal of the tree
void rbtDisplay(struct rbNode *node) {
    if (node == NULL) {
        printf("[]");
        return;
    }
    printf("%d(%d) [", node->data, node->color);
    rbtDisplay(node->link[0]);
    printf("] [");
    rbtDisplay(node->link[1]);
    printf("]");
}
