#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Typeof.html#Typeof
// https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html#Statement-Exprs
// https://stackoverflow.com/questions/3437404/min-and-max-in-c
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

// Represents a node
typedef struct treeNode {
    int value;
    struct treeNode *left;
    struct treeNode *right;
}
treeNode;

// Create a new node function
treeNode *createNode(int value){
    treeNode *newNode = malloc(sizeof(treeNode)); // Allocate on the heap a new tree node
    if (newNode != NULL){  // if malloc succeeded
        newNode->value = value; // set the value
        newNode->left = NULL; // initializing left and right child to be null so not pointing to anything 
        newNode->right = NULL;
    }
    return newNode;
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

treeNode *insertNumber(treeNode *root, int value){
    if (root == NULL) {
        root = createNode(value); 
    }
    else if (value <= root->value) {
        root->left = insertNumber(root->left, value); 
    }
    else {
        root->right = insertNumber(root->right, value);
    }
    return root;
}

int findHeight(treeNode **root) {
    if (*root == NULL) {
        return -1;
    }
    return max(findHeight(&(*root)->left), findHeight(&(*root)->right)) +1;
}

bool isSubTreeLesser(treeNode **root, int value) {
    if ((*root) == NULL) {
        return true;
    }
    if ((*root)->value <= value
        && isSubTreeLesser(&(*root)->left, value)
        && isSubTreeLesser(&(*root)->right, value)) {
            return true;
        }
        else {
            return false;
        }
}
bool isSubTreeGreater(treeNode **root, int value) {
    if ((*root) == NULL) {
        return true;
    }
    if ((*root)->value >= value
        && isSubTreeGreater(&(*root)->left, value)
        && isSubTreeGreater(&(*root)->right, value)) {
            return true;
        }
        else {
            return false;
        }
}

bool isBinarySearchTree (treeNode **root) {
    if ((*root) == NULL) {
        return true;
    }
    if (isSubTreeLesser(&(*root)->left, (*root)->value) 
      && isSubTreeGreater(&(*root)->right, (*root)->value)
      && isBinarySearchTree(&(*root)->left)
      && isBinarySearchTree(&(*root)->right)) {
        return true;
      }
      else {
        return false;
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

    root = insertNumber(root, 15); 
    root = insertNumber(root, 11);
    root = insertNumber(root, 24);
    root = insertNumber(root, 5);
    root = insertNumber(root, 19);
    root = insertNumber(root, 16);
    
    printTree(root, 0);

    int p = findHeight(&root);
    printf("\nheight = %d", p);

    if (isBinarySearchTree(&root) == true) {
        printf("\nit is a BST");
    }

    freeTree(root);

    /*
    ==170== HEAP SUMMARY:
    ==170==     in use at exit: 0 bytes in 0 blocks
    ==170==   total heap usage: 7 allocs, 7 frees, 1,168 bytes allocated
    ==170==
    ==170== All heap blocks were freed -- no leaks are possible
    */
}