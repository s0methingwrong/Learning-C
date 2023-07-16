#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "qtree.h"

Qnode * createQnode() {
    Qnode * qnode = malloc(sizeof(Qnode));
    qnode->nw = NULL;
    qnode->ne = NULL;
    qnode->sw = NULL;
    qnode->se = NULL;
    qnode->we_border = NULL;
    qnode->ns_border = NULL;
    qnode->leaf = NULL;
    return qnode;
}

void freeQnodeWithData(Qnode * qnode) {
    if(!qnode)
        return;
    if(qnode->nw)
        freeQnodeWithData(qnode->nw);
    if(qnode->ne)
        freeQnodeWithData(qnode->ne);
    if(qnode->sw)
        freeQnodeWithData(qnode->sw);
    if(qnode->se)
        freeQnodeWithData(qnode->se);
    if(qnode->we_border)
        free((void *)(qnode->we_border));
    if(qnode->ns_border)
        free((void *)(qnode->ns_border));
    if(qnode->leaf)
        freeListWithItems(qnode->leaf);
    free(qnode);
}

void splitQnode(Qnode * qnode) {
    if(!qnode)
        return;
    if(!qnode->leaf)
        return;
    
    initInnerQnodes(qnode);
    qnode->we_border = getMedianListByKt1(qnode->leaf);
    //printf("kt1med = %s\n", qnode->we_border);
    List * west = createList();
    List * east = createList();
    splitIn2ListsByKt1(qnode->leaf, west, east, qnode->we_border);

    /*
    ListNode * ln = west->head;
    printf("\n***west***\n");
    while(ln) {
        printf("k1=%s|k2=%s|info=%u, ", ln->item->key1, ln->item->key2, ln->item->info);
        ln = ln->next;
    }
    printf("***\n");

    ln = east->head;
    printf("\n***east***\n");
    while(ln) {
        printf("k1=%s|k2=%s|info=%u, ", ln->item->key1, ln->item->key2, ln->item->info);
        ln = ln->next;
    }
    printf("***\n");
    */

    qnode->ns_border = getOverageMedianByKt2(west, east);
    //printf("kt2med = %s\n", qnode->ns_border);
    splitIn2ListsByKt2(west, qnode->nw->leaf, qnode->sw->leaf, qnode->ns_border);
    splitIn2ListsByKt2(east, qnode->ne->leaf, qnode->se->leaf, qnode->ns_border);
    freeList(west);
    freeList(east);
    freeList(qnode->leaf);
    qnode->leaf = NULL;
}

void initInnerQnodes(Qnode * qnode) {
    if(!qnode)
        return;
    if(!qnode->leaf)
        return;
    
    qnode->nw = createQnode();
    qnode->ne = createQnode();
    qnode->sw = createQnode();
    qnode->se = createQnode();

    qnode->nw->leaf = createList();
    qnode->ne->leaf = createList();
    qnode->sw->leaf = createList();
    qnode->se->leaf = createList();
}

int isLeaf(Qnode * qnode) {
    if(qnode->leaf)
        return 1;
    return 0;
}

Qtree * createQtree(unsigned int m_leaf_size) {
    Qtree * qtree = malloc(sizeof(Qtree));
    qtree->root = NULL;
    qtree->size = 0;
    qtree->m_leaf_size = m_leaf_size;

    return qtree;
}

void freeQtree(Qtree * qtree) {
    if(!qtree)
        return;
    if(!qtree->root) {
        free(qtree);
        return;
    }
    freeQnodeWithData(qtree->root);
    free(qtree);
}

int addToQnode(Qnode * qnode, Item * item, unsigned int m_leaf_size) {
    if(isLeaf(qnode)) {
        push(qnode->leaf, item);
        if(qnode->leaf->size > m_leaf_size) {
            splitQnode(qnode);
            return 4;
        }
        return 0;
    }
    if((kt1cmp(item->key1, qnode->we_border) < 0) &&
        (kt2cmp(item->key2, qnode->ns_border) < 0))
        return addToQnode(qnode->nw, item, m_leaf_size);
    else if((kt1cmp(item->key1, qnode->we_border) < 0) &&
        (kt2cmp(item->key2, qnode->ns_border) >= 0))
        return addToQnode(qnode->sw, item, m_leaf_size);
    else if((kt1cmp(item->key1, qnode->we_border) >= 0) &&
        (kt2cmp(item->key2, qnode->ns_border) < 0))
        return addToQnode(qnode->ne, item, m_leaf_size);
    else
        return addToQnode(qnode->se, item, m_leaf_size);
}

void addToQtree(Qtree * qtree, KeyType1 k1, KeyType2 k2, InfoType info) {
    if(!qtree->root) {
        qtree->root = createQnode();
        qtree->root->leaf = createList();
        qtree->size++;
    }

    Item * item = createItem(k1, k2, info);
    qtree->size += addToQnode(qtree->root, item, qtree->m_leaf_size);

}

Qnode * getLeafAndSetPrev(Qtree * qtree, Item * item, Qnode ** prev) {
    if(!qtree)
        return NULL;
    if(!qtree->root)
        return NULL;
    Qnode * cur = qtree->root;
    while(!isLeaf(cur)) {
        *prev = cur;
        if((kt1cmp(item->key1, cur->we_border) < 0) &&
            (kt2cmp(item->key2, cur->ns_border) < 0)) {
            cur = cur->nw;
        }
        else if((kt1cmp(item->key1, cur->we_border) < 0) &&
            (kt2cmp(item->key2, cur->ns_border) >= 0)) {
            cur = cur->sw;
        }
        else if((kt1cmp(item->key1, cur->we_border) >= 0) &&
            (kt2cmp(item->key2, cur->ns_border) < 0)) {
            cur = cur->ne;
        }
        else {
            cur = cur->se;
        }
    }
    return cur;
}

Qnode * getParentQnode(Qtree * qtree, Item * item) {
    Qnode * prev = NULL;
    Qnode * leaf = getLeafAndSetPrev(qtree, item, &prev);
    if(!leaf)
        return NULL;
    ListNode * fln = findFirstLn(leaf->leaf, item->key1, item->key2);
    if(!fln)
        return NULL;
    
    return prev;
}

Qnode * getQnode(Qtree * qtree, Item * item) {
    Qnode * prev = NULL;
    Qnode * leaf = getLeafAndSetPrev(qtree, item, &prev);
    if(!leaf)
        return NULL;
    ListNode * fln = findFirstLn(leaf->leaf, item->key1, item->key2);
    if(!fln)
        return NULL;
    
    return leaf;
}

void delItemWithSeqNum(Qtree * qtree, KeyType1 k1, KeyType2 k2, int sn) {
    Item * item = createItem(k1, k2, DEFAULT_INFO);
    Qnode * parent = getParentQnode(qtree, item);
    Qnode * qnode = getQnode(qtree, item);
    freeItem(item);

    if(!qnode)
        return;
    delLnWithSeqNumDelItem(qnode->leaf, k1, k2, sn);
    
    if(!parent)
        return;
    while(isEmptyLeafsChildren(parent)) {
        delChildren(parent);
        item = createItem(k1, k2, DEFAULT_INFO);
        parent = getParentQnode(qtree, item);
        freeItem(item);
        if(!parent)
            return;
    }

}

int isEmptyLeafsChildren(Qnode * qnode) {
    if(qnode->nw->leaf->size == 0 &&
        qnode->ne->leaf->size == 0 &&
        qnode->sw->leaf->size == 0 &&
        qnode->se->leaf->size == 0)
        return 1;
    
    return 0;
}

void delChildren(Qnode * qnode) {
    if(!qnode)
        return;
    if(isLeaf(qnode))
        return;
    freeQnodeWithData(qnode->nw);
    freeQnodeWithData(qnode->ne);
    freeQnodeWithData(qnode->sw);
    freeQnodeWithData(qnode->se);
    qnode->nw = NULL;
    qnode->ne = NULL;
    qnode->sw = NULL;
    qnode->se = NULL;
    free((void *)(qnode->ns_border));
    free((void *)(qnode->we_border));
    qnode->ns_border = NULL;
    qnode->we_border = NULL;
    qnode->leaf = createList();
}

List * search(Qtree * qtree, KeyType1 k1, KeyType2 k2) {
    Item * item = createItem(k1, k2, DEFAULT_INFO);
    Qnode * qnode = getQnode(qtree, item);
    freeItem(item);

    if(!qnode)
        return NULL;
    
    return findAll(qnode->leaf, k1, k2);
}

void traversalQnodeWithFile(Qnode * qnode, FILE * fp, void (*f)(FILE * fp, Qnode * qnode)) {
    if(!qnode)
        return;
    if(isLeaf(qnode)) {
        f(fp, qnode);
        return;
    }

    traversalQnodeWithFile(qnode->se, fp, f);
    traversalQnodeWithFile(qnode->ne, fp, f);
    traversalQnodeWithFile(qnode->sw, fp, f);
    traversalQnodeWithFile(qnode->nw, fp, f);
}

void traversalWithFile(Qtree * qtree, FILE * fp, void (*f)(FILE * fp, Qnode * qnode)) {
    traversalQnodeWithFile(qtree->root, fp, f);
}