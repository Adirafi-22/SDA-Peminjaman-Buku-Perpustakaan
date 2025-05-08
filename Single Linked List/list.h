#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct ElmtList *addressList;
typedef struct ElmtList {
    char judul[50];
    int stok;
    Queue antrianPeminjam;
    addressList next;
} ElmtList;

typedef struct {
    addressList FIRST;
} List;

void createEmpty(List *L);
addressList alokasi(char judul[], int stok);
void insertFirst(List *L, addressList P);
void deleteFirst(List *L, addressList *P);
addressList findElm(List L, char judul[]);
void printInfo(List L);

#endif

