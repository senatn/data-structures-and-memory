#include <stdio.h>
#include <stdlib.h>

// Define a node structure
typedef struct node {
    int number;
    struct node *next;
    struct node *prev;
}
node;

node *head; //global variable

// Create a new node
struct node *getNewNode(int number) {
    node *newNode = malloc(sizeof(node)); // create a new node in heap
    newNode->number = number;
    newNode->next = NULL;
    newNode->prev =NULL;
    return newNode;
}

void print() {
    node *print = head;
    printf("List is: ");
    while (print != NULL) {
        printf(" %d", print->number);
        print = print->next;
    }
    printf("\n");
}

// Insert a new node at the head of the list
void insertAtHead (int number) {
    node *newNode = getNewNode(number);
    if (head == NULL) {
        head = newNode;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
} 

int main() {
    insertAtHead(5);
    insertAtHead(4);
    insertAtHead(9);
    insertAtHead(8);
    print();

    node *freePointer = head;
    while (freePointer != NULL)
    {
        node *holderPointer = freePointer->next; // we need a second pointer because of to hold the next place when we free the freePointer
        free(freePointer); // free print_pointer which is pointed to the first memory location in the list
        freePointer = holderPointer; // pointed to the next memory location for to free in the next iteration.
    }

    /*
    ==47== HEAP SUMMARY:
    ==47==     in use at exit: 0 bytes in 0 blocks
    ==47==   total heap usage: 3 allocs, 3 frees, 1,072 bytes allocated       
    ==47==
    ==47== All heap blocks were freed -- no leaks are possible*/
}