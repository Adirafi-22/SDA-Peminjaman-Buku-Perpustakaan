#include "queue.h"

void createEmptyQueue(Queue *Q) {
    (*Q).HEAD = NULL;
    (*Q).TAIL = NULL;
}

addressQueue alokasiQueue(char nama[], int priority) {
    addressQueue P = (addressQueue)malloc(sizeof(ElmtQueue));
    if (P != NULL) {
        strcpy(P->nama, nama);
        P->priority = priority;
        P->next = NULL;
        P->prev = NULL;
    }
    return P;
}

int isEmptyQueue(Queue Q) {
    return (Q.HEAD == NULL && Q.TAIL == NULL);
}

void enqueue(Queue *Q, addressQueue P) {
    if (isEmptyQueue(*Q)) {
        (*Q).HEAD = P;
        (*Q).TAIL = P;
    } else if (P->priority > (*Q).HEAD->priority) {
        P->next = (*Q).HEAD;
        (*Q).HEAD->prev = P;
        (*Q).HEAD = P;
    } else {
        addressQueue curr = (*Q).HEAD;
        while (curr != NULL && P->priority <= curr->priority) {
            curr = curr->next;
        }
        if (curr == NULL) {
            P->prev = (*Q).TAIL;
            (*Q).TAIL->next = P;
            (*Q).TAIL = P;
        } else {
            P->next = curr;
            P->prev = curr->prev;
            curr->prev->next = P;
            curr->prev = P;
        }
    }
}

void dequeue(Queue *Q, addressQueue *P) {
    if (!isEmptyQueue(*Q)) {
        *P = (*Q).HEAD;
        if ((*Q).HEAD == (*Q).TAIL) {
            (*Q).HEAD = NULL;
            (*Q).TAIL = NULL;
        } else {
            (*Q).HEAD = (*Q).HEAD->next;
            (*Q).HEAD->prev = NULL;
        }
        (*P)->next = NULL;
        (*P)->prev = NULL;
    } else {
        *P = NULL;
    }
}

void printInfoQueue(Queue Q) {
    addressQueue P = Q.HEAD;
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
    } else {
        printf("\n=== ANTRIAN PEMINJAM ===\n");
        printf("%-20s | %s\n", "Nama", "Prioritas");
        printf("-----------------------------------\n");
        while (P != NULL) {
            char prioritasStr[20];
            switch (P->priority) {
                case DOSEN: strcpy(prioritasStr, "Dosen"); break;
                case MAHASISWA: strcpy(prioritasStr, "Mahasiswa"); break;
                case MASYARAKAT_UMUM: strcpy(prioritasStr, "Masyarakat Umum"); break;
                default: strcpy(prioritasStr, "Unknown");
            }
            printf("%-20s | %s\n", P->nama, prioritasStr);
            P = P->next;
        }
        printf("\n");
    }
}

void printInfoQueueReverse(Queue Q) {
    addressQueue P = Q.TAIL;
    if (isEmptyQueue(Q)) {
        printf("Antrian kosong\n");
    } else {
        printf("\n=== ANTRIAN PEMINJAM (TERBALIK) ===\n");
        printf("%-20s | %s\n", "Nama", "Prioritas");
        printf("-----------------------------------\n");
        while (P != NULL) {
            char prioritasStr[20];
            switch (P->priority) {
                case DOSEN: strcpy(prioritasStr, "Dosen"); break;
                case MAHASISWA: strcpy(prioritasStr, "Mahasiswa"); break;
                case MASYARAKAT_UMUM: strcpy(prioritasStr, "Masyarakat Umum"); break;
                default: strcpy(prioritasStr, "Unknown");
            }
            printf("%-20s | %s\n", P->nama, prioritasStr);
            P = P->prev;
        }
        printf("\n");
    }
}

