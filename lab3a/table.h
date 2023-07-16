#ifndef TABLE_H
#define TABLE_H

typedef unsigned int KeyType;

typedef int InfoType;

typedef int RelType; 

typedef struct KeySpace {
    KeyType key;
    RelType release;
    InfoType *info;
    struct KeySpace *next; 
}KeySpace;


typedef struct Table {
    KeySpace **ks;
    int msize;
    int csize;
}Table;

// interface

void initTable(Table * table, int msize);

void addToKeySpace(Table * table, KeyType key, InfoType * info);

void deleteFromKeySpace(Table * table, KeyType key);

void deleteKSByRel(Table * table, KeyType key, RelType rel);

KeySpace * searchByKey(Table * table, KeyType key);

KeySpace * searchByKeyAndByRel(Table * table, KeyType key, RelType rel);


// utils

unsigned int hash_int(unsigned int key, int msize);

KeySpace * deleteCurrentAndGetNext(KeySpace * ks);

void freeKS(KeySpace * ks);

KeySpace * ksDeepCopy(KeySpace * ks);

InfoType * infoDeepCopy(InfoType * info);

#endif
