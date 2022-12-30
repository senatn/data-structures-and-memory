#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

int findHeight(treeNode *root) {
    if (root == NULL) {
        return -1;
    }
    return max(findHeight(root->left), findHeight(root->right)) +1;
}

bool isSubTreeLesser(treeNode *root, int value) {
    if (root == NULL) {
        return true;
    }
    if (root->value <= value
        && isSubTreeLesser(root->left, value)
        && isSubTreeLesser(root->right, value)) {
            return true;
        }
        else {
            return false;
        }
}
bool isSubTreeGreater(treeNode *root, int value) {
    if (root == NULL) {
        return true;
    }
    if (root->value >= value
        && isSubTreeGreater(root->left, value)
        && isSubTreeGreater(root->right, value)) {
            return true;
        }
        else {
            return false;
        }
}

bool isBinarySearchTree (treeNode *root) {
    if (root == NULL) {
        return true;
    }
    if (isSubTreeLesser(root->left, root->value) 
    && isSubTreeGreater(root->right, root->value)
    && isBinarySearchTree(root->left)
    && isBinarySearchTree(root->right)) {
        return true;
      }
      else {
        return false;
      }
} // time complexity is O(n^2)

/*isSubTreeLesser and isSubTreeGreater functions are very expensive
for each node we are looking at all nodes in subtrees 
a more efficient solution is below */

bool isBinarySearchTreeEfficientSolution (treeNode *root, int minValue, int maxValue) {
    if (root == NULL) {
        return true;
    }
    if (root->value > minValue && root->value < maxValue
    && isBinarySearchTreeEfficientSolution(root->left, minValue, root->value)
    && isBinarySearchTreeEfficientSolution(root->right, root->value, maxValue)) {
        return true;
      }
      else {
        return false;
      }
} // time complexity is O(n)

// left, data, right
void inorderTraversal(treeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d  ", root->value);
        inorderTraversal(root->right);
    }
}

// data, left, right
void preorderTraversal(treeNode *root) {
    if (root != NULL) {
        printf("%d  ", root->value);
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
} 

// left, right, data
void postorderTraversal(treeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);

        inorderTraversal(root->right);
        printf("%d  ", root->value);
    }
}

treeNode *findMinimum(treeNode *currentNode) {
    if(currentNode->left == NULL) return currentNode;
    return findMinimum(currentNode->left);
}

treeNode *findMaximum(treeNode *currentNode) {
    if(currentNode->right == NULL) return currentNode;
    return findMaximum(currentNode->right);
}

treeNode *findNode(treeNode *currentNode, int value) {
    if(currentNode->value == value) return currentNode;
    else if (currentNode->value < value) return findNode(currentNode->right, value);
    else if (currentNode->value > value) return findNode(currentNode->left, value);
    return currentNode;
}

treeNode *getSuccessor(treeNode *root, int value) {
    treeNode *current = findNode(root, value); // O(h)
    if(current == NULL) return NULL;
    if(current == findMaximum(root)) return current; //??
    if(current->right != NULL) {
        return findMinimum(current->right); // O(h)
    }
    else if (current->right == NULL) {
        treeNode *after = NULL;
        treeNode *before = root;
        while(before != current) {
            if(current->value < before->value) {
                after = before; //
                before = after->left;
            }
            else {
                before = before->right;
            }
        }
        return after;
    }
}

treeNode *delete(treeNode *root, int value) {
    if(root == NULL) return root;
    else if(value < root->value) root->left = delete(root->left, value);
    else if(value > root->value) root->right = delete(root->right, value);
    else {
        // no child
        if(root->left == NULL && root->right == NULL) {
            free(root); // delete function returning a pointer but now root is a dangling pointer and I cannot set it as a return value.
            root = NULL; // For this, I assigned NULL to the root pointer.
            return root; // and i returned
        }
        // one right child
        else if(root->left == NULL) {
            treeNode *temp = root->right;
            free(root);
            return temp;
        }
        // one left child
        else if(root->right == NULL) {
            treeNode *temp = root->left;
            free(root);
            return temp;
        }
        // 2 children
        else {
            treeNode *temp = findMinimum(root->right);
            root->value = temp->value;
            root->right = delete(root->right, temp->value);
            return root;
        }
    }
    return root;
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
    root = insertNumber(root, 28);
    root = insertNumber(root, 25);
    root = insertNumber(root, 30);
    
    printTree(root, 0);

    int p = findHeight(root);
    printf("\nheight = %d", p);

    if (isBinarySearchTree(root) == true) {
        printf("\nit is a BST");
    }

    if (isBinarySearchTreeEfficientSolution(root, INT_MIN, INT_MAX) == true) {
        printf("\nit is a BST");
    }
    printf("\nInorder Traversal: ");
    inorderTraversal(root);

    delete(root, 15);

    // printf("\ndelete function: %d" , delete(root, 28)->value);

    printf("\nInorder Traversal: ");
    inorderTraversal(root);

    printf("\nSuccessor of 19: %d" , getSuccessor(root, 19)->value);

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);

    printf("\nPostorder Traversal: ");
    postorderTraversal(root);

    freeTree(root);

    /*
    ==46== HEAP SUMMARY:
    ==46==     in use at exit: 0 bytes in 0 blocks
    ==46==   total heap usage: 10 allocs, 10 frees, 1,240 bytes allocated
    ==46==
    ==46== All heap blocks were freed -- no leaks are possible
    */
}