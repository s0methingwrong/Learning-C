#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
    void * data;
    struct ListNode * next;
    struct ListNode * prev;
}ListNode;

typedef struct List {
    ListNode * head;
    ListNode * tail;
    unsigned int size;
}List;

ListNode * createListNode();
void freeLn(ListNode * ln);

List * createList();
void freeList(List * list);
void freeListDelData(List * list);
void clearList(List * list);
void clearListDelData(List * list);
void pushfront(List * list, void * data);
void pushback(List * list, void * data);
void * front (List * list);
void * back(List * list);
void popfront(List * list);
void popback(List * list);
void popfrontDelData(List * list);
void popbackDelData(List * list);
int inList(List *list, void * data, int (*datacmp)(void * p1, void * p2));
ListNode * findLn(List * list, void * data, int (*datacmp)(void * p1, void * p2));
void popLn(List * list, ListNode * ln);
void concatListAndClear2nd(List * dst, List * src);

#endif