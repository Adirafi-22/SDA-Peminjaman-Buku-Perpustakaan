#include "list.h"
#include "stack.h"
#include "queue.h"
#include "common.h"

void tambahBuku(List *L, char judul[], int stok) {
    addressList P = alokasi(judul, stok);
    if (P != NULL) {
        insertLast(L, P);
        printf("Buku '%s' berhasil ditambahkan dengan stok %d.\n", judul, stok);
    } else {
        printf("Gagal menambahkan buku.\n");
    }
}

void tambahStok(List *L, char judul[], int tambahan) {
    addressList P = findElm(*L, judul);
    if (P != NULL) {
        P->stok += tambahan;
        printf("Stok buku '%s' berhasil ditambah menjadi %d.\n", judul, P->stok);
    } else {
        printf("Buku '%s' tidak ditemukan.\n", judul);
    }
}

void pinjamBuku(List *L, Stack *S, char judul[], char nama[], int priority) {
    addressList buku = findElm(*L, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }
    addressQueue peminjam = alokasiQueue(nama, priority);
    if (peminjam != NULL) {
        enqueue(&(buku->antrianPeminjam), peminjam);
        printf("Anda telah masuk antrian untuk meminjam buku '%s'.\n", judul);
        Aktivitas aktivitas;
        strcpy(aktivitas.namaPeminjam, nama);
        strcpy(aktivitas.judulBuku, judul);
        aktivitas.tipePriority = priority;
        aktivitas.tipeAktivitas = 1;
        addressStack P = alokasiStack(aktivitas);
        if (P != NULL) {
            push(S, P);
        }
    } else {
        printf("Gagal menambahkan ke antrian peminjam.\n");
    }
}

void kembalikanBuku(List *L, Stack *S, char judul[], char nama[]) {
    addressList buku = findElm(*L, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }
    buku->stok++;
    printf("Buku '%s' berhasil dikembalikan oleh '%s'. Stok sekarang: %d\n", judul, nama, buku->stok);
    Aktivitas aktivitas;
    strcpy(aktivitas.namaPeminjam, nama);
    strcpy(aktivitas.judulBuku, judul);
    aktivitas.tipePriority = 0;
    aktivitas.tipeAktivitas = 2;
    addressStack P = alokasiStack(aktivitas);
    if (P != NULL) {
        push(S, P);
    }
}

void batalkanAktivitas(List *L, Stack *S) {
    addressStack P;
    pop(S, &P);
    if (P == NULL) {
        printf("Tidak ada aktivitas untuk dibatalkan.\n");
        return;
    }
    printf("Membatalkan aktivitas terakhir...\n");
    switch (P->info.tipeAktivitas) {
        case 1: {
            addressList buku = findElm(*L, P->info.judulBuku);
            if (buku != NULL && !isEmptyQueue(buku->antrianPeminjam)) {
                addressQueue peminjam;
                dequeue(&(buku->antrianPeminjam), &peminjam);
                if (peminjam != NULL) {
                    free(peminjam);
                }
            }
            printf("Peminjaman buku '%s' oleh '%s' dibatalkan.\n", P->info.judulBuku, P->info.namaPeminjam);
            break;
        }
        case 2: {
            addressList buku = findElm(*L, P->info.judulBuku);
            if (buku != NULL && buku->stok > 0) {
                buku->stok--;
                printf("Pengembalian buku '%s' oleh '%s' dibatalkan.\n", P->info.judulBuku, P->info.namaPeminjam);
            }
            break;
        }
        default:
            printf("Aktivitas tidak dikenal.\n");
    }
    free(P);
}

void prosesPeminjaman(List *L, Stack *S, char judul[]) {
    addressList buku = findElm(*L, judul);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judul);
        return;
    }
    if (buku->stok <= 0) {
        printf("Stok buku '%s' habis. Tidak bisa memproses peminjaman.\n", judul);
        return;
    }
    if (isEmptyQueue(buku->antrianPeminjam)) {
        printf("Tidak ada antrian peminjam untuk buku '%s'.\n", judul);
        return;
    }
    addressQueue peminjam;
    dequeue(&(buku->antrianPeminjam), &peminjam);
    if (peminjam != NULL) {
        buku->stok--;
        printf("Peminjaman buku '%s' oleh '%s' berhasil diproses. Stok tersisa: %d\n", judul, peminjam->nama, buku->stok);
        Aktivitas aktivitas;
        strcpy(aktivitas.namaPeminjam, peminjam->nama);
        strcpy(aktivitas.judulBuku, judul);
        aktivitas.tipePriority = peminjam->priority;
        aktivitas.tipeAktivitas = 1;
        addressStack P = alokasiStack(aktivitas);
        if (P != NULL) {
            push(S, P);
        }
        free(peminjam);
    }
}

int main() {
    List daftarBuku;
    Stack historyAktivitas;
    int pilihan, stok, priority;
    char judul[50], nama[50];
    createEmpty(&daftarBuku);
    createEmptyStack(&historyAktivitas);

    do {
        printf("\n=============================================\n");
        printf("    SISTEM PEMINJAMAN BUKU PERPUSTAKAAN\n");
        printf("=============================================\n");
        printf("1. Tambah Buku\n");
        printf("2. Tambah Stok\n");
        printf("3. Pinjam Buku\n");
        printf("4. Proses Peminjaman\n");
        printf("5. Kembalikan Buku\n");
        printf("6. Batalkan Aktivitas Terakhir\n");
        printf("7. Lihat Data Buku\n");
        printf("8. Lihat Data Buku (Reverse)\n");
        printf("9. Lihat History Aktivitas\n");
        printf("10. Lihat History Aktivitas (Reverse)\n");
        printf("11. Lihat Antrian Peminjam\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan); getchar();

        switch (pilihan) {
            case 1:
                clearScreen();
                printf("\n--- TAMBAH BUKU ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Stok: ");
                scanf("%d", &stok); getchar();
                tambahBuku(&daftarBuku, judul, stok);
                break;
            case 2:
                clearScreen();
                printf("\n--- TAMBAH STOK ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Tambahan stok: ");
                scanf("%d", &stok); getchar();
                tambahStok(&daftarBuku, judul, stok);
                break;
            case 3:
                clearScreen();
                printf("\n--- PINJAM BUKU ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Nama peminjam: ");
                fgets(nama, 50, stdin);
                nama[strcspn(nama, "\n")] = 0;
                printf("Prioritas (1: Masyarakat Umum, 2: Mahasiswa, 3: Dosen): ");
                scanf("%d", &priority); getchar();
                pinjamBuku(&daftarBuku, &historyAktivitas, judul, nama, priority);
                break;
            case 4:
                clearScreen();
                printf("\n--- PROSES PEMINJAMAN ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                prosesPeminjaman(&daftarBuku, &historyAktivitas, judul);
                break;
            case 5:
                clearScreen();
                printf("\n--- KEMBALIKAN BUKU ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Nama peminjam: ");
                fgets(nama, 50, stdin);
                nama[strcspn(nama, "\n")] = 0;
                kembalikanBuku(&daftarBuku, &historyAktivitas, judul, nama);
                break;
            case 6:
                clearScreen();
                batalkanAktivitas(&daftarBuku, &historyAktivitas);
                break;
            case 7:
                clearScreen();
                printInfo(daftarBuku);
                break;
            case 8:
                clearScreen();
                printInfoReverse(daftarBuku);
                break;
            case 9:
                clearScreen();
                printInfoStack(historyAktivitas);
                break;
            case 10:
                clearScreen();
                printInfoStackReverse(historyAktivitas);
                break;
            case 11:
                clearScreen();
                printf("\n--- LIHAT ANTRIAN PEMINJAM ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                {
                    addressList P = findElm(daftarBuku, judul);
                    if (P != NULL) {
                        printInfoQueue(P->antrianPeminjam);
                        printInfoQueueReverse(P->antrianPeminjam);
                    } else {
                        printf("Buku '%s' tidak ditemukan.\n", judul);
                    }
                }
                break;
            case 0:
                printf("Terima kasih telah menggunakan program ini.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        clearScreen();
    } while (pilihan != 0);
    return 0;
}

