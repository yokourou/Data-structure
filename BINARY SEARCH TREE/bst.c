#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct bst * bstCreateNode(int key) {
    struct bst * new=malloc(sizeof(struct bst));
    new->key=key;
    new->right=NULL ;
    new->left=NULL;
    return new ;
}

void bstInorderTraversal(struct bst * root) {
	
    if(root!=NULL){
        bstInorderTraversal(root->left);
        printf("%d ",root->key);
        bstInorderTraversal(root->right);
        
    }
	
}

struct bst * bstInsert(struct bst * root, int key) {
    
    if(root ==NULL){
        struct bst * new=bstCreateNode(key);
        return new ;
    }
    else{
        if(root->key>key){
             root->left =bstInsert(root->left,key);
        }
        else{
            root->right=bstInsert(root->right,key);
        }
    }
   return root   ;
}

struct bst * bstMinValue(struct bst * root) {
    if (root !=NULL){
        bstMinValue(root->left);
    }
	return root;
}

struct bst * bstDelete(struct bst * root, int key) {

   if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left = bstDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = bstDelete(root->right, key);
    }
    
    else {
        if (root->left == NULL) {
            struct bst *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct bst *temp = root->left;
            free(root);
            return temp;
        }
        
        struct bst *temp = bstMinValue(root->right);
        
        root->key = temp->key;
        
        root->right = bstDelete(root->right, temp->key);
    }
    
    return root;
} 
    


void bstFree(struct bst * root) {
    if(root !=NULL){
        bstFree(root->right);
        bstFree(root->left);

    }
    free(root);
}

void bstDisplay(struct bst *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        if (root->right != NULL || root->left != NULL) {
            printf("[");
            bstDisplay(root->right);
            printf("] [");
            bstDisplay(root->left);
            printf("]");
        }

     else {
        printf("[]");
    }
    }
}
