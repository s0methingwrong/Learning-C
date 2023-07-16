#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Matrix {
    int ** data;
    int * sizes;
    int size;
}Matrix;

typedef struct Vector {
    int * data;
    int size;
}Vector;

void createMatrix(Matrix * matrix);
int imax_in_row(Matrix * matrix, int row);
int min_sz_row_col(Matrix * matrix, int row, int col);
int col_sz(Matrix * matrix, int col);
void createVector(Vector * vector, Matrix * matrix);
void outputMatrix(Matrix * matrix);
void outputVector(Vector * vector);
int digit_scanf(char* fmt, int * ptr);
void safe_digit_scanf(char * fmt, int * ptr);
void freeMatrix(Matrix * matrix);
void freeVector(Vector * vector);


int main(){
    Matrix matrix;
    Vector vector;
    createMatrix(&matrix);
    outputMatrix(&matrix);
    printf("***createvector***\n");
    createVector(&vector, &matrix);
    outputVector(&vector);

    freeMatrix(&matrix);
    freeVector(&vector);
    return 0;
}

void createMatrix(Matrix * matrix){
    printf("***input matrix***\nInput a number of rows:\n");
    safe_digit_scanf("%d", &matrix->size);
    while(matrix->size <= 0) {
        printf("***wrong input:\n\tnumber of rows must be positive\n***\n");
        safe_digit_scanf("%d", &matrix->size);
    }
    matrix->sizes = (int*)malloc(sizeof(int)*matrix->size);
    matrix->data = (int**)malloc(sizeof(int*)*matrix->size);
    for (int i=0; i<matrix->size; i++){
        printf("Input a size of the row #%d:\n", i);
        safe_digit_scanf("%d", matrix->sizes + i);
        if(i>0) {
            while(matrix->sizes[i] > matrix->sizes[i-1] || matrix->sizes[i] <= 0) {
                printf("***wrong input:\n\tnumber of elements in the row must be\tpositive and less then in the previous\n***\n");
                printf("Input a size of the row #%d:\n", i);
                safe_digit_scanf("%d", matrix->sizes + i);
            }
        }
        matrix->data[i] = (int*)malloc(sizeof(int)*matrix->sizes[i]);
        for (int j=0; j<matrix->sizes[i]; j++){
            printf("Input an element #%d of the row #%d:\n", j, i);
            safe_digit_scanf("%d", &matrix->data[i][j]);
        }
    }
    printf("***input matrix end***\n");
}

int imax_in_row(Matrix * matrix, int row){
    int max = matrix->data[row][0];
    int ind = 0;

    for (int i=0;i<matrix->sizes[row];++i){
            if(matrix->data[row][i] > max){
                max = matrix->data[row][i];
                ind++;
            }
    }
    printf("imax_in_row = %d\n", ind);
    return ind;
}

int min_sz_row_col(Matrix * matrix, int row, int col){
    int col_size = col_sz(matrix, col);
    if (col_size < matrix->sizes[row])
        return col_size;
    else
        return matrix->sizes[row];
}

int col_sz(Matrix * matrix, int col) {
    int sz = 0;
    for(int i=0; i<matrix->size; i++) {
        if(matrix->sizes[i] > col)
            sz++;
    }

    return sz;
}

void createVector(Vector * vector, Matrix * matrix) {
    vector->size = matrix->size;
    vector->data = (int*)malloc(sizeof(int)*vector->size);
    int k;
    int l;
    for(int i=0; i<vector->size; i++) {
        vector->data[i] = 0;
        k = imax_in_row(matrix, i);
        l = min_sz_row_col(matrix, i, k);
        for(int j=0; j<l; j++)
            vector->data[i] += matrix->data[i][j] * matrix->data[j][k]; 
    }
}

void outputMatrix(Matrix * matrix) {
    printf("***output matrix***\n");
    for(int i=0; i<matrix->size; i++) {
        if(i!=0)
            printf("\n");
        for(int j=0; j<matrix->sizes[i]; j++)
            printf("%d\t", matrix->data[i][j]);
    }
    printf("\n");
    printf("***output matrix end***\n");
}

void outputVector(Vector * vector) {
    printf("***output vector***\n");
    for(int j=0; j<vector->size; j++)
        printf("%d\t", vector->data[j]);
    printf("\n");
    printf("***output vector end***\n");
}

int digit_scanf(char* fmt, int * ptr) {
    char s[20];
    scanf("%s", s);
    printf("s = %s,\t%d\n", s, (int)strlen(s));
    int i = 0;
    if(strlen(s) > 0) {
        if(s[0] == '-') {
            i = 1;
            if(strlen(s) == 1)
                return 0;
        }
    }
    else {
        return 0;
    }
    for(int j=i; j<strlen(s); j++) {
        if(!isdigit(s[j])) {
            return 0;
        }
    }
    *ptr = atoi(s);
    return 1;
}

void safe_digit_scanf(char * fmt, int * ptr) {
    int correct = digit_scanf(fmt, ptr);
    while(!correct) {
        printf("***wrong input:\n\tthe input must be integer\n**\n");
        correct = digit_scanf(fmt, ptr);
    }
}

void freeMatrix(Matrix * matrix) {
    if(matrix->data) {
        for(int i=0; i<matrix->size; i++) {
            if(matrix->data[i]) {
                free(matrix->data[i]);
            }
        }
        free(matrix->data);
    }
    if(matrix->sizes)
        free(matrix->sizes);
}

void freeVector(Vector * vector) {
    if(vector->data)
        free(vector->data);
}


/*
Input a number of rows:
3
Input a size of the row #1:
5
Input an element #1 of the row #1:
56
Input an element #2 of the row #1:
*/
