#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H

#define DEFAULT_INFO 0

typedef const char * KeyType1;
typedef const char * KeyType2;
typedef unsigned int InfoType;

typedef struct ListNodeKt2 {
    KeyType2 key2;
    struct ListNodeKt2 * next;
    struct ListNodeKt2 * prev;
}ListNodeKt2;

typedef struct ListKt2 {
    ListNodeKt2 * head;
    ListNodeKt2 * tail;
    unsigned int size;
}ListKt2;

typedef struct Item {
    KeyType1 key1;
    KeyType2 key2;
    InfoType info;
}Item;

int kt1cmp(KeyType1 k1, KeyType1 k2);
int kt2cmp(KeyType2 k1, KeyType2 k2);
int itemcmp(Item * it1, Item * it2);
Item * createItem(KeyType1 k1, KeyType2 k2, InfoType info);
void freeItem(Item * item);

int lnkt2cmp(ListNodeKt2 * ln1, ListNodeKt2 * ln2);

void pushKt2(ListKt2 * list, KeyType2 key2);

void pushLnKt2ToHead(ListKt2 * list, ListNodeKt2 * ln);

void pushLnKt2ToTail(ListKt2 * list, ListNodeKt2 * ln);

void pushLnKt2BeforeCur(ListKt2 * list, ListNodeKt2 * ln, ListNodeKt2 * cur);

void freeListKt2(ListKt2 * list);

void popfrontKt2(ListKt2 * list);

ListKt2 * createListKt2();

KeyType2 getMedianListKt2(ListKt2 * list);

#endif