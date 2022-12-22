#include <stdio.h>
#include <stdlib.h>

// Represents a node
typedef struct treenode {
    int value;
    struct treenode *left;
    struct treenode *right;
} treenode;

// Create a new node function
treenode *createnode(int value){
    treenode *result = malloc(sizeof(treenode)); // Allocate on the heap a new tree node
    if (result != NULL){  // if malloc succeeded
        result->left = NULL; // initializing left and right child to be null so not pointing to anything 
        result->right = NULL;
        result->value = value; // set the value
    }
    return result;
}
 //when printing the tree, indent the line based on the level that we are at
void printtabs(int tabs){
    for (int i = 0; i < tabs; i++){
        printf("\t");
    }
}

void printtree(treenode *root, int tabLevel){
    if(root == NULL){
        printtabs(tabLevel);
        printf("<empty>\n");
        return;
    }
    /* Trees can be traversed in different ways.
    i'm gonna do today is called preorder traversal
    1. visit the root
    2. traverse the left subtree
    3/ traverse the right subtree */

    printtabs(tabLevel);
    printf("value = %i\n", root->value);
    
    printtabs(tabLevel);
    printf("left = \n");
    printtree(root->left, tabLevel + 1); //when dealing with tree is you often benefit from doing things recursively
    
    printtabs(tabLevel);
    printf("rigth = \n");
    printtree(root->right, tabLevel + 1);

}

int main(void)
{
    treenode *n1 = createnode(10); // declare a few nodes
    treenode *n2 = createnode(11);
    treenode *n3 = createnode(12);
    treenode *n4 = createnode(13);
    treenode *n5 = createnode(14);
    treenode *n6 = createnode(15);
    treenode *n7 = createnode(16);

    n1->left = n2; //now we have a tree
    n1->right = n3;
    n3->left = n4;
    n3->right = n5;
    n5->left = n6;
    n5->right = n7;

    printtree(n1, 0);

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);
    free(n7);
/*
 ==163== HEAP SUMMARY:
==163==     in use at exit: 0 bytes in 0 blocks
==163==   total heap usage: 8 allocs, 8 frees, 1,192 bytes allocated
==163==
==163== All heap blocks were freed -- no leaks are possible
*/

}