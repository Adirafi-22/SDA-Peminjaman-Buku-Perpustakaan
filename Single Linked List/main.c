#include "list.h"
#include "queue.h"
#include "stack.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Deklarasi fungsi tambahan dari main
void tambahBuku(List *L, char judul[], int stok);
void tambahStok(List *L, char judul[], int tambahan);
void pinjamBuku(List *L, Stack *S, char judul[], char nama[], int priority);
void prosesPeminjaman(List *L, Stack *S, char judul[]);
void kembalikanBuku(List *L, Stack *S, char judul[], char nama[]);
void batalkanAktivitas(List *L, Stack *S);

int main() {
    List daftarBuku;
    Stack historyAktivitas;
    int pilihan, stok, priority;
    char judul[50], nama[50];

    createEmpty(&daftarBuku);
    createEmptyStack(&historyAktivitas);

    do {
        printf("\n============================================="
               "\n    SISTEM PEMINJAMAN BUKU PERPUSTAKAAN"
               "\n============================================="
               "\n1. Tambah Buku"
               "\n2. Tambah Stok"
               "\n3. Pinjam Buku"
               "\n4. Proses Peminjaman"
               "\n5. Kembalikan Buku"
               "\n6. Batalkan Aktivitas Terakhir"
               "\n7. Lihat Data Buku"
               "\n8. Lihat History Aktivitas"
               "\n0. Keluar"
               "\nPilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                clearScreen();
                printf("\n--- TAMBAH BUKU ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Stok: ");
                scanf("%d", &stok);
                getchar();
                tambahBuku(&daftarBuku, judul, stok);
                break;
            case 2:
                clearScreen();
                printf("\n--- TAMBAH STOK ---\nJudul buku: ");
                fgets(judul, 50, stdin);
                judul[strcspn(judul, "\n")] = 0;
                printf("Tambahan stok: ");
                scanf("%d", &stok);
                getchar();
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
                scanf("%d", &priority);
                getchar();
                pinjamBuku(&daftarBuku, &historyAktivitas, judul, nama, priority);
                break;
            case 4:
                clearScreen();
                printf("\n--- PROSES PEMINJAMAN ---\nJudul buku yang akan diproses: ");
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
                printf("\n--- BATALKAN AKTIVITAS TERAKHIR ---\n");
                batalkanAktivitas(&daftarBuku, &historyAktivitas);
                break;
            case 7:
                clearScreen();
                printInfo(daftarBuku);
                break;
            case 8:
                clearScreen();
                printInfoStack(historyAktivitas);
                break;
            case 0:
                clearScreen();
                printf("Terima kasih telah menggunakan program ini.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}

