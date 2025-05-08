#include "library.h"

void tambahBuku(List *L, char judul[], int stok) {
    addressList P = findElm(*L, judul);
    if (P == NULL) {
        P = alokasi(judul, stok);
        insertFirst(L, P);
        printf("Buku '%s' berhasil ditambahkan dengan stok %d.\n", judul, stok);
    } else {
        P->stok += stok;
        printf("Stok buku '%s' ditambahkan. Stok sekarang: %d\n", judul, P->stok);
    }
}

void tambahStok(List *L, char judul[], int tambahan) {
    addressList P = findElm(*L, judul);
    if (P != NULL) {
        P->stok += tambahan;
        printf("Stok buku '%s' ditambahkan. Stok sekarang: %d\n", judul, P->stok);
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void pinjamBuku(List *L, Stack *S, char judul[], char nama[], int priority) {
    addressList P = findElm(*L, judul);
    if (P != NULL) {
        addressQueue Peminjam = alokasiQueue(nama, priority);
        enqueue(&(P->antrianPeminjam), Peminjam);
        printf("'%s' telah ditambahkan ke dalam antrian peminjam buku '%s'.\n", nama, judul);
        Aktivitas aktivitas;
        strcpy(aktivitas.namaPeminjam, nama);
        strcpy(aktivitas.judulBuku, judul);
        aktivitas.tipePriority = priority;
        aktivitas.tipeAktivitas = 1;
        addressStack As = alokasiStack(aktivitas);
        push(S, As);
        if (P->stok > 0) {
            printf("Stok buku '%s' tersedia. Proses peminjaman dapat dilakukan.\n", judul);
        } else {
            printf("Stok buku '%s' kosong. Masuk dalam antrian peminjaman.\n", judul);
        }
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void prosesPeminjaman(List *L, Stack *S, char judul[]) {
    addressList P = findElm(*L, judul);
    if (P != NULL) {
        if (P->stok > 0 && !isEmptyQueue(P->antrianPeminjam)) {
            addressQueue Peminjam;
            dequeue(&(P->antrianPeminjam), &Peminjam);
            P->stok--;
            printf("Peminjaman buku '%s' oleh '%s' berhasil diproses.\n", judul, Peminjam->nama);
            Aktivitas aktivitas;
            strcpy(aktivitas.namaPeminjam, Peminjam->nama);
            strcpy(aktivitas.judulBuku, judul);
            aktivitas.tipePriority = Peminjam->priority;
            aktivitas.tipeAktivitas = 1;
            addressStack As = alokasiStack(aktivitas);
            push(S, As);
            free(Peminjam);
        } else if (P->stok <= 0) {
            printf("Stok buku '%s' kosong. Tidak dapat memproses peminjaman.\n", judul);
        } else {
            printf("Tidak ada antrian peminjam untuk buku '%s'.\n", judul);
        }
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void kembalikanBuku(List *L, Stack *S, char judul[], char nama[]) {
    addressList P = findElm(*L, judul);
    if (P != NULL) {
        P->stok++;
        printf("Buku '%s' berhasil dikembalikan oleh '%s'. Stok sekarang: %d\n", judul, nama, P->stok);
        Aktivitas aktivitas;
        strcpy(aktivitas.namaPeminjam, nama);
        strcpy(aktivitas.judulBuku, judul);
        aktivitas.tipePriority = 0;
        aktivitas.tipeAktivitas = 2;
        addressStack As = alokasiStack(aktivitas);
        push(S, As);
        if (!isEmptyQueue(P->antrianPeminjam)) {
            printf("Ada antrian peminjam untuk buku '%s'. Siap untuk diproses.\n", judul);
            printInfoQueue(P->antrianPeminjam);
        }
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void batalkanAktivitas(List *L, Stack *S) {
    if (!isEmptyStack(*S)) {
        addressStack P;
        pop(S, &P);
        if (P->info.tipeAktivitas == 1) {
            addressList bookP = findElm(*L, P->info.judulBuku);
            if (bookP != NULL) {
                addressQueue current = bookP->antrianPeminjam.HEAD;
                addressQueue prev = NULL;
                int found = 0;
                while (current != NULL && !found) {
                    if (strcmp(current->nama, P->info.namaPeminjam) == 0) {
                        found = 1;
                        if (prev == NULL) {
                            bookP->antrianPeminjam.HEAD = current->next;
                            if (bookP->antrianPeminjam.HEAD == NULL) {
                                bookP->antrianPeminjam.TAIL = NULL;
                            }
                        } else if (current->next == NULL) {
                            prev->next = NULL;
                            bookP->antrianPeminjam.TAIL = prev;
                        } else {
                            prev->next = current->next;
                        }
                        free(current);
                    } else {
                        prev = current;
                        current = current->next;
                    }
                }
                printf("Peminjaman buku '%s' oleh '%s' dibatalkan.\n", P->info.judulBuku, P->info.namaPeminjam);
            }
        } else if (P->info.tipeAktivitas == 2) {
            addressList bookP = findElm(*L, P->info.judulBuku);
            if (bookP != NULL) {
                bookP->stok--;
                printf("Pengembalian buku '%s' oleh '%s' dibatalkan. Stok sekarang: %d\n", P->info.judulBuku, P->info.namaPeminjam, bookP->stok);
            }
        }
        Aktivitas aktivitas;
        strcpy(aktivitas.namaPeminjam, P->info.namaPeminjam);
        strcpy(aktivitas.judulBuku, P->info.judulBuku);
        aktivitas.tipePriority = P->info.tipePriority;
        aktivitas.tipeAktivitas = 3;
        addressStack As = alokasiStack(aktivitas);
        push(S, As);
        free(P);
    } else {
        printf("Tidak ada aktivitas yang dapat dibatalkan.\n");
    }
}

