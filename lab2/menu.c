#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void menu() {
    const char * menuInfo = "command\t - description\n0\t - show menu\n1\t - input path to directory\n2\t - move to previous directory\n3\t - show current directory\n4\t - quit\n";

    Stack stack;
    stack.top = NULL;
    stack.size = 0;

    int com = 0;
    char path[MAX_PATH_LENGTH];
    char * lastPath;

    int quit = 0;

    while(1) {
        switch(com) {

            case 0:
                printf("%s", menuInfo);
                break;

            case 1:
                printf("Input path to directory:\n");
                scanf("%s", path);
                if(dir_is_valid(path)) {
                    pathToStack(path, &stack);
                    //showDirContent(path);
                } else {
                    printf("There is no such directory\n");
                }
                break;
            
            case 2:
                delLastPath(&stack);
                break;

            case 3:
                lastPath = getLastPath(&stack);
                if(!lastPath) {
                    printf("There are no paths in memory\n");
                } else {
                    showDirContent(lastPath);
                }
                break;
            
            case 4:
                quit = 1;
                break;

            default:
                printf("Wrong command!\n%s", menuInfo);
                break;
        }

        if(quit)
            break;
        
        printf("Input a command: ");
        scanf("%d", &com);
    }
}

void pathToStack(const char * dirname, Stack * stack) {
    char * dirname_cpy = (char*)malloc(sizeof(char)*(strlen(dirname)+1));
    strcpy(dirname_cpy, dirname);
    push(stack, (void*)dirname_cpy);
}

char * getLastPath(Stack * stack) {
    if(stackIsEmpty(stack))
        return NULL;
    return (char*)top(stack);
}

void delLastPath(Stack * stack) {
    if(stackIsEmpty(stack))
        return;
    pop(stack);
}

char * getAndDelLastPath(Stack * stack) {
    if(stackIsEmpty(stack))
        return NULL;
    char * lastPath = (char*)top(stack);
    pop(stack);
    return lastPath;
}

void showDirContent(const char * dirname) {
    DIR * dir;
    struct dirent * entry;

    dir = opendir(dirname);
    if(!dir) {
        printf("Error: wrong name of the directory\n");
        return;
    }

    while((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int dir_is_valid(char * path) {
    DIR * dir;
    dir = opendir(path);
    if(!dir) {;
        return 0;
    }
    return 1;
}
