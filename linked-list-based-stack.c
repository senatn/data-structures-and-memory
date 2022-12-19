/*--------------linked list based implementation--------------*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char data;
  struct node *next;
} node;

// Stack structure
typedef struct stack {
  node *top;
} stack;

// Function to create a new node
node* createNode(char data) {
  node *newNode = malloc(sizeof(node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// function to create a new stack
stack* createStack() {
  stack *stack = malloc(sizeof(stack));
  stack->top = NULL;
  return stack;
}

// function to check if the stack is empty
int isEmpty(stack *stack) {
  return !stack->top; // the !stack->top expression will be equal to 1 if stack->top is NULL (if the stack is empty), and 0 if stack->top is not NULL (if the stack is not empty).
}

// function to push a new element onto the stack
void push(stack *stack, char data) {
  node *newNode = createNode(data);
  newNode->next = stack->top;
  stack->top = newNode;
}

// function to pop an element from the stack
char pop(stack *stack) {
  if (isEmpty(stack)) {
    return '\0';
  }
  node *temp = stack->top;
  char data = temp->data;
  stack->top = stack->top->next;
  free(temp);
  return data;
}

int main(void) {
  // Create a new stack
  stack *stack = createStack();

  // Get a sentence from the user
  char sentence[100];
  printf("Enter a sentence: ");
  scanf("%[^\n]s", sentence);

  // Push each character of the sentence onto the stack
  for (int i = 0; i < strlen(sentence); i++) {
    push(stack, sentence[i]);
  }

  // Pop each character from the stack and print it
  printf("Reversed sentence: ");
  while (!isEmpty(stack)) {
    printf("%c", pop(stack));
  }
  printf("\n");

  return 0;
}