#include <stdio.h>
#include <stdlib.h>
  
// Represents a node
typedef struct node {
    int number;
    struct node *next;
}
node;

struct node *head; // declare as a global so can be accessed anywhere

void insert(int new) {
    struct node *temp = malloc(sizeof(node));
    if (temp == NULL) {
        return;
    }
    temp->number = new;
    temp->next = NULL;
    temp->next = head;
    head = temp;
}

void insertPosition(int new, int position) {
    struct node *temp = malloc(sizeof(node));
    if (temp == NULL) {
        return;
    }
    temp->number = new;
    temp->next = NULL;
    if (position == 1) {
        temp->next = head;
        head = temp;
        return;
    }

    struct node *temp2 = head;
    for (int i = 0; i < position - 2; i++ ) {
        temp2 = temp2->next;
    }
    temp->next = temp2->next;
    temp2->next = temp;
}

void deletePosition(int position) {
    struct node *temp = head;
    if (position == 1) {
        head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; i < position - 2; i++) {
        temp = temp->next;
    }

    struct node *temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
}

void reverse() {
    struct node *prev, *current, *next;
    current = head;
    prev = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

// reverse linked list using recursion
void reverseUsingRecursion(node *lastNode) {
    if(lastNode == NULL) {
        head = lastNode;
        return;        
    }
    reverseUsingRecursion(lastNode->next);
    struct node *p = lastNode->next;
    p->next = lastNode;
    lastNode->next = NULL;
}

void print() {
    struct node *print = head;
    printf("List is: ");
    while (print != NULL) {
        printf(" %d", print->number);
        print = print->next;
    }
    printf("\n");
}

// print linked list using recursion
void printUsingRecursion(node *print) {
    if(print != NULL) {
        printf("%d ", print->number);
        printUsingRecursion(print->next);
    }
    printf("\n");
    return;
}

int main() {
    head = NULL;

    int x, y;
    printf("How many number?\n");
    scanf("%d", &x);
    for(int i = 0; i < x; i++ ) {
        printf("Enter the number:\n");
        scanf("%d", &y);
        insert(y);
        print();
    }

    insertPosition(45, 3);
    print();

    deletePosition(4);
    print();

    reverse();
    print();

    struct node *freePointer = head;
    while (freePointer != NULL)
    {
        struct node *holderPointer = freePointer->next; // we need a second pointer because of to hold the next place when we free the freePointer
        free(freePointer); // free print_pointer which is pointed to the first memory location in the list
        freePointer = holderPointer; // pointed to the next memory location for to free in the next iteration.
    }

    /*
    ==46== HEAP SUMMARY:
    ==46==     in use at exit: 0 bytes in 0 blocks
    ==46==   total heap usage: 9 allocs, 9 frees, 2,160 bytes allocated
    ==46==
    ==46== All heap blocks were freed -- no leaks are possible
    */
}