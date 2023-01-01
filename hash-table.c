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
    if (hashTable[index] != NULL) {
        return false;
    }
    hashTable[index] = p;
    return true;
}

void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == NULL) {
            printf("\t%i\t---\n", i);
        }
        else {
            printf("\t%i\t%s\n", i, hashTable[i]->name);
        }
    }

}


int main() {
    initHashTable();

    person jacob = {.name = "jacob", .age = 21};
    person kate = {.name = "kate", .age = 27};
    person mpho = {.name = "mpho", .age = 14};

    initTablePerson(&jacob);
    initTablePerson(&kate);
    initTablePerson(&mpho);

    printTable();
    return 0;
}