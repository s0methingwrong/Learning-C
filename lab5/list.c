#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List * createList() {
    List * list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void freeList(List * list) {
    clearList(list);
    free(list);
}

void freeListDelData(List * list) {
    clearListDelData(list);
    free(list);
}

void pushfront(List * list, void * data) {
    ListNode * ln = createListNode();
    ln->data = data;

    if(list->size == 0) {
        list->head = ln;
        list->tail =  ln;
        list->size++;
        return;
    }

    ln->next = list->head;
    list->head->prev = ln;
    list->head = ln;
    list->size++;
}

void pushback(List * list, void * data) {
    ListNode * ln = createListNode();
    ln->data = data;

    if(list->size == 0) {
        list->head = ln;
        list->tail =  ln;
        list->size++;
        return;
    }

    ln->prev = list->tail;
    list->tail->next = ln;
    list->tail = ln;
    list->size++;
}

void * front (List * list) {
    return list->head->data;
}

void * back(List * list) {
    return list->tail->data;
}

void popfront(List * list) {
    ListNode * tmp = list->head;
    list->head = list->head->next;
    if(list->head)
        list->head->prev = NULL;
    freeLn(tmp);
    if(list->size == 1) {
        list->tail = list->head;
    }
    list->size--;
}

void popback(List * list) {
    ListNode * tmp = list->tail;
    list->tail = list->tail->prev;
    if(list->tail)
        list->tail->next = NULL;
    freeLn(tmp);
    if(list->size == 1) {
        list->head = list->tail;
    }
    list->size--;
}

void popfrontDelData(List * list) {
    void * data = front(list);
    if(data)
        free(data);
    popfront(list);
}

void popbackDelData(List * list) {
    void * data = back(list);
    if(data)
        free(data);
    popback(list);
}

void clearList(List * list) {
    while(list->size > 0) {
        popfront(list);
    }
}

void clearListDelData(List * list) {
    while(list->size > 0)
        popbackDelData(list);
}

int inList(List *list, void * data, int (*datacmp)(void * p1, void * p2)) {
    if(list->size == 0)
        return 0;
    ListNode * cur = list->head;
    while(cur) {
        if(datacmp(cur->data, data) == 0)
            return 1;
        cur = cur->next;
    }

    return 0;
}

ListNode * findLn(List * list, void * data, int (*datacmp)(void * p1, void * p2)) {
    if(list->size == 0)
        return NULL;
    ListNode * cur = list->head;
    while(cur) {
        if(datacmp(cur->data, data) == 0)
            return cur;
        cur = cur->next;
    }

    return NULL;
}

void popLn(List * list, ListNode * ln) {
    if(list->head == ln) {
        popfront(list);
        return;
    }
    if(list->tail == ln) {
        popback(list);
        return;
    }
    ln->prev->next = ln->next;
    ln->next->prev = ln->prev;
    list->size--;

    freeLn(ln);
}

void concatListAndClear2nd(List * dst, List * src) {
    if(src->size == 0)
        return;
    if(dst->size == 0) {
        dst->head = src->head;
        dst->tail = src->tail;
        dst->size = src->size;
    } else {
        dst->tail->next = src->head;
        src->head->prev = dst->tail;
        dst->tail = src->tail;
        dst->size += src->size;
    }
    src->head = NULL;
    src->tail = NULL;
    src->size = 0;
}