#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h" 

typedef struct {
    char namaPeminjam[50];
    char judulBuku[50];
    int tipePriority;
    int tipeAktivitas; // 1: Pinjam, 2: Kembalikan, 3: Batalkan
} Aktivitas;

typedef struct ElmtStack *addressStack;
typedef struct ElmtStack {
    Aktivitas info;
    addressStack next;
} ElmtStack;

typedef struct {
    addressStack TOP;
} Stack;

void createEmptyStack(Stack *S);
addressStack alokasiStack(Aktivitas aktivitas);
int isEmptyStack(Stack S);
void push(Stack *S, addressStack P);
void pop(Stack *S, addressStack *P);
void printInfoStack(Stack S);

#endif

