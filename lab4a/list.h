#ifndef LIST_H
#define LIST_H

typedef unsigned int InfoType;

typedef struct ListNode {
    InfoType info;
    struct ListNode * next;
    struct ListNode * prev;
}ListNode;

typedef struct List {
    ListNode * head;
    ListNode * tail;
    unsigned int size;
}List;

void initList(List * list);
void push(List * list, InfoType info);
void pop(List * list); 
InfoType top(List * list);
ListNode * getListNodeBySeqNum(List * list, int sn);
void freeList(List * list);
void popback(List * list);

#endif