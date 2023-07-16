#include <stdlib.h>
#include "graph.h"

void initGraph(Graph * g, unsigned int vNum) {
    g->vNum = vNum;
    g->mtrx = malloc(sizeof(int)*vNum*vNum);
    initTable(&(g->table), vNum);
}

void readGraphMatrix(FILE * fp, Graph * g) {
    int i, j;
    for(i = 0; i < g->vNum; i++)
        for(j = 0; j < g->vNum; j++)
            fscanf(fp, "%d", &(g->mtrx[i * g->vNum + j]));
}

void readGraphTable(FILE * fp, Graph * g) {
    int i;
    char buf[200];
    for(i = 0; i < g->vNum; i++) {
        fscanf(fp, "%s", buf);
        addToTable(&(g->table), buf, i);
    }
}

void readVertexNumber(FILE * fp, Graph * g) {
    unsigned int vNum;
    fscanf(fp, "%u", &vNum);
    initGraph(g, vNum);
}

void readGraph(FILE * fp, Graph * g) {
    readVertexNumber(fp, g);
    readGraphTable(fp, g);
    readGraphMatrix(fp, g);
}

void writeGraphMatrix(FILE * fp, Graph * g) {
    int i, j;
    for(i = 0; i < g->vNum; i++)
        for(j = 0; j < g->vNum; j++) {
            fprintf(fp, "%d", g->mtrx[i * g->vNum + j]);
            if(j == g->vNum - 1)
                fprintf(fp, "\n");
            else
                fprintf(fp, " ");
        }
}

void writeGraphTable(FILE * fp, Graph * g) {
    int i;
    for(i = 0; i < g->vNum; i++) {
        fprintf(fp, "%s\n", getTableKey(&(g->table), i));
    }
}

void writeVertexNumber(FILE * fp, Graph * g) {
    fprintf(fp, "%u\n", g->vNum);
}

void writeGraph(FILE * fp, Graph * g) {
    writeVertexNumber(fp, g);
    writeGraphTable(fp, g);
    writeGraphMatrix(fp, g);
}

void clearGraph(Graph * g) {
    if(g->mtrx)
        free(g->mtrx);
    clearTable(&(g->table));
}

List * createAdjList(Graph * g, int v) {
    List *alist = createList();
    int j, tmp;
    for(j = 0; j < g->vNum; j++) {
        tmp = g->mtrx[v * g->vNum + j];
        if(tmp)
            pushback(alist, createInt(j));
    }

    return alist;
}

List * BFS(Graph * g, int s, int target) {
    if(s == target)
        return createList();

    int * visited = malloc(sizeof(int)*g->vNum);
    int i, val;
    for(i = 0; i < g->vNum; i++)
        visited[i] = 0;
    visited[s] = 1;

    int * folks = malloc(sizeof(int)*g->vNum);
    for(i = 0; i < g->vNum; i++)
        folks[i] = -1;

    List * curLayer = createAdjList(g, s);
    if(curLayer->size == 0)
        return NULL;
    ListNode * ln = curLayer->head;
    while(ln) {
        val = *(int *)(ln->data);
        folks[val] = s;
        ln = ln->next;
    }

    List * tmp;
    while(curLayer->size > 0) {
        if(inList(curLayer, (void *)&target, intcmp)) {
            List * route = createList();
            val = folks[target];
            pushfront(route, createInt(val));
            while(val != s) {
                val = folks[val];
                pushfront(route, createInt(val));
            }
            free(visited);
            free(folks);
            freeListDelData(curLayer);
            return route;
        }
        tmp = curLayer;
        curLayer = nextLayer(g, curLayer, visited, folks);
        freeListDelData(tmp);
    }
    freeListDelData(curLayer);
    free(visited);
    free(folks);

    return NULL;
}

List * nextLayer(Graph * g, List * cur, int * visited, int * folks) {
    List * children = createList();
    ListNode * ln = cur->head;
    int j, tmp, val;
    while(ln) {
        val = *(int *)(ln->data);
        for(j = 0; j < g->vNum; j++) {
            tmp = g->mtrx[val * g->vNum + j];
            if(tmp && !visited[j]) {
                pushback(children, createInt(j));
                folks[j] = val;
            }
        }
        ln = ln->next;
    }

    return children;
}

int edgeNum(Graph * g) {
    int i, j;
    int cnt = 0;
    for(i = 0; i < g->vNum - 1; i++)
        for(j = i + 1; j < g->vNum; j++)
            if(g->mtrx[i * g->vNum + j] == 1)
                cnt++;
    return cnt;
}

Edge * edgeArr(Graph * g) {
    Edge * edges = malloc(sizeof(Edge)*edgeNum(g));
    int i, j;
    int cnt = 0;
    for(i = 0; i < g->vNum - 1; i++)
        for(j = i + 1; j < g->vNum; j++)
            if(g->mtrx[i * g->vNum + j] == 1) {
                edges[cnt].a = i;
                edges[cnt].b = j;
                cnt++;
            }
    return edges;
}

List * pathBellmanFord(Graph * g, int s, int target) {
    static int inf = 1000000000;
    int n = g->vNum;
    int m = edgeNum(g);
    Edge * e = edgeArr(g);
    int * d = malloc(sizeof(int)*n);
    int i, j;
    for(i = 0; i < n; i++)
        d[i] = inf;
    d[s] = 0;
    int * p = malloc(sizeof(int)*n);
    for(i = 0; i < n; i++)
        p[i] = -1;
    for (;;) {
		int any = 0;
		for (j = 0; j < m; ++j)
			if (d[e[j].a] < inf)
				if (d[e[j].b] > d[e[j].a] + 1) {
					d[e[j].b] = d[e[j].a] + 1;
					p[e[j].b] = e[j].a;
					any = 1;
				}
		if (!any)  break;
	}

    if(d[target] == inf) {
        free(e);
        free(d);
        free(p);
        return NULL;
    } else {
        List * route = createList();
        int val = p[target];
        pushfront(route, createInt(val));
        while(val != s) {
            val = p[val];
            pushfront(route, createInt(val));
        }
        free(e);
        free(d);
        free(p);
        return route;
    }
    return NULL;
}