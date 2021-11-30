#include "pesanan_todo.h"

#include <stdio.h>
#include <stdlib.h>

void CreateList(LList *l) {
    FIRST(*l) = NULL;
}

boolean isEmptyLL(LList l) {
    return FIRST(l) == NULL;
}

Pesanan getPesanan(LList l, int idx) {
    Address p;
    p = l;
    if (!(idx == lengthListLinked(l))) {
        for (int i = 0; i < idx; i++) {
            p = NEXT(p);
        }
        return INFO(p);
    } else {
        Pesanan x;
        return x;
    }
}

void setPesanan(LList *l, int idx, Pesanan val) {
    int i;
    Address p;

    i = 0;
    p = *l;
    if (idx == lengthListLinked(*l)) {
        insertLastLL(l, val);
    } else {
        while (i < idx) {
            i++;
            p = NEXT(p);
        }
        INFO(p) = val;
    }
}

int indexOfLL(LList l, Pesanan val) {
    Address p;
    boolean found;
    int i;
    p = l;
    found = false;
    i = 0;
    while (p != NULL && !found) {
        if (isPesananEqual(INFO(p), val)) {
            found = true;
        } else {
            p = NEXT(p);
            i++;
        }
    }
    if (found) {
        return i;
    } else {
        return IDX_UNDEF;
    }
}

void insertFirst(LList *l, Pesanan val) {
    Address p;

    p = newNode(val);
    if (p != NULL) {
        NEXT(p) = *l;
        *l = p;
    }
}

void insertLastLL(LList *l, Pesanan val) {
    Address p, last;

    if (isEmptyLL(*l)) {
        insertFirst(l, val);
    } else {
        p = newNode(val);
        if (p != NULL) {
            last = *l;
            while (NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(LList *l, Pesanan val, int idx) {
    Address p, loc;
    int i;

    if (idx == 0) {
        insertFirst(l, val);
    } else if (idx == lengthListLinked(*l)) {
        insertLastLL(l, val);
    } else {
        p = newNode(val);
        if (p != NULL) {
            loc = *l;
            i = 0;
            while (i < idx - 1) {
                loc = NEXT(loc);
                i++;
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
        }
    }
}

void deleteFirst(LList *l, Pesanan *val) {
    Address p;

    p = *l;
    *val = INFO(p);
    *l = NEXT(p);
    free(p);
}

void deleteLastLL(LList *l, Pesanan *val) {
    Address p, loc;

    p = *l;
    loc = NULL;
    while (NEXT(p) != NULL) {
        loc = p;
        p = NEXT(p);
    }
    if (loc == NULL) {
        *l = NULL;
    } else {
        NEXT(loc) = NULL;
    }
    *val = INFO(p);
    free(p);
}

void deleteAt(LList *l, int idx, Pesanan *val) {
    Address p, loc;
    int ctr;

    if (idx == 0) {
        deleteFirst(l, val);
    } else {
        ctr = 0;
        loc = *l;
        while (ctr < idx - 1) {
            ctr++;
            loc = NEXT(loc);
        }
        p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        free(p);
    }
}

int lengthListLinked(LList l) {
    int i;
    Address p;

    i = 0;
    p = l;
    while (p != NULL) {
        i++;
        p = NEXT(p);
    }
    return i;
}