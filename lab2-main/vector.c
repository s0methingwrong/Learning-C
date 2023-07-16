#include <stdlib.h>
#include "vector.h"

vector * createVector(int size) {
    vector * vec = (vector*)malloc(sizeof(vector));
    vec->arr = (void**)malloc(sizeof(void*)*size);
    vec->size = size;
    vec->start_idx = -1;
    vec->end_idx = -1;
    return vec;
}

void add_to_end(vector * vec, void * data) {
    if(vec->end_idx == vec->size - 1) {
        freeFirstHalf(vec);
    }
    vec->end_idx++;
    vec->arr[vec->end_idx] = data;
    if(vec->start_idx == -1)
        vec->start_idx = 0;
}

void freeFirstHalf(vector * vec) {
    int i;

    //free first half of the array
    for(i = 0; i < vec->size/2; i++)
        if(vec->arr[i] != NULL)
            free(vec->arr[i]);

    //move second half to the start of the array
    for(i = vec->size/2; i < vec->size; i++)
        vec->arr[i - vec->size/2] = vec->arr[i];
    vec->start_idx = 0;
    vec->end_idx = vec->size - vec->size/2 - 1;
}

int delete_from_end(vector * vec) {
    if(vec->start_idx == -1)
        return 0;
    if(vec->arr[vec->end_idx] != NULL)
        free(vec->arr[vec->end_idx]);
    vec->end_idx--;
    if(vec->end_idx == -1)
        vec->start_idx = -1;
    return 1;
}

