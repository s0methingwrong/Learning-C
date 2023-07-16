#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void initList(List * list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void push(List * list, InfoType info) {
    ListNode * node = malloc(sizeof(ListNode));
    if(list->head)
        list->head->prev = node;
    else
        list->tail = node;
    node->info = info;
    node->next = list->head;
    node->prev = NULL;
    list->head = node;
    list->size++;
}

void pop(List * list) {
    if(list->size == 0)
        return;
    ListNode * tmp = list->head;
    list->head = list->head->next;
    if(list->head)
        list->head->prev = NULL;
    else
        list->tail = NULL;
    list->size--;
    free(tmp);
}

InfoType top(List * list) {
    if(list->size == 0) {
        printf("Error: Attempt to read the top of the empty list\n");
        exit(-1);
    }
    return list->head->info;
}

ListNode * getListNodeBySeqNum(List * list, int sn) {
    if(sn <= 0 || sn > list->size || list->size == 0)
        return NULL;
    ListNode * node = list->tail;
    while(--sn)
        node = node->prev;
    return node;
}

void freeList(List * list) {
    while(list->head)
        pop(list);
    list->head = NULL;
}

void popback(List * list) {
    if(list->size == 0)
        return;
    ListNode * tmp = list->tail;
    list->tail = list->tail->prev;
    if(list->tail)
        list->tail->next = NULL;
    else
        list->head = NULL;
    list->size--;
    free(tmp);
}
