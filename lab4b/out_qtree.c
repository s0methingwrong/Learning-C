#include "out_qtree.h"

void print_list(FILE * fp, List * list) {
    if(!(void *)list)
        return;
    ListNode * cur = list->tail;
    while((void *)cur) {
        if(cur->prev)
            fprintf(fp, "k1=%s|k2=%s|info=%u, ", cur->item->key1, cur->item->key2, cur->item->info);
        else
            fprintf(fp, "k1=%s|k2=%s|info=%u", cur->item->key1, cur->item->key2, cur->item->info);
        cur = cur->prev;
    }
}

void print_qnode(FILE * fp, Qnode * qnode) {
    fprintf(fp, "[");
    print_list(fp, qnode->leaf);
    fprintf(fp, "]\n");
}

void print_qtree(FILE * fp, Qtree * qtree) {
    fprintf(fp, "\n***Qtree***\n");
    traversalWithFile(qtree, fp, print_qnode);
    fprintf(fp, "***end***\n");
}