/*----------------array based implementation----------------*/ 

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101

int A[MAX_SIZE];
int top = -1; // means is emty stack

void push (int number) {
    if(top == MAX_SIZE -1) { // for handle overflow
        printf("Error: stack overflow\n");
        return;
    }
    A[++top] = number;  // ++top means: increment will happen before assignment
                        // top++;
                        // A[top] = number; 
}

void pop () {
    if(top == -1) { // if list is empty
        printf("Error: no element to pop\n");
        return;
    }
    top--;
}

int Top() {
    return A[top];
}

void print () {
    printf("Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    push(8);
    print();
    push(4);
    print();
    push(6);
    print();
    push(2);
    print();
    pop();
    print();
    push(16);
    print();
    return 0;
}