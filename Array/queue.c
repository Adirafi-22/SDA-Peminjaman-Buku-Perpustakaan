#include "queue.h"

void createEmptyQueue(Queue *Q) {
    (*Q).HEAD = 0;
    (*Q).TAIL = -1;
    (*Q).jumlah = 0;
}

int isEmptyQueue(Queue Q) {
    return (Q.jumlah == 0);
}

int isFullQueue(Queue Q) {
    return (Q.jumlah == MAX_ANTRIAN);
}

void enqueue(Queue *Q, char nama[], int priority) {
    if (isFullQueue(*Q)) {
        printf("Queue penuh, tidak bisa menambah data.\n");
    } else {
        if (isEmptyQueue(*Q)) {
            (*Q).HEAD = 0;
            (*Q).TAIL = 0;
            strcpy((*Q).data[0].nama, nama);
            (*Q).data[0].priority = priority;
        } else {
            int position = (*Q).TAIL + 1;  // Bisa disesuaikan sesuai dengan logika prioritas
            strcpy((*Q).data[position].nama, nama);
            (*Q).data[position].priority = priority;
            (*Q).TAIL = position;
        }
        (*Q).jumlah++;
    }
}

void dequeue(Queue *Q, ElmtQueue *val) {
    if (isEmptyQueue(*Q)) {
        printf("Queue kosong, tidak bisa menghapus data.\n");
    } else {
        *val = (*Q).data[(*Q).HEAD];
        (*Q).HEAD++;
        (*Q).jumlah--;
    }
}

void printInfoQueue(Queue Q) {
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
    } else {
        printf("\n=== ANTRIAN PEMINJAM ===\n");
        int i;
        for ( i = Q.HEAD; i <= Q.TAIL; i++) {
            printf("%s\n", Q.data[i].nama);
        }
    }
}

