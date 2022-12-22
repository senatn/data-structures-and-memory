#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represents a node
typedef struct treeNode {
    int value;
    struct treeNode *left;
    struct treeNode *right;
}
treeNode;

// Create a new node function
treeNode *createNode(int value){
    treeNode *result = malloc(sizeof(treeNode)); // Allocate on the heap a new tree node
    if (result != NULL){  // if malloc succeeded
        result->value = value; // set the value
        result->left = NULL; // initializing left and right child to be null so not pointing to anything 
        result->right = NULL;
    }
    return result;
}
 //when printing the tree, indent the line based on the level that we are at
void printTabs(int tabs){
    for (int i = 0; i < tabs; i++){
        printf("\t");
    }
}

void printTree(treeNode *root, int tabLevel){
    if(root == NULL){
        printTabs(tabLevel);
        printf("<empty>\n");
        return;
    }
    /* Trees can be traversed in different ways.
    i'm gonna do today is called preorder traversal
    1. visit the root
    2. traverse the left subtree
    3. traverse the right subtree */

    printTabs(tabLevel);
    printf("value = %i\n", root->value);
    
    printTabs(tabLevel);
    printf("left = \n");
    printTree(root->left, tabLevel + 1); //when dealing with tree is you often benefit from doing things recursively
    
    printTabs(tabLevel);
    printf("rigth = \n");
    printTree(root->right, tabLevel + 1);

}

/* I use double pointer because if the tree is null i need to be able to
change the adress that the root pointer points to. With a singe pointer 
we would not be able to that  */
bool insertNumber(treeNode **rootptr, int value){
    treeNode *root = *rootptr; // I create a pointer which is pointing to the root pointer points to

    if (root == NULL) {
        // that means our tree is emty so set our root pointer to a new node
        (*rootptr) = createNode(value); // basicly creating a new root for the tree
        return true; // return true because we insert a new node at the tree
    }

    if (value == root->value) {
        return false; // do notings is just a decision. if value is alredy in tree no need to add again. only allow a value once
    }

    if (value < root->value) {
        return insertNumber(&(root->left), value); // if value is smaller then root value, recurcifly call our function and as
    }

    else {
        return insertNumber(&(root->right), value);
    }

}

bool findNumber(treeNode *root, int value) {
    if (root == NULL) {
        return false;
    }
    
    if (value == root->value) {
        return true;
    }

    if (value < root->value) {
        return findNumber(root->left, value);
    }
    
    else {
        return findNumber(root->right, value);
    }

}

void freeTree (treeNode *freeNode) {
    if (freeNode == NULL) {
        return;
    }
    freeTree(freeNode->left);
    freeTree(freeNode->right);
    free(freeNode);
}

int main(void)
{
    treeNode *root = NULL;

    insertNumber(&root, 15);
    insertNumber(&root, 11);
    insertNumber(&root, 24);
    insertNumber(&root, 5);
    insertNumber(&root, 19);
    insertNumber(&root, 16);
    
    printTree(root, 0);

    printf("%d (%d)\n", 16, findNumber(root, 16));
    printf("%d (%d)\n", 44, findNumber(root, 44));

    freeTree(root);

    /*
    ==170== HEAP SUMMARY:
    ==170==     in use at exit: 0 bytes in 0 blocks
    ==170==   total heap usage: 7 allocs, 7 frees, 1,168 bytes allocated
    ==170==
    ==170== All heap blocks were freed -- no leaks are possible
    */
}