/* File : stack.h */
/* Definisi ADT Stack dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef STACK_H
#define STACK_H

#include "../boolean.h"
#include "../pesanan/pesanan.h"

#ifndef IDX_UNDEF
#define IDX_UNDEF -1
#endif
#define STACK_CAPACITY 100

typedef struct {
  Pesanan buffer[STACK_CAPACITY]; /* tabel penyimpan elemen */
  int idxTop;              /* alamat TOP: elemen puncak */
  int tasCap; /* kapasitas tas, dapat berkembang sesuai Mobita */
} Stack;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Stack, maka akses elemen : */
#define IDX_TOP(s) (s).idxTop
#define     TOP(s) (s).buffer[(s).idxTop]
#define TASCAPACITY(s) (s).tasCap

/* *** Konstruktor/Kreator *** */
void CreateStack(Stack *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isEmptyStack(Stack s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isFullStack(Stack s);
/* Mengirim true jika tabel penampung nilai s stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void push(Stack *s, Pesanan val);
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void pop(Stack *s, Pesanan *val);
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

void deleteIdxTas(Stack *s, int idx, Pesanan *val);
/* Menghapus elemen dengan indeks idx dari Stack s */
/* I.S. idx indeks yang valid di s */
/* F.S. val berisi item dengan indeks idx dari list, val dihapus dari list, IDX_TOP berkurang 1,  */

/* ************ Menambah kapasitas Stack ************ */
void increaseTasCapacity(Stack *s);
/* Menambah kapasitas tas sejumlah 1 */
/* I.S. Tas terdefinisi */
/* F.S. TASCAPACITY(*s) bertambah 1 */
void increase2TimesTasCapacity(Stack *s);
/* Menambah kapasitas tas sejumlah 2 kali lipat sebelumnya */
/* I.S. Tas terdefinisi */
/* F.S. TASCAPACITY(*s) bertambah 2 kali lipat saat TASCAPACITY(*s) < 50
   TASCAPACITY(*s) = 100 saat TASCAPACITY >= 50 */

#endif

