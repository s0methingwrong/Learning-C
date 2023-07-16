#ifndef TABLE_H
#define TABLE_H

typedef unsigned int KeyType;

typedef int InfoType;

typedef int RelType;

typedef struct FileInfo {
    char * fname;
    long msize_pos;
    long csize_pos;
    long ks_pos;
    long items_pos;
    long last_item_pos;
}FileInfo;

typedef struct Item {
    KeyType key;
    RelType release;
    InfoType info;
    long next; 
}Item;


typedef struct Table {
    int msize;
    int csize;
    FileInfo * finfo;;
}Table;


// interface

void addToTable(Table * table, KeyType key, InfoType info);

// utils

unsigned int uhash(KeyType key, int msize);

void writeInitial(char * fname, int msize);

long itemPos(char * fname, KeyType key, long ks_pos);

int get_msize(char * fname, long msize_pos);

int get_csize(char * fname, long csize_pos);

void update_csize(char * fname, long csize_pos, int new_csize);

void writeItem(char * fname, long pos, Item * item);

Item readItem(char * fname, long pos);

// todo 
// updateItem - utils
// addToTable - finish
// search - interface
// delete - interface


#endif

/*
msize - 4 bytes
csize - 4 bytes

ks - msize*sizeof(KeySpace) bytes

a
b
f
d
e


*/
