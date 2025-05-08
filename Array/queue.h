#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi konstanta prioritas
#define MASYARAKAT_UMUM 1
#define MAHASISWA 2
#define DOSEN 3

// Definisi maksimum ukuran antrian
#define MAX_ANTRIAN 50

// Struktur data untuk pengguna/peminjam (digunakan di queue)
typedef struct {
    char nama[50];
    int priority;
} ElmtQueue;

// Struktur data untuk antrian dengan prioritas
typedef struct {
    ElmtQueue data[MAX_ANTRIAN];
    int HEAD;
    int TAIL;
    int jumlah;
} Queue;

// Deklarasi fungsi untuk Queue
void createEmptyQueue(Queue *Q);
int isEmptyQueue(Queue Q);
int isFullQueue(Queue Q);
void enqueue(Queue *Q, char nama[], int priority);
void dequeue(Queue *Q, ElmtQueue *val);
void printInfoQueue(Queue Q);
void printInfoQueueReverse(Queue Q);

#endif

