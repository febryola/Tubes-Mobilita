/* File: listgadget.h */

/* MODUL PENYIMPANAN GADGET YANG SUDAH DIBELI */
/* modifikasi ADT List Statis */

#ifndef LISTGADGET_H
#define LISTGADGET_H

#include <stdio.h>
#include "../boolean.h"
#include "../gadget/gadget.h"

/*  Kamus Umum */
#ifndef IDX_UNDEF
	#define IDX_UNDEF -1
#endif
/* Indeks tak terdefinisi*/
#define GADGET_UNDEF '0'
/* Nilai elemen tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef struct {
	Gadget contents[5]; /* memori tempat penyimpan elemen (container) */
} ListGadget;
/* Indeks yang digunakan [0..4] */
/* Jika l adalah ListGadget, cara deklarasi dan akses: */
/* Deklarasi : l : ListGadget */
/* Maka cara akses:
	 GADGET_ELMT(l,i) untuk mengakses elemen ke-i */
/* Definisi :
	 List kosong: semua elemen bernilai GADGET_UNDEF
	 Definisi elemen pertama: GADGET_ELMT(l,i) dengan i=0 */

/* ********** SELEKTOR ********** */
#define GADGET_ELMT(l, i) (l).contents[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
/* I.S. l sembarang */
/* F.S. Terbentuk ListGadget l kosong dengan kapasitas 5 */
/* Proses: Inisialisasi semua elemen List l dengan GADGET_UNDEF, set capacity 5 */
void CreateListGadget(ListGadget *l){
	int i;
	for(i = 0; i < 5; i++){
		GADGET_ELMT(*l, i) = GADGET_UNDEF;
	}
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
int lengthListGadget(ListGadget l){
	int i = 0;
	int count = 0;
	while(i < 5){
		if (GADGET_ELMT(l,i) != GADGET_UNDEF) {
			count++;
		}
		i++;
	}
	return count;
}

/* ********** Test Indeks yang valid ********** */
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxListGadgetValid(ListGadget l, int i){
	return (i >= 0) && (i <= 5);
}
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
boolean isIdxListGadgetEff(ListGadget l, int i){
	return (i >= 0) && (i <= lengthListGadget(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isEmptyListGadget(ListGadget l){
	return lengthListGadget(l) == 0;
}
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
boolean isFullListGadget(ListGadget l){
	return lengthListGadget(l) == 5;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* Proses : Menuliskan isi List Gadget, format seperti di inventory */
void displayListGadget(ListGadget l){
	int i;
    int j = 1;
    for (i = 0; i < 5; i++) {
        printf("%d. ", (i+1));
        if (isGadgetValid(GADGET_ELMT(l,i))) {
					printGadgetName(GADGET_ELMT(l,i)); printf("\n");
        } else {
            printf("-\n");
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN ********** */
/* Proses: Menambahkan val sebagai elemen dalam list, di indeks tempat GADGET_UNDEF pertama */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
void insertGadget(ListGadget *l, Gadget val){
	int i = 0;
	while(GADGET_ELMT(*l, i) != GADGET_UNDEF){
		i++;
	}
	GADGET_ELMT(*l, i) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* Proses : Menghapus elemen List pada indeks tertentu */
/* I.S. List tidak kosong, idx indeks yang valid */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
void deleteGadget(ListGadget *l, int idx, Gadget *val){
    *val = GADGET_ELMT(*l,idx);
    GADGET_ELMT(*l, idx) = GADGET_UNDEF;
}

#endif
