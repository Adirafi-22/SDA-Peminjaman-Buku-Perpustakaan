#ifndef LIBRARY_H
#define LIBRARY_H

#include "list.h"
#include "stack.h"
#include "queue.h"

void tambahBuku(List *L, char judul[], int stok);
void tambahStok(List *L, char judul[], int tambahan);
void pinjamBuku(List *L, Stack *S, char judul[], char nama[], int priority);
void prosesPeminjaman(List *L, Stack *S, char judul[]);
void kembalikanBuku(List *L, Stack *S, char judul[], char nama[]);
void batalkanAktivitas(List *L, Stack *S);

#endif

