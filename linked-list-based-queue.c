#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //to make the bool function work

typedef struct node {
    int number;
    struct node *next;
} node;

node *front = NULL;
node *rear = NULL;

void enQueue (int addingNumber) {
    node *newNode = malloc(sizeof(node));
    newNode->number = addingNumber;
    newNode->next = NULL;
    if (isEmty () == true) {
        front = newNode;
        rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

void deQueue () {
    node *deletedNode = front; // we will use that temp node for free previous head node
    if ( front == NULL) return;
    if ( front == rear) {
        front = rear = NULL;
    }
    front = front->next;
    free(deletedNode);
}

bool isEmty () {
    if ( front == NULL && rear == NULL) {
        return true;
    }
    return false;
}