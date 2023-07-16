#include <stdio.h>
#include <stdlib.h>
#include "table.h"


int main() {
    Table t;
    int cap = 100;

    initTable(&t, cap);
    InfoType * x = malloc(sizeof(InfoType));
    *x = 1000;
    KeyType k = 666;

    addToKeySpace(&t, k, x);

    KeySpace * item = searchByKey(&t, k);
    printf("%d\n", (int)*(item->info));
    freeKS(item);

    item = searchByKeyAndByRel(&t, k, (RelType)1);
    printf("%d\n", (int)*(item->info));
    freeKS(item);

    x = malloc(sizeof(InfoType));
    *x = 1077;

    addToKeySpace(&t, k, x);

    item = searchByKeyAndByRel(&t, k, (RelType)2);
    printf("%d\n", (int)*(item->info));
    freeKS(item);

    return 0;
}
