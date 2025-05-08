#include "stack.h"

void createEmptyStack(Stack *S) {
    (*S).TOP = -1;
    (*S).BOTTOM = -1;
    (*S).jumlah = 0;
}

int isEmptyStack(Stack S) {
    return (S.jumlah == 0);
}

int isFullStack(Stack S) {
    return (S.jumlah == MAX_AKTIVITAS);
}

void push(Stack *S, Aktivitas aktivitas) {
    if (isFullStack(*S)) {
        printf("Stack penuh, tidak bisa menambah data.\n");
    } else {
        (*S).data[(*S).TOP] = aktivitas;
        (*S).TOP++;
        (*S).jumlah++;
    }
}

void pop(Stack *S, Aktivitas *val) {
    if (isEmptyStack(*S)) {
        printf("Stack kosong, tidak bisa menghapus data.\n");
    } else {
        *val = (*S).data[(*S).TOP];
        (*S).TOP--;
        (*S).jumlah--;
    }
}

void printInfoStack(Stack S) {
    if (isEmptyStack(S)) {
        printf("Stack kosong\n");
    } else {
        printf("\n=== HISTORY AKTIVITAS ===\n");
        int i;
        for ( i = 0; i < S.jumlah; i++) {
            printf("%s\n", S.data[i].namaPeminjam);
        }
    }
}

// Implementasi fungsi printInfoStackReverse
void printInfoStackReverse(Stack S) {
    if (isEmptyStack(S)) {
        printf("Stack kosong\n");
    } else {
        printf("\n=== HISTORY AKTIVITAS (TERBALIK) ===\n");
        int i;
        for ( i = S.BOTTOM; i >= 0; i--) {
            printf("%s\n", S.data[i].namaPeminjam);
        }
    }
}

