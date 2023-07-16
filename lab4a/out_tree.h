#ifndef OUT_TREE_H
#define OUT_TREE_H

#include <stdio.h>
#include <string.h>
#include "tree.h"

void print_node(Node * node);

void print_tree(Tree * tree);

void print_tree_until_key(Tree * tree, KeyType key);

void print_list(List * list);

void fill_gv_file(char * fname, Tree * tree);

void writeNode(FILE * fp, Node * node);

void createPNG(char * gv_fname, char * out_png_fname);

#endif