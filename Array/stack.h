#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi maksimum ukuran stack
#define MAX_AKTIVITAS 100

// Struktur data untuk aktivitas (digunakan di stack)
typedef struct {
    char namaPeminjam[50];
    char judulBuku[50];
    int tipePriority;
    int tipeAktivitas; // 1: Pinjam, 2: Kembalikan, 3: Batalkan
} Aktivitas;

// Struktur data untuk stack
typedef struct {
    Aktivitas data[MAX_AKTIVITAS];
    int TOP;
    int BOTTOM;
    int jumlah;
} Stack;

// Deklarasi fungsi untuk Stack
void createEmptyStack(Stack *S);
int isEmptyStack(Stack S);
int isFullStack(Stack S);
void push(Stack *S, Aktivitas aktivitas);
void pop(Stack *S, Aktivitas *val);
void printInfoStack(Stack S);
void printInfoStackReverse(Stack S);  // Pastikan fungsi ini dideklarasikan

#endif

