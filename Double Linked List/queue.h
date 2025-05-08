// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASYARAKAT_UMUM 1
#define MAHASISWA 2
#define DOSEN 3

typedef struct ElmtQueue *addressQueue;
typedef struct ElmtQueue {
    char nama[50];
    int priority;
    addressQueue next;
    addressQueue prev;
} ElmtQueue;

typedef struct {
    addressQueue HEAD;
    addressQueue TAIL;
} Queue;

void createEmptyQueue(Queue *Q);
addressQueue alokasiQueue(char nama[], int priority);
int isEmptyQueue(Queue Q);
void enqueue(Queue *Q, addressQueue P);
void dequeue(Queue *Q, addressQueue *P);
void printInfoQueue(Queue Q);
void printInfoQueueReverse(Queue Q);

#endif

