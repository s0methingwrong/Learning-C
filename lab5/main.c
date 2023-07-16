#include <string.h>
#include "graph.h"
#include "list.h"

int mystrcmp(void * p1, void * p2);
void print_list(List * list);
void print_list_int(List * list);

int main() {
    Graph g;

    FILE * in = fopen("input.txt", "r");
    readGraph(in, &g);
    fclose(in);

    FILE * out = fopen("output.txt", "w");
    writeGraph(out, &g);
    fclose(out);

    List * route = pathBellmanFord(&g, 0, 3);

    print_list_int(route);

    freeListDelData(route);

    clearGraph(&g);

    /*
    List * list = createList();
    pushback(list, "moscow");
    pushback(list, "london");
    pushfront(list, "paris");

    print_list(list);
    printf("%d\n", inList(list, "moscowa", mystrcmp));
    printf("%s\n", (char *)back(list));

    ListNode * ln = findLn(list, "london", mystrcmp);
    printf("%s\n", (char *)(ln->data));

    popLn(list, ln);

    print_list(list);

    freeList(list);
    */

    return 0;
}

int mystrcmp(void * p1, void * p2) {
    return strcmp((const char *)p1, (const char *)p2);
}

void print_list(List * list) {
    ListNode * cur = list->head;
    while(cur) {
        printf("%s\t", (char *)(cur->data));
        cur = cur->next;
    }
    printf("\n");
}

void print_list_int(List * list) {
    ListNode * cur = list->head;
    while(cur) {
        printf("%d ", *(int *)(cur->data));
        cur = cur->next;
    }
    printf("\n");
}