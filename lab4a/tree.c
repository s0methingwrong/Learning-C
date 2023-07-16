#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tree.h"

void initTree(Tree * tree) {
    tree->root = NULL;
    tree->size = 0;
}

void add(Tree * tree, KeyType key, InfoType info) {
    if(tree->root) {
        tree->size += addToNode(tree->root, key, info);
        return;
    }
    tree->root = createEmptyNode(key);
    push(&(tree->root->list_info), info);
    tree->size++;
}

int addToNode(Node * node, KeyType key, InfoType info) {
    if(node->key > key) {
        if(node->left)
            return addToNode(node->left, key, info);
        else {
            node->left = createEmptyNode(key);
            push(&(node->left->list_info), info);
            return 1;
        }
    } else if (node->key < key) {
        if(node->right)
            return addToNode(node->right, key, info);
        else {
            node->right = createEmptyNode(key);
            push(&(node->right->list_info), info);
            return 1;
        }
    } else
        push(&(node->list_info), info);
    return 0;
}

Node * createEmptyNode(KeyType key) {
    Node * node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    initList(&(node->list_info));
    return node;
}

Node * getParentNode(Tree * tree, KeyType key) {
    if(!tree->root)
        return NULL;
    Node * parent = NULL;
    Node * tmp = tree->root;
    while(tmp->key != key) {
        parent = tmp;
        if(tmp->key > key) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
        if(!tmp)
            return NULL;
    }

    return parent;
}

Node * getNode(Tree * tree, KeyType key) {
    if(!tree->root)
        return NULL;
    if(tree->root->key == key)
        return tree->root;
    
    Node * parent = getParentNode(tree, key);
    if(!parent)
        return NULL;
    if(parent->left)
        if(parent->left->key == key)
            return parent->left;
    if(parent->right)
        if(parent->right->key == key)
            return parent->right;
    return NULL;
}

ListNode * getListNodeByKeyAndSeqNum(Tree * tree, KeyType key, int sn) {
    Node * node = getNode(tree, key);
    if(!node) {
        return NULL;
    }
    return getListNodeBySeqNum(&(node->list_info), sn);
}

void deleteNode(Tree * tree, KeyType key) {
    Node * todel = getNode(tree, key);
    Node * parent = getParentNode(tree, key);

    if(!todel)
        return;
    
    Node * replacer = findReplacerAandSetChildren(todel);

    if(!parent)
        tree->root = replacer;
    else {
        if(todel == parent->left)
            parent->left = replacer;
        else
            parent->right = replacer;
    }

    freeList(&(todel->list_info));
    free(todel);
    tree->size--;
}

Node * findReplacerAandSetChildren(Node * todel) {
    Node * replacer;
    if(!todel->right)
        replacer = todel->left;
    else if(!todel->right->left) {
        replacer = todel->right;
        replacer->left = todel->left;
    } else {
        Node * prev = todel->right;
        replacer = todel->right->left;
        while(replacer->left) {
            prev = replacer;
            replacer = replacer->left;
        }
        prev->left = NULL;
        replacer->left = todel->left;
        replacer->right = todel->right;
    }

    return replacer;
}

void del(Tree * tree, KeyType key) {
    Node * node = getNode(tree, key);
    if(!node)
        return;
    
    if(node->list_info.size == 1) {
        deleteNode(tree, key);
        return;
    }

    popback(&(node->list_info));
}

void traversal(Tree * tree, void (*f)(Node * node)) {
    traversalNode(tree->root, f);
}

void traversalNode(Node * node, void (*f)(Node * node)) {
    if(!node)
        return;
    traversalNode(node->left, f);
    f(node);
    traversalNode(node->right, f);
}

void traversalUntilKey(Tree * tree, void (*f)(Node * node), KeyType key) {
    traversalNodeUntilKey(tree->root, f, key);
}

void traversalNodeUntilKey(Node * node, void (*f)(Node * node), KeyType key) {
    if(!node)
        return;
    traversalNodeUntilKey(node->left, f, key);
    if(node->key <= key)
        f(node);
    else
        return;
    traversalNodeUntilKey(node->right, f, key);
}

void traversalWithFile(Tree * tree, FILE * fp, void (*f)(FILE * fp, Node * node)) {
    traversalNodeWithFile(tree->root, fp, f);
}

void traversalNodeWithFile(Node * node, FILE * fp, void (*f)(FILE * fp, Node * node)) {
    if(!node)
        return;
    traversalNodeWithFile(node->left, fp, f);
    f(fp, node);
    traversalNodeWithFile(node->right, fp, f);
}

Node * getNodeWithMinKey(Tree * tree) {
    Node * node = tree->root;
    if(!node)
        return NULL;
    while(node->left)
        node = node->left;
    
    return node;
}

Node * getNodeWithMaxKey(Tree * tree) {
    Node * node = tree->root;
    if(!node)
        return NULL;
    while(node->right)
        node = node->right;
    
    return node;
}

ListNode * getListNodeWithMostDiffKeyByKeyAndSeqNum(Tree * tree, KeyType key, int sn) {
    Node * node_max_key = getNodeWithMaxKey(tree);
    Node * node_min_key = getNodeWithMinKey(tree);
    if(!node_max_key && !node_min_key)
        return NULL;
    Node * target_node;
    if(abs(node_max_key->key - key) > abs(node_min_key->key - key))
        target_node = node_max_key;
    else
        target_node = node_min_key;

    return getListNodeByKeyAndSeqNum(tree, target_node->key, sn);
}