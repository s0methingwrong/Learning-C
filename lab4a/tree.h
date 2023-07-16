#ifndef TREE_H 
#define TREE_H

#include "list.h"

typedef unsigned int KeyType;

typedef struct Node {
    KeyType key;
    List list_info;
    struct Node * left;
    struct Node * right;
}Node;

typedef struct Tree {
    Node * root;
    unsigned int size;
}Tree;

//interface

void initTree(Tree * tree);

void add(Tree * tree, KeyType key, InfoType info);

ListNode * getListNodeByKeyAndSeqNum(Tree * tree, KeyType key, int sn); // sn - sequence number; error if there is no such key

void del(Tree * tree, KeyType key);

void traversal(Tree * tree, void (*f)(Node * node));

void traversalWithFile(Tree * tree, FILE * fp, void (*f)(FILE * fp, Node * node));

void traversalUntilKey(Tree * tree, void (*f)(Node * node), KeyType key);

ListNode * getListNodeWithMostDiffKeyByKeyAndSeqNum(Tree * tree, KeyType key, int sn);

// utils

void traversalNode(Node * node, void (*f)(Node * node));

void traversalNodeWithFile(Node * node, FILE * fp, void (*f)(FILE * fp, Node * node));

void traversalNodeUntilKey(Node * node, void (*f)(Node * node), KeyType key);

Node * createEmptyNode(KeyType key);

int addToNode(Node * node, KeyType key, InfoType info); // return 1 if Node was created else 0

Node * getParentNode(Tree * tree, KeyType key); // return NULL if key in the root or there is no node with such key

Node * getNode(Tree * tree, KeyType key); // return NULL if there is no such key

void deleteNode(Tree * tree, KeyType key);

Node * getNodeWithMinKey(Tree * tree);

Node * getNodeWithMaxKey(Tree * tree);

Node * findReplacerAandSetChildren(Node * todel);

#endif