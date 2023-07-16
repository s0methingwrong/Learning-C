#include <stdlib.h>
#include <string.h>
#include "table.h"

void initTable(Table * t, unsigned int size) {
    t->keyArr = malloc(sizeof(char *)*size);
    int i;
    for(i = 0; i < size; i++)
        t->keyArr[i] = NULL;
    t->size = size;
}

void addToTable(Table * t, const char * key, int idx) {
    char * cpkey = malloc(sizeof(char)*(strlen(key)+1));
    strcpy(cpkey, key);
    t->keyArr[idx] = cpkey;
}

void clearTable(Table * t) {
    int i;
    for(i = 0; i < t->size; i++)
        if(t->keyArr[i])
            free(t->keyArr[i]);
}

char * getTableKey(Table * t, int idx) {
    return t->keyArr[idx];
}

int getTabelIdx(Table * t, char * key) {
    int i;
    for(i = 0; i < t->size; i++) {
        if(strcmp(t->keyArr[i], key) == 0)
            return i;
    }
    return -1;
}