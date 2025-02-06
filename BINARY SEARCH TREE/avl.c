#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int max(int a, int b) {
	if (a>b) {
		return a;
	}
	else {
		return b;
	}
}

struct avl * avlCreateNode(int key) {
    struct avl* new =malloc(sizeof(struct avl));
    new->key=key;
    new->height=1;
    new->right=NULL;
    new->left=NULL;
    return new ;
}



int avlHeight(struct avl * root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return root->height ;
    }

}

int avlGetBalance(struct avl *root) {
    if (root == NULL) {
        return 0;
    } else {
        return avlHeight(root->left) - avlHeight(root->right);
    }
}


struct avl * avlRotateRight(struct avl * x) {
    struct avl *new = x->left;
    struct avl *temp=new->right;
    new->right=x;
    x->left=temp ;
    x->height = max(avlHeight(x->left), avlHeight(x->right)) + 1;

    new->height = max(avlHeight(new->left), avlHeight(new->right)) + 1 ;



    return new ;

}

struct avl * avlRotateLeft(struct avl * x) {
    struct avl *new =x->right;
    struct avl *temp=new->left ;
    new->left=x;
    x->right=temp ;
    x->height = max(avlHeight(x->left), avlHeight(x->right)) + 1;

    new->height = max(avlHeight(new->left), avlHeight(new->right)) + 1 ;
    return new ;
}

struct avl * avlInsert(struct avl * root, int key) {
    if( root == NULL){
        struct avl * new =avlCreateNode(key);
        return new ;
    }
    else{
        if (root->key > key){
           root->left =avlInsert(root->left,key);
        }
        else if(root->key < key) {
            root->right= avlInsert(root->right,key);
            }
        else {
            return root ;
        }
    }
    
    root->height= max(avlHeight(root->left),avlHeight(root->right))+1 ;
    int bal = avlGetBalance(root) ;
    if (root->key < key){
        if (bal == -2 ){
            if (avlGetBalance(root->right)> 0){
                root->right=avlRotateRight(root->right);
                root=avlRotateLeft(root);
            }
            else{
                root=avlRotateLeft(root);
            }
        } }
    else{
        if(bal == 2){
            if(avlGetBalance(root->left) < 0){
                if(avlGetBalance(root->left)<0){
                    root->left=avlRotateLeft(root->left);
                    root=avlRotateRight(root);
                }
                }
            }
        
        else{
            root=avlRotateRight(root);
        }
    }
    return root ;
    
}


struct avl * avlMinValue(struct avl * root) {
    if (root == NULL || root->left == NULL) {
        return root;
    }
    return avlMinValue(root->left);
}

struct avl * avlDelete(struct avl * root, int key) {
    if(root == NULL){
        return NULL ;
        }
    if (key < root->key) {
        root->left = avlDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = avlDelete(root->right, key);
    }
    
    else {
        if (root->left == NULL) {
            struct avl *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct avl *temp = root->left;
            free(root);
            return temp;
        }
        
        struct avl *temp = avlMinValue(root->right);
        
        root->key = temp->key;
        
        root->right = avlDelete(root->right, temp->key);
    }

   if (root == NULL) {
        return root;
    }

    root->height = max(avlHeight(root->left), avlHeight(root->right)) + 1;
    int bal =avlGetBalance(root);
        if (root->key >key){
            if (bal == -2 ){
                if (avlGetBalance(root->right)> 0){
                    root->right=avlRotateRight(root->right);
                    root=avlRotateLeft(root);
                }else{
                    root=avlRotateLeft(root);
                }
                } 
        }else{
            if(bal == 2){
                if(avlGetBalance(root->left) < 0){
                    root->left=avlRotateLeft(root->left);
                    root=avlRotateRight(root);
                }else{
                    root=avlRotateRight(root);
                }
            }
        }
    return root;
}



void avlFree(struct avl * root) {
    if(root!=NULL){
        avlFree(root->right);
        avlFree(root->left);
        free(root);
    }
    
}

void avlDisplay(struct avl * root) {
    if(root!=NULL){
        printf("%d",root->key);
        printf(" [");
        avlDisplay(root->left);
        printf("] [");
        avlDisplay(root->right);
        printf(" ]") ;
    }
    else{
        printf("[]");
    }
}


