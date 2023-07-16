#include "table.h"

void addToTable(Table * table, KeyType key, InfoType info) {
    unsigned int hash = uhash(key, get_msize(table->finfo->fname, table->finfo->msize_pos));

    Item item;
    item.info = info;
    item.key = key;
    item.next = -1;
    item.release = 1;
    
}
