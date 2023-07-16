#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "table.h"
#include "list.h"

typedef struct Graph {
    unsigned int vNum;
    int * mtrx; // adjacent matrix
    Table table;
}Graph;

typedef struct Edge {
    int a;
    int b;
}Edge;

void initGraph(Graph * g, unsigned int vNum);
void readGraphMatrix(FILE * fp, Graph * g);
void readGraphTable(FILE * fp, Graph * g);
void readVertexNumber(FILE * fp, Graph * g);
void readGraph(FILE * fp, Graph * g);
void writeGraphMatrix(FILE * fp, Graph * g);
void writeGraphTable(FILE * fp, Graph * g);
void writeVertexNumber(FILE * fp, Graph * g);
void writeGraph(FILE * fp, Graph * g);
void clearGraph(Graph * g);
List * createAdjList(Graph * g, int v); //v - index of a vertex, return adjacent list
List * BFS(Graph * g, int s, int target);
List * nextLayer(Graph * g, List * cur, int * visited, int * folks);
int edgeNum(Graph * g);
Edge * edgeArr(Graph * g);
List * pathBellmanFord(Graph * g, int s, int target);

//utils

void * createInt(int n);
int intcmp(void * p1, void * p2);

#endif