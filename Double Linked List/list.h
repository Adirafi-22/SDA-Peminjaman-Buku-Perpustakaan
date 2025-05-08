// list.h
#ifndef LIST_H
#define LIST_H

#include "queue.h"

typedef struct ElmtList *addressList;
typedef struct ElmtList {
    char judul[50];
    int stok;
    Queue antrianPeminjam;
    addressList next;
    addressList prev;
} ElmtList;

typedef struct {
    addressList FIRST;
    addressList LAST;
} List;

void createEmpty(List *L);
addressList alokasi(char judul[], int stok);
void insertFirst(List *L, addressList P);
void insertLast(List *L, addressList P);
void insertAfter(addressList prec, addressList P);
void deleteFirst(List *L, addressList *P);
void deleteLast(List *L, addressList *P);
void deleteAfter(addressList prec, addressList *P);
addressList findElm(List L, char judul[]);
void printInfo(List L);
void printInfoReverse(List L);

#endif
