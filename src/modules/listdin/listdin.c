/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
	 memori list dinamik */

#include <stdio.h>
#include <stdlib.h>

#include "listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
void CreateListDin(ListDin *l, int capacity) {
    LISTDIN_CAPACITY(*l) = capacity;
    LISTDIN_NEFF(*l) = 0;
    BUFFER(*l) = (ListDinElType *)malloc(capacity * sizeof(ListDinElType));
}

/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, LISTDIN_CAPACITY(l)=0; LISTDIN_NEFF(l)=0 */
void dealocate(ListDin *l) {
    LISTDIN_CAPACITY(*l) = 0;
    LISTDIN_NEFF(*l) = 0;
    free(BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */

/* *** Banyaknya elemen *** */
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */
int lengthListDin(ListDin l) {
    return LISTDIN_NEFF(l);
}

/* *** Selektor INDEKS *** */
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
IdxType getLastIdx(ListDin l) {
    return lengthListDin(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxValidLD(ListDin l, int i) {
    return (i >= 0) && (i < LISTDIN_CAPACITY(l));
}

/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..LISTDIN_NEFF(l) */
boolean isIdxEffLD(ListDin l, IdxType i) {
    return (i >= 0) && (i < lengthListDin(l));
}

/* ********** TEST KOSONG/PENUH ********** */

/* *** Test list kosong *** */
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
boolean isEmptyDin(ListDin l) {
    return lengthListDin(l) == 0;
}

/* *** Test list penuh *** */
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
boolean isFullLD(ListDin l) {
    return lengthListDin(l) == LISTDIN_CAPACITY(l);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */

/* *** Mendefinisikan isi list dari pembacaan *** */
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= LISTDIN_CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= LISTDIN_CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
			0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
void readListDin(ListDin *l) {
	ListDinElType p;
	char name;
	int absis, ordinat;
    // TODO: pakai mesin kata, bukan scanf
    int n = IDX_UNDEF, i = 0;
    do {
        // Panjang list
        scanf("%d", &n);
    } while ((n < 0) || (n > LISTDIN_CAPACITY(*l)));
    LISTDIN_NEFF(*l) = n;
    for (i = 0; i < LISTDIN_NEFF(*l); i++) {
        scanf(" %c %d %d", &name, &absis, &ordinat);
		Name(p) = name;
		Absis(p) = absis;
		Ordinat(p) = ordinat;

		ELMT_DIN(*l, i) = p;
		// printf("%c ", Name(ELMT_DIN(*l, i)));
		// printf("(%d,", Absis(ELMT_DIN(*l, i)));
		// printf("%d)", Ordinat(ELMT_DIN(*l, i)));
    }
}
void setElmtLDin(ListDin *lDin, char bangunan, float absis, float ordinat, int index){
    POINT koordinat = MakePOINT(absis,ordinat);
    Name(koordinat) = bangunan;
    ELMT_DIN(*lDin,index) = koordinat;
}


/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
	 antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
	 di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
// void displayListDin(ListDin l){
// 	int i;
// 	printf("[");
// 	for(i = 0; i < lengthListDin(l); i++){
// 		printf("%d", ELMT_DIN(l,i));
// 		if (i < lengthListDin(l)-1) {
// 			printf(",");
// 		}
// 	}
// 	printf("]");
// }

/* I.S. l tidak kosong dan idx berada dalam idx efektif */
/* F.S. Menampilkan nama, absis, dan ordinat elemen pada index ke-idx */
void displayElmtDin(ListDin l, IdxType idx) {
    POINT p;

    p = ELMT_DIN(l, idx);
    printf("%c ", Name(p));
    printf("(%d,", Absis(p));
    printf("%d)", Ordinat(p));
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */
IdxType indexOfDin(ListDin l, char val) {
    int i = 0;
    boolean found = false;
    for (i = 0; i < lengthListDin(l); i++) {
        if (Name(ELMT_DIN(l, i)) == val) {
            return i;
        }
    }
    return IDX_UNDEF;
}

/* ********** OPERASI LAIN ********** */
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
void copyList(ListDin lIn, ListDin *lOut) {
    CreateListDin(lOut, LISTDIN_CAPACITY(lIn));
    LISTDIN_NEFF(*lOut) = LISTDIN_NEFF(lIn);
    int i;
    for (i = 0; i < lengthListDin(lIn); i++) {
        ELMT_DIN(*lOut, i) = ELMT_DIN(lIn, i);
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
void insertLastDin(ListDin *l, ListDinElType val) {
    ELMT_DIN(*l, lengthListDin(*l)) = val;
    LISTDIN_NEFF(*l)
    ++;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
void deleteLastDin(ListDin *l, ListDinElType *val) {
    *val = ELMT_DIN(*l, lengthListDin(*l) - 1);
    LISTDIN_NEFF(*l)
    --;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */

/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
void growList(ListDin *l, int num) {
    ListDin temp;
    int i;
    copyList(*l, &temp);
    dealocate(l);
    CreateListDin(l, lengthListDin(temp) + num);
    LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(temp) + num;
    for (i = 0; i < lengthListDin(temp); i++) {
        ELMT_DIN(*l, i) = ELMT_DIN(temp, i);
        LISTDIN_NEFF(*l)
        ++;
    }
    dealocate(&temp);
}

/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
void shrinkList(ListDin *l, int num) {
    ListDin temp;
    int i;
    copyList(*l, &temp);
    dealocate(l);
    CreateListDin(l, LISTDIN_CAPACITY(temp) - num);
    LISTDIN_CAPACITY(*l) = LISTDIN_CAPACITY(temp) - num;
    for (i = 0; i < lengthListDin(temp); i++) {
        ELMT_DIN(*l, i) = ELMT_DIN(temp, i);
        LISTDIN_NEFF(*l)
        ++;
    }
    dealocate(&temp);
}

/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List tidak kosong */
/* F.S. Ukuran nEff = capacity */
void compactList(ListDin *l) {
    ListDin temp;
    int i;
    void *ptr;

    copyList(*l, &temp);
    ptr = realloc(BUFFER(*l), lengthListDin(temp) * sizeof(ListDinElType));
    LISTDIN_CAPACITY(*l) = lengthListDin(temp);
    for (i = 0; i < lengthListDin(temp); i++) {
        ELMT_DIN(*l, i) = ELMT_DIN(temp, i);
    }
    dealocate(&temp);
}