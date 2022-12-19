#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 101

char stack[MAX_SIZE];
int top = -1; // means is emty stack


void push (char c) {
    if(top == MAX_SIZE -1) { // for handle overflow
        printf("Error: stack overflow\n");
        return;
    }
    stack[++top] =c;  // ++top means: increment will happen before assignment
                        // top++;
                        // stack[top] = c; 
}

void pop () {
    if(top == -1) { // if list is empty
        printf("Error: no element to pop\n");
        return;
    }
    top--;
}

int checkBalancedParentheses(char *expression, int lenght) {
    for (int i = 0; i < lenght; i++) {
        char c = expression[i];
        if (c == '(' || c ==  '{' || c == '[') {
            push(c);
        }
        else if (c == ')' || c ==  '}' || c == ']') {
            if (top == -1) {
                printf("Expression is not balanced\n");
                return 0;
            }
            char topStack = stack[top--];
            if ((c != ')' && topStack == '(') || (c != '}' && topStack == '{') || (c != ']' && topStack == '[')) {
                printf("Expression is not balanced\n");
                return 0;
            }
        }
    }
    if(top == -1){
        printf("Expression is balanced\n");
        return 0;
    }
    else {
        printf("Expression is not balanced\n");
        return 0;
    }
    return 0;    
    
}

int main(void) {
    // Get a expression from the user
    char expression[MAX_SIZE];
    printf("Enter an expression to check for balanced parentheses: ");
    scanf("%[^\n]s", expression);
    int lenght = strlen(expression);

    checkBalancedParentheses(expression, lenght);
    return 0;
}