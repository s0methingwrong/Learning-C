#include <stdio.h>
#include <string.h>
#include "out_tree.h"

void print_node(Node * node) {
    printf("node.key = %u:\t[", node->key);
    print_list(&(node->list_info));
    printf("]\n");
}

void print_tree(Tree * tree) {
    printf("\n***Tree***\n");
    traversal(tree, print_node);
    printf("***end***\n");
}

void print_tree_until_key(Tree * tree, KeyType key) {
    printf("\n***Tree***\n");
    traversalUntilKey(tree, print_node, key);
    printf("***end***\n");
}

void print_list(List * list) {
    ListNode * cur = list->head;
    while(cur) {
        if(cur->next)
            printf("%u, ", cur->info);
        else
            printf("%u", cur->info);
        cur = cur->next;
    }
}

void writeNode(FILE * fp, Node * node) {
    if(node->left) {
        fprintf(fp, "    %u -> %u\n", node->key, node->left->key);
    }
    if(node->right) {
        fprintf(fp, "    %u -> %u\n", node->key, node->right->key);
    }
}

void fill_gv_file(char * fname, Tree * tree) {
    FILE * fp = fopen(fname, "w");
    if(!fp)
        return;
    fprintf(fp, "digraph G {\n");
    traversalWithFile(tree, fp, writeNode);
    fprintf(fp, "}\n");
    fclose(fp);
}

void createPNG(char * gv_fname, char * out_png_fname) {
    FILE * pPipe;
    pPipe = popen("cmd.exe", "w");
    if(pPipe)
        fprintf(pPipe, "dot -Tpng %s -o %s\n", gv_fname, out_png_fname);
    pclose(pPipe);
}