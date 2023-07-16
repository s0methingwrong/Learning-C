#include <stdlib.h>
#include "table.h"

void initTable(Table * table, int msize) {
    table->ks = malloc(sizeof(KeySpace*)*msize);
    int i;
    table->csize = 0;
    for(i = 0; i < msize; i++)
        table->ks[i] = NULL;
}

unsigned int hash_int(unsigned int key, int msize) {
    static unsigned int a = 101;
    static unsigned int b = 43;
    static unsigned int p = 97;

    return  ((a * key + b) * p) % (unsigned int)msize;
}

void addToKeySpace(Table * table, KeyType key, InfoType * info) {
    unsigned int hash = hash_int(key, table->msize);
    if(table->ks[hash] == NULL) {
        table->ks[hash] = malloc(sizeof(KeySpace));
        table->ks[hash]->key = key;
        table->ks[hash]->release = 1;
        table->ks[hash]->info = info;
        table->csize++;
        return;
    }
    KeySpace * tmp = table->ks[hash];
    while(tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(KeySpace));
    tmp->next->key = key;
    tmp->next->release = tmp->release + 1;
    tmp->next->info = info;
    table->csize++;
}

void deleteFromKeySpace(Table * table, KeyType key) {
    unsigned int hash = hash_int(key, table->msize);
    if(table->ks[hash] == NULL)
        return;
    if(table->ks[hash]->key != key) 
        return;
    while((table->ks[hash] = deleteCurrentAndGetNext(table->ks[hash])))
        table->csize--;
}

KeySpace * deleteCurrentAndGetNext(KeySpace * ks) {
    if(!ks)
        return NULL;
    KeySpace * tmp = ks->next;
    freeKS(ks);
    return tmp;
}

void freeKS(KeySpace * ks) {
    if(!ks)
        return;
    if(ks->info)
        free(ks->info);
    free(ks);
}

void deleteKSByRel(Table * table, KeyType key, RelType rel) {
    unsigned int hash = hash_int(key, table->msize);
    if(table->ks[hash] == NULL)
        return;
    if(table->ks[hash]->key != key) 
        return;
    if(table->ks[hash]->release == rel) {
        table->ks[hash] = deleteCurrentAndGetNext(table->ks[hash]);
        table->csize--;
        return;
    }
    KeySpace * prev = table->ks[hash];
    KeySpace * cur = prev->next;
    while(cur) {
        if(cur->release == rel) {
            prev->next = deleteCurrentAndGetNext(cur);
            table->csize--;
            return;
        }
        cur = cur->next;
        prev = prev->next;
    }
}

KeySpace * searchByKey(Table * table, KeyType key) {
    unsigned int hash = hash_int(key, table->msize);
    if(table->ks[hash] == NULL)
        return NULL;
    if(table->ks[hash]->key != key) 
        return NULL;
    return ksDeepCopy(table->ks[hash]);
}

KeySpace * searchByKeyAndByRel(Table * table, KeyType key, RelType rel) {
    unsigned int hash = hash_int(key, table->msize);
    if(table->ks[hash] == NULL)
        return NULL;
    if(table->ks[hash]->key != key) 
        return NULL;
    if(table->ks[hash]->release == rel)
        return ksDeepCopy(table->ks[hash]);
    KeySpace * cur = table->ks[hash];
    while(cur) {
        if(cur->release == rel) {
            return ksDeepCopy(cur);
        }
        cur = cur->next;
    }
    return NULL;
}

KeySpace * ksDeepCopy(KeySpace * ks) {
    if(!ks)
        return NULL;
    KeySpace * tmp = malloc(sizeof(KeySpace));
    tmp->key = ks->key;
    tmp->release = ks->release;
    tmp->info = infoDeepCopy(ks->info);
    tmp->next = ks->next;
    return tmp;
}

InfoType * infoDeepCopy(InfoType * info) {
    if(!info)
        return NULL;
    InfoType * tmp = malloc(sizeof(InfoType));
    *tmp = *info;
    return tmp;
}
