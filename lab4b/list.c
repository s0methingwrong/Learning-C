#include <stdlib.h>
#include <string.h>
#include "list.h"

int lncmp(ListNode * ln1, ListNode * ln2) {
    return itemcmp(ln1->item, ln2->item);
}

List * createList() {
    List * list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void freeln(ListNode * ln) {
    if(!ln)
        return;
    freeItem(ln->item);
    free(ln);
}

void push(List * list, Item * item) {
    ListNode * ln = malloc(sizeof(ListNode));
    ln->item = item;
    ln->next = NULL;
    ln->prev = NULL;

    if(list->size == 0) {
        pushLnToHead(list, ln);
        return;
    }

    if(lncmp(ln, list->head) < 0) {
        pushLnToHead(list, ln);
        return;
    }

    if(lncmp(ln, list->tail) >= 0) {
        pushLnToTail(list, ln);
        return;
    }

    ListNode * cur = list->head;
    while(lncmp(ln, cur) >= 0)
        cur = cur->next;
    pushLnBeforeCur(list, ln, cur);
}

void pushLnToHead(List * list, ListNode * ln) {
    if(list->size == 0) {
        list->head = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    if(lncmp(ln, list->head) <= 0) {
        ln->next = list->head;
        list->head->prev = ln;
        list->head = ln;
        list->size++;
        return;
    }

    return;
}

void pushLnToTail(List * list, ListNode * ln) {
    if(list->size == 0) {
        list->head = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    if(lncmp(ln, list->tail) >= 0) {
        ln->prev = list->tail;
        list->tail->next = ln;
        list->tail = ln;
        list->size++;
        return;
    }

    return;
}

void pushLnBeforeCur(List * list, ListNode * ln, ListNode * cur) {
    ln->prev = cur->prev;
    ln->next = cur;
    cur->prev->next = ln;
    cur->prev = ln;
    list->size++;
}

void pushback(List * list, Item * item) {
    ListNode * ln = malloc(sizeof(ListNode));
    ln->item = item;
    ln->next = NULL;
    ln->prev = NULL;

    pushLnToTail(list, ln);
}

Item * top(List * list) {
    if(!list)
        return NULL;
    if(!list->head)
        return NULL;
    return list->head->item;
}

void popfront(List * list) {
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

    ListNode * todel = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->size--;
    free(todel);
}

void popfrontWithFreeItem(List * list) {
    Item * it = top(list);
    popfront(list);
    if(it)
        freeItem(it);
}

ListNode * findFirstLn(List * list, KeyType1 k1, KeyType2 k2) {
    if(!list)
        return NULL;

    Item * tosearch = createItem(k1, k2, DEFAULT_INFO);
    
    ListNode * cur = list->head;
    while(cur) {
        if(itemcmp(tosearch, cur->item) == 0) {
            freeItem(tosearch);
            return cur;
        }
        cur = cur->next;
    }
    freeItem(tosearch);

    return NULL;
}

List * findAll(List * list, KeyType1 k1, KeyType2 k2) {
    if(!list)
        return NULL;
    
    ListNode * firstln = findFirstLn(list, k1, k2);
    if(!firstln)
        return NULL;
    
    List * li = createList();
    Item * tosearch = createItem(k1, k2, DEFAULT_INFO);
    while(itemcmp(tosearch, firstln->item) == 0) {
        push(li, firstln->item);
        firstln = firstln->next;
        if(!firstln)
            break;
    }

    freeItem(tosearch);

    return li;
}

void freeList(List * list) {
    if(!list)
        return;
    while(list->size > 0)
        popfront(list);
    free(list);
}

void freeListWithItems(List * list) {
    if(!list)
        return;
    while(list->size > 0)
        popfrontWithFreeItem(list);
    free(list);
}

void delLnWithSeqNumDelItem(List * list, KeyType1 k1, KeyType2 k2, int sn) {
    if(!list)
        return;
    
    if(sn < 1)
        return;
    
    ListNode * firstln = findFirstLn(list, k1, k2);
    if(!firstln)
        return;
    
    Item * tosearch = createItem(k1, k2, DEFAULT_INFO);
    while(--sn) {
        firstln = firstln->next;
        if(!firstln) {
            freeItem(tosearch);
            return;
        }
        if(itemcmp(tosearch, firstln->item) != 0) {
            freeItem(tosearch);
            return;
        }
    }
    delLn(list, firstln);
}

void delLn(List * list, ListNode * ln) {
    if(!list || !ln)
        return;
    
    if(ln == list->head) {
        popfrontWithFreeItem(list);
        return;
    }

    if(ln == list->tail) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->size--;
        freeln(ln);
        return;
    }

    ln->prev->next = ln->next;
    ln->next->prev = ln->prev;
    list->size--;
    freeln(ln);
}

void splitIn2ListsByKt1(List * src, List * dst1, List * dst2, KeyType1 k1) {
    if(!src || !dst1 || !dst2)
        return;
    
    ListNode * cur = src->head;
    while(cur) {
        if(kt1cmp(cur->item->key1, k1) < 0)
            pushback(dst1, cur->item);
        else
            pushback(dst2, cur->item);
        cur = cur->next;
    }
}

void splitIn2ListsByKt2(List * src, List * dst1, List * dst2, KeyType2 k2) {
    if(!src || !dst1 || !dst2)
        return;
    
    ListNode * cur = src->head;
    while(cur) {
        if(kt2cmp(cur->item->key2, k2) < 0)
            pushback(dst1, cur->item);
        else
            pushback(dst2, cur->item);
        cur = cur->next;
    }
}

KeyType1 getMedianListByKt1(List * list) {
    if(!list)
        return NULL;
    if(list->size == 0)
        return NULL;
    ListNode * cur = list->head;
    unsigned int c = list->size/2;
    while(c--)
        cur = cur->next;
    KeyType1 k1 = malloc(sizeof(KeyType1)*(strlen((char *)(cur->item->key1))+1));
    strcpy((char *)k1, (const char *)(cur->item->key1));
    return k1;
}

ListKt2 * getListKt2(List * list) {
    if(!list)
        return NULL;
    if(list->size == 0)
        return NULL;
    ListKt2 * lkt2 = createListKt2();
    ListNode * cur = list->head;
    while(cur) {
        pushKt2(lkt2, cur->item->key2);
        cur = cur->next;
    }

    return lkt2;
}

KeyType2 getOverageMedianByKt2(List * src1, List * src2) {
    ListKt2 * lkt2_1 = getListKt2(src1);
    ListKt2 * lkt2_2 = getListKt2(src2);

    if(!lkt2_1 && !lkt2_2)
        return NULL;
    
    KeyType2 k2_1 = (KeyType2)"";
    KeyType2 k2_2 = (KeyType2)"";
    KeyType2 k2;
    if(lkt2_1)
        k2_1 = getMedianListKt2(lkt2_1);
    if(lkt2_2)
        k2_2 = getMedianListKt2(lkt2_2);
    if(kt2cmp(k2_1, k2_2) > 0) {
        k2 = malloc(sizeof(KeyType2)*(strlen((char *)k2_1)+1));
        strcpy((char *)k2, (const char *)(k2_1));
        return k2;
    }
    k2 = malloc(sizeof(KeyType2)*(strlen((char *)k2_2)+1));
    strcpy((char *)k2, (const char *)(k2_2));
    return k2;   
}