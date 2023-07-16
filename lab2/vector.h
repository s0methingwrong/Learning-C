#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
    void ** arr;
    int size;
    int start_idx;
    int end_idx;
}vector;

vector * createVector(int size);

void add_to_end(vector * vec, void * data);

void freeFirstHalf(vector * vec);

int delete_from_end(vector * vec);

#endif
