#ifndef MENU_H
#define MENU_H

#include "stack.h"

#define MAX_PATH_LENGTH 1000 //in bytes

void menu();

void pathToStack(const char * dirname, Stack * stack);

char * getLastPath(Stack * stack);

void delLastPath(Stack * stack);

char * getAndDelLastPath(Stack * stack);

void showDirContent(const char * dirname);

int dir_is_valid(char * path);

#endif
