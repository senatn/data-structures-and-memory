#include <stdio.h>
#include <stdlib.h>
  
// Represents a node
typedef struct node
{
    int number;
    struct node *next;
}
node;
//vbnm
//program will take command line arguments and I want my program allocate nodes and stitch them together
int main(int argc, char *argv[])
{
    node *list = NULL; // this is just my pointer

    for (int i = 1; i < argc; i++) // i start at 1 instead of 0 because argv[0] is the name of program
    {
        int assigned_number = atoi(argv[i]); // atoi is ascii to intiger

        // n is a temporary pointer    
        node *n = malloc(sizeof(node));
        // thats going to return the address of that chunk of memory 
        // pointer n got a garbage value by default and we have got a node somewhere in memory 

        // it is required to check whether the malloc() was successful or not
        if (n == NULL) // If malloc fails
        {
            return 1;  // and we’ll exit our program with return 1
        }
        /* There is a bug in the above codes actually, if the malloc fails at the second call or any call exept first,
        you need to free any notes that you did allocate successfully earlier. 
        And Valgrind wouldn`t help to find it this memory leak. When I run valgrind it says 
        All heap blocks were freed -- no leaks are possible ¯\_(ツ)_/¯ */

        n->number = assigned_number;
        n->next = NULL;
        n->next = list; // this line useless for the first iteration but after first allocation                       
                        // every time we add a new node, new node points to current begining of the list
        list = n;       // update the actual list to point at this new node. 
    }

    // for print all list, declare a temporary pointer
    node *print_pointer = list; // it's not pointing at list per se it's pointing at he firs node in the list. ( list also a pointer)
    while (print_pointer != NULL)
    {
        printf("%i\n", print_pointer->number);
        print_pointer = print_pointer->next; // print_pointer is now pointing at the second node
    }

    print_pointer = list;
    while (print_pointer != NULL)
    {
        node *holder_pointer = print_pointer->next; // we need a second pointer because of to hold the next place when we free the print_pointer
        free(print_pointer); // free print_pointer which is pointed to the first memory location in the list
        print_pointer = holder_pointer; // pointed to the next memory location for to free in the next iteration.
    }
}