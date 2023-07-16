#ifndef TABLE_H
#define TABLE_H

typedef struct Table {
    char ** keyArr;
    unsigned int size;
}Table;

void initTable(Table * t, unsigned int size);
void addToTable(Table * t, const char * key, int idx);
void clearTable(Table * t);
char * getTableKey(Table * t, int idx);
int getTabelIdx(Table * t, char * key); //return idx of key and -1 if key is not present in the table

#endif