#ifndef LIST_H
#define LIST_H

#include "item_types.h"

typedef struct ListNode {
    Item * item;
    struct ListNode * next;
    struct ListNode * prev;
}ListNode;

typedef struct List {
    ListNode * head;
    ListNode * tail;
    unsigned int size;
}List;

//interface

List * createList();

void push(List * list, Item * item);

void pushback(List * list, Item * item);

Item * top(List * list);

void popfront(List * list); // without deleting the item

List * findAll(List * list, KeyType1 k1, KeyType2 k2);

void freeList(List * list); // without deleting items

void freeListWithItems(List * list); // with deleting items

void delLnWithSeqNumDelItem(List * list, KeyType1 k1, KeyType2 k2, int sn);

void splitIn2ListsByKt1(List * src, List * dst1, List * dst2, KeyType1 k1); // dst1 and dst2 must be empty

void splitIn2ListsByKt2(List * src, List * dst1, List * dst2, KeyType2 k2); // dst1 and dst2 must be empty

KeyType1 getMedianListByKt1(List * list);

KeyType2 getOverageMedianByKt2(List * src1, List * src2);

ListKt2 * getListKt2(List * list);

//utils

int lncmp(ListNode * ln1, ListNode * ln2); // compare two nodes, return -1 if ln1 < ln2, 0 if ln1 = ln2 and 1 else

void freeln(ListNode * ln); // also free item

void pushLnToHead(List * list, ListNode * ln);

void pushLnToTail(List * list, ListNode * ln);

void pushLnBeforeCur(List * list, ListNode * ln, ListNode * cur);

void popfrontWithFreeItem(List * list);

ListNode * findFirstLn(List * list, KeyType1 k1, KeyType2 k2);

void delLn(List * list, ListNode * ln); // with deleting item

#endif