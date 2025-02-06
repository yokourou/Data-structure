#include <stdlib.h>
#include <stdio.h>
#include "sierpinski.h"

list_triangles *addTriangle(list_triangles *l, triangle I) {
    list_triangles *l2 = malloc(sizeof(list_triangles));
    l2->next = l;
    l2->ABC = I;
    return l2;
}

triangle nouvtriangleC(triangle I) {
    triangle nouv;
    nouv.A.x = (I.A.x + I.C.x) / 2;
    nouv.A.y = (I.A.y + I.C.y) / 2;
    nouv.B.x = (I.B.x + I.C.x) / 2;
    nouv.B.y = (I.B.y + I.C.y) / 2;
    nouv.C.x = I.C.x;
    nouv.C.y = I.C.y;
    return nouv;
}

triangle nouvtriangleA(triangle I) {
    triangle nouv;
    nouv.C.x = (I.C.x + I.A.x) / 2;
    nouv.C.y = (I.C.y + I.A.y) / 2;
    nouv.B.x = (I.B.x + I.A.x) / 2;
    nouv.B.y = (I.B.y + I.A.y) / 2;
    nouv.A.x = I.A.x;
    nouv.A.y = I.A.y;
    return nouv;
}

triangle nouvtriangleB(triangle I) {
    triangle nouv;
    nouv.C.x = (I.C.x + I.B.x) / 2;
    nouv.C.y = (I.C.y + I.B.y) / 2;
    nouv.C.x = (I.C.x + I.B.x) / 2;
    nouv.C.y = (I.C.y + I.B.y) / 2;
    nouv.B.x = I.B.x;
    nouv.B.y = I.B.y;
    return nouv;
}

void sierpinski_n(list_triangles *l, int n) {
    if (n > 0) {
        while (l != NULL) {
            list_triangles *nouv = l->next;
            triangle currenttr = l->ABC;
            l->ABC = nouvtriangleA(currenttr);
            l = addTriangle(l, nouvtriangleB(currenttr));
            l = addTriangle(l, nouvtriangleC(currenttr));
            l = l->next;
        }
        sierpinski_n(l, n - 1);
    }
}

void listTrianglesFree(list_triangles *l) {
    if (l != NULL) {
        listTrianglesFree(l->next);
        free(l);
    }
}
