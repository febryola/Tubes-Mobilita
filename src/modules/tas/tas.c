#include <stdio.h>
#include "tas.h"

/* *** Konstruktor/Kreator *** */
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */
void CreateStack(Stack *s){
	IDX_TOP(*s) = IDX_UNDEF;
	TASCAPACITY(*s) = 3;
}

/* ************ Prototype ************ */
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isEmptyStack(Stack s){
	return IDX_TOP(s) == IDX_UNDEF;
}
/* Mengirim true jika tabel penampung nilai s stack penuh */
boolean isFullStack(Stack s){
	return IDX_TOP(s) == TASCAPACITY(s)-1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
/* Menambahkan val sebagai elemen Stack s */
/* I.S. s mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */
void push(Stack *s, Pesanan val){
	IDX_TOP(*s)++;
	TOP(*s) = val;
}

/* ************ Menghapus sebuah elemen Stack ************ */
/* Menghapus val dari Stack s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */
void pop(Stack *s, Pesanan *val){
	*val = TOP(*s);
	IDX_TOP(*s)--;
}

/* Menghapus elemen dengan indeks idx dari Stack s */
/* I.S. idx indeks yang valid di s */
/* F.S. val berisi item dengan indeks idx dari list, val dihapus dari list, IDX_TOP berkurang 1,  */
void deleteIdxTas(Stack *s, int idx, Pesanan *val){
  *val = (*s).buffer[idx];
  int i;
  for(i = idx+1; i <= IDX_TOP(*s); i++){
      (*s).buffer[i-1] = (*s).buffer[i];
  }
  IDX_TOP(*s)--;
}

/* ************ Menambah kapasitas Stack ************ */
/* Menambah kapasitas tas sejumlah 1 */
/* I.S. Tas terdefinisi */
/* F.S. TASCAPACITY(*s) bertambah 1 saat TASCAPACITY(*s) < STACK_CAPACITY */
void increaseTasCapacity(Stack *s){
    if (TASCAPACITY(*s) < STACK_CAPACITY) {
        TASCAPACITY(*s)++;
    }
}

/* Menambah kapasitas tas sejumlah 2 kali lipat sebelumnya */
/* I.S. Tas terdefinisi */
/* F.S. TASCAPACITY(*s) bertambah 2 kali lipat saat TASCAPACITY(*s) < 50
   TASCAPACITY(*s) = 100 saat TASCAPACITY >= 50 */
void increase2TimesTasCapacity(Stack *s) {
    if (TASCAPACITY(*s) < 50) {
        TASCAPACITY(*s) = 2 * TASCAPACITY(*s);
    } else {
        TASCAPACITY(*s) = 100;
    }
}
