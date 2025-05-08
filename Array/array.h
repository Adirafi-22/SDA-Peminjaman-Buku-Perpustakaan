#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Definisi maksimum ukuran array buku
#define MAX_BUKU 100

// Struktur data untuk buku
typedef struct {
    char judul[50];
    int stok;
    Queue antrianPeminjam;
} ElmtArray;

// Struktur data untuk array buku
typedef struct {
    ElmtArray data[MAX_BUKU];
    int jumlah;
} Array;

// Deklarasi fungsi untuk Array
void createEmptyArray(Array *A);
int findElmArray(Array A, char judul[]);
void insertArray(Array *A, char judul[], int stok);
void deleteArray(Array *A, int idx);
void printInfoArray(Array A);
void printInfoArrayReverse(Array A);

#endif

