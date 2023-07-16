#include <stdio.h>
#include <string.h>
#include "out_tree.h"
#include "tree.h"


int main() {
    char *gv_fname = "1.gv";
    char *out_png_fname = "1.png";
    Tree tree;
    initTree(&tree);
    add(&tree, (KeyType)8, (InfoType)1);
    add(&tree, (KeyType)11, (InfoType)2);
    add(&tree, (KeyType)5, (InfoType)3);
    add(&tree, (KeyType)14, (InfoType)4);
    add(&tree, (KeyType)7, (InfoType)5);
    add(&tree, (KeyType)7, (InfoType)6);
    add(&tree, (KeyType)11, (InfoType)7);

    print_tree(&tree);

    del(&tree, (KeyType)7);

    print_tree(&tree);

    del(&tree, (KeyType)7);

    print_tree(&tree);

    add(&tree, (KeyType)11, (InfoType)8);
    add(&tree, (KeyType)5, (InfoType)9);
    add(&tree, (KeyType)19, (InfoType)10);
    add(&tree, (KeyType)2, (InfoType)11);
    add(&tree, (KeyType)9, (InfoType)12);
    add(&tree, (KeyType)11, (InfoType)13);

    print_tree(&tree);

    printf("info = %u\n", getListNodeByKeyAndSeqNum(&tree, 11, 2)->info);

    fill_gv_file(gv_fname, &tree);

    createPNG(gv_fname, out_png_fname);

    print_tree_until_key(&tree, (KeyType)9);

    printf("info = %u\n", getListNodeWithMostDiffKeyByKeyAndSeqNum(&tree, 7, 1)->info);

    return 0;
}
