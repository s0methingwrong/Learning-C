#include <stdlib.h>
#include <string.h>
#include "item_types.h"

int kt1cmp(KeyType1 k1, KeyType1 k2) {
    return strcmp((const char*)k1, (const char*)k2);
}

int kt2cmp(KeyType2 k1, KeyType2 k2) {
    return strcmp((const char*)k1, (const char*)k2);
}

int itemcmp(Item * it1, Item * it2) {
    int kt1_cmp = kt1cmp(it1->key1, it2->key1);
    if(kt1_cmp != 0)
        return kt1_cmp;

    return kt2cmp(it1->key2, it2->key2); 
}

Item * createItem(KeyType1 k1, KeyType2 k2, InfoType info) {
    Item * item = malloc(sizeof(Item));
    if(k1) {
        item->key1 = malloc(sizeof(KeyType1) * (strlen((const char *)k1) + 1));
        strcpy((char *)(item->key1), (const char *)k1);
    } else 
        item->key1 = "";
    if(k2) {
        item->key2 = malloc(sizeof(KeyType2) * (strlen((const char *)k2) + 1));
        strcpy((char *)(item->key2), (const char *)k2);
    } else
        item->key2 = "";
    item->info = info;

    return item;
}

void freeItem(Item * item) {
    if(!item)
        return;
    if(item->key1)
        free((void *)(item->key1));
    if(item->key2)
        free((void *)(item->key2));
    free(item);
}

int lnkt2cmp(ListNodeKt2 * ln1, ListNodeKt2 * ln2) {
    return kt2cmp(ln1->key2, ln2->key2);
}

void pushKt2(ListKt2 * list, KeyType2 key2) {
    ListNodeKt2 * ln = malloc(sizeof(ListNodeKt2));
    ln->key2 = key2;
    ln->next = NULL;
    ln->prev = NULL;

    if(list->size == 0) {
        pushLnKt2ToHead(list, ln);
        return;
    }

    if(lnkt2cmp(ln, list->head) <= 0) {
        pushLnKt2ToHead(list, ln);
        return;
    }

    if(lnkt2cmp(ln, list->tail) > 0) {
        pushLnKt2ToTail(list, ln);
        return;
    }

    ListNodeKt2 * cur = list->head;
    while(lnkt2cmp(ln, cur) > 0)
        cur = cur->next;
    pushLnKt2BeforeCur(list, ln, cur);
}

void pushLnKt2ToHead(ListKt2 * list, ListNodeKt2 * ln) {
    if(list->size == 0) {
        list->head = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    if(lnkt2cmp(ln, list->head) <= 0) {
        ln->next = list->head;
        list->head->prev = ln;
        list->head = ln;
        list->size++;
        return;
    }

    return;
}

void pushLnKt2ToTail(ListKt2 * list, ListNodeKt2 * ln) {
    if(list->size == 0) {
        list->head = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    if(lnkt2cmp(ln, list->tail) > 0) {
        ln->prev = list->tail;
        list->tail->next = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    return;
}

void pushLnKt2BeforeCur(ListKt2 * list, ListNodeKt2 * ln, ListNodeKt2 * cur) {
    ln->prev = cur->prev;
    ln->next = cur;
    cur->prev->next = ln;
    cur->prev = ln;
    list->size++;
}

void popfrontKt2(ListKt2 * list) {
    if(!list)
        return;
    if(!list->head)
        return;
    if(list->size == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }

    ListNodeKt2 * todel = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->size--;
    free(todel);
}

void freeListKt2(ListKt2 * list) {
    if(!list)
        return;
    while(list->size > 0)
        popfrontKt2(list);
    free(list);
}

ListKt2 * createListKt2() {
    ListKt2 * list = malloc(sizeof(ListKt2));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

KeyType2 getMedianListKt2(ListKt2 * list) {
    if(!list)
        return NULL;
    if(list->size == 0)
        return NULL;
    ListNodeKt2 * cur = list->head;
    unsigned int c = list->size/2;
    while(c--)
        cur = cur->next;
    return cur->key2;
}