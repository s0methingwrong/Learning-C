#include <stdio.h>
#include <stdlib.h>
#include "table.h"

#define OPEN_F_ERROR "Opening of the file was failed\n"
#define FSEEK_ERROR "Setting the cursor was failed\n"

unsigned int uhash(KeyType key, int msize) {
    static unsigned int a = 101
    static unsigned int b = 43;
    static unsigned int p = 97;

    return (unsigned int)( ((a*(unsigned int)key + b)*p) % (unsigned int) msize )
}


void writeInitial(char * fname, int msize) {
    FILE * fp = fopen(fname, "wb+");
    int csize = 0;
    int pos = -1;
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, 0, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fwrite(&msize, sizeof(int), 1, fp);
    fwrite(&csize, sizeof(int), 1, fp);
    fwrite(&pos, sizeof(long), msize, fp);
    fclose(fp);
}

int get_msize(char * fname, long msize_pos) {
    FILE * fp = fopen(fname, "wb+");
    int msize;
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, msize_pos, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fread(&msize, sizeof(int), 1, fp);
    fclose(fp);

    return msize;
}

int get_csize(char * fname, long csize_pos) {
    FILE * fp = fopen(fname, "wb+");
    int csize;
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, csize_pos, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fread(&csize, sizeof(int), 1, fp);
    fclose(fp);

    return csize;
}

void update_csize(char * fname, long csize_pos, int new_csize) {
    FILE * fp = fopen(fname, "wb+");
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, csize_pos, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fwrite(&new_csize, sizeof(int), 1, fp);
    fclose(fp);
}

long itemPos(char * fname, KeyType key, long ks_pos) {
    unsigned int hash = uhash(key, get_msize(fname));

    FILE * fp = fopen(fname, "wb+");
    long pos;
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, ks_pos + hash * sizeof(long), SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fread(&pos, sizeof(int), 1, fp);
    fclose(fp);

    return pos;
}

void writeItem(char * fname, long pos, Item * item) {
    FILE * fp = fopen(fname, "wb+");
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, pos, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fwrite(item, sizeof(Item), 1, fp);
    fclose(fp);
}

Item readItem(char * fname, long pos) {
    Item item;
    FILE * fp = fopen(fname, "wb+");
    if(!fp) {
        printf(OPEN_F_ERROR);
        exit(-1);
    }
    if(fseek(fp, pos, SEEK_SET)) {
        printf(FSEEK_ERROR);
        exit(-1);
    }
    fread(&item, sizeof(Item), 1, fp);
    fclose(fp);

    return Item;
}
