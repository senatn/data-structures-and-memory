#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
    char name[MAX_NAME];
    int age;
    /* add other data */
    struct person *next;
} person;

person *hashTable[TABLE_SIZE];

unsigned int hash(char *name) {
    int lenght = strlen(name);
    unsigned int hashValue = 0;
    for (int i = 0; i < lenght; i++) {
        hashValue += name[i];
        hashValue = (hashValue * name[i]) % TABLE_SIZE;
    }
    return hashValue;
}

// for initilaze empty table
void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

bool initTablePerson (person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hashTable[index];
    hashTable[index] = p;
    return true;
}

// find a person in the table by their name
person *hashTableLookup (char *name) {
    int index = hash(name);
    person *tmp = hashTable[index];
    while (tmp != NULL && strcmp(tmp->name, name) != 0 ) {
        tmp = tmp->next;
    }
    return tmp;
}

person *hashTableDelete (char *name) {
    int index = hash(name);
    person *tmp = hashTable[index];
    person *prev = NULL;
    while (tmp != NULL && strcmp(tmp->name, name) != 0 ) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) {
        return NULL;
    }
    if (prev == NULL) {
        hashTable[index] = tmp->next;
    }
    else {
        prev->next = tmp->next;
    }
    return tmp;
}

void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == NULL) {
            printf("\t%i\t---\n", i);
        }
        else {
            printf("\t%i\t", i);
            person *tmp = hashTable[i];
            while (tmp != NULL) {
                printf("%s - ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

int main() {
    initHashTable();

    person jacob = {.name = "jacob", .age = 21};
    person kate = {.name = "kate", .age = 27};
    person mpho = {.name = "mpho", .age = 14};
    person alice = {.name = "alice", .age = 28};
    person george = {.name = "george", .age = 22};
    person brian = {.name = "brian", .age = 16};
    person david = {.name = "david", .age = 29};
    person eric = {.name = "eric", .age = 22};
    person robert = {.name = "robert", .age = 13};

    initTablePerson(&jacob);
    initTablePerson(&kate);
    initTablePerson(&mpho);
    initTablePerson(&alice);
    initTablePerson(&george);
    initTablePerson(&brian);
    initTablePerson(&david);
    initTablePerson(&eric);
    initTablePerson(&robert);

    printTable();
    
    person *tmp = hashTableLookup("alice");
    if (tmp == NULL) {
        printf("Not Found\n");
    }
    else {
        printf("Found %s\n", tmp->name);
    }

    person *tmp2 = hashTableLookup("mpho");
    if (tmp2 == NULL) {
        printf("Not Found\n");
    }
    else {
        printf("Found %s\n", tmp2->name);
    }

    hashTableDelete("mpho");
    person *tmp3 = hashTableLookup("mpho");
    if (tmp3 == NULL) {
        printf("Not Found\n");
    }
    else {
        printf("Found %s\n", tmp2->name);
    }

    printTable();

    return 0;
}