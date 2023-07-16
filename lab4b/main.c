#include <string.h>
#include "out_qtree.h"

int main() {
    Qtree * qtree = createQtree(10);

    addToQtree(qtree, (KeyType1)"banana", (KeyType2)"luck", (InfoType)10);
    addToQtree(qtree, (KeyType1)"banana", (KeyType2)"luck", (InfoType)20);
    addToQtree(qtree, (KeyType1)"bananas", (KeyType2)"luck", (InfoType)30);
    addToQtree(qtree, (KeyType1)"gym", (KeyType2)"lock", (InfoType)40);
    addToQtree(qtree, (KeyType1)"desk", (KeyType2)"sun", (InfoType)50);
    addToQtree(qtree, (KeyType1)"deer", (KeyType2)"bar", (InfoType)60);
    addToQtree(qtree, (KeyType1)"elephant", (KeyType2)"neck", (InfoType)70);
    addToQtree(qtree, (KeyType1)"goal", (KeyType2)"beer", (InfoType)80);
    addToQtree(qtree, (KeyType1)"duck", (KeyType2)"witch", (InfoType)90);
    addToQtree(qtree, (KeyType1)"wine", (KeyType2)"wind", (InfoType)100);
    addToQtree(qtree, (KeyType1)"bananas", (KeyType2)"luck", (InfoType)110);

    addToQtree(qtree, (KeyType1)"banana", (KeyType2)"luck", (InfoType)120);
    addToQtree(qtree, (KeyType1)"banana", (KeyType2)"luck", (InfoType)130);
    addToQtree(qtree, (KeyType1)"bananas", (KeyType2)"luck", (InfoType)140);
    addToQtree(qtree, (KeyType1)"gym", (KeyType2)"lock", (InfoType)150);
    addToQtree(qtree, (KeyType1)"desk", (KeyType2)"sun", (InfoType)160);
    addToQtree(qtree, (KeyType1)"deer", (KeyType2)"bar", (InfoType)170);
    addToQtree(qtree, (KeyType1)"elephant", (KeyType2)"neck", (InfoType)180);
    addToQtree(qtree, (KeyType1)"goal", (KeyType2)"beer", (InfoType)190);
    addToQtree(qtree, (KeyType1)"duck", (KeyType2)"witch", (InfoType)200);
    addToQtree(qtree, (KeyType1)"wine", (KeyType2)"wind", (InfoType)210);
    addToQtree(qtree, (KeyType1)"bananas", (KeyType2)"luck", (InfoType)220);

    delItemWithSeqNum(qtree, (KeyType1)"banana", (KeyType2)"luck", 1);

    print_qtree(stdout, qtree);

    List * list = search(qtree, (KeyType1)"banana", (KeyType2)"luck");
    if(list) {
        print_list(stdout, list);
        freeList(list);
    }

    freeQtree(qtree);
    return 0;
}