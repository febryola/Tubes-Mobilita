#include "../boolean.h"
#include <stdio.h>
#include "pesanan.h"

void SetPesanan(Pesanan *p, int tval, POINT pval, POINT dval, Item ival, int Ptval) {
/* I.S. pesanan p sembarang */
/* F.S. pesanan p terbentuk dengan sbb: */
/* - time bernilai tval */
/* - lokasi pick up bernilai pval */
/* - lokasi drop off bernilai dval */
/* - item bernilai ival */
/* - Ptime bernilai Ptval */
    /* ALGORITMA */
    TIME(*p) = tval;
    PICK_UP(*p) = pval;
    DROP_OFF(*p) = dval;
    ITEM(*p) = ival;
    PTIME(*p) = Ptval;
}

/* Mengecek apakah pesanan a dan b sama */
boolean isPesananEqual(Pesanan a, Pesanan b){
	return (TIME(a) == TIME(b)) && EQ(PICK_UP(a), PICK_UP(b)) 
	&& EQ(DROP_OFF(a), DROP_OFF(b)) && isItemEqual(ITEM(a), ITEM(b)) && (PTIME(a) == PTIME(b));
}

/* *** Kreator *** */
void CreateQueue(Queue *q) {
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */
    IDX_HEAD(*q) = IDX_UNDEF;
	IDX_TAIL(*q) = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmpty(Queue q) {
/* Mengirim true jika q kosong: lihat definisi di atas */
    return (IDX_HEAD(q) == IDX_UNDEF) && (IDX_TAIL(q) == IDX_UNDEF);
}
boolean isFull(Queue q) {
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai CAPACITY-1 */
    return (IDX_HEAD(q) == 0) && (IDX_TAIL(q) == P_CAPACITY-1);
}
int length(Queue q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
    if (isEmpty(q)){
		return 0;
	}
	return (IDX_TAIL(q) - IDX_HEAD(q) + 1);
}

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, Pesanan val) {
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
    int i, tmpIdx = 0;
	if (isEmpty(*q)){
		IDX_HEAD(*q) = 0;
		IDX_TAIL(*q) = 0;
	} else {
		if (IDX_TAIL(*q) == (P_CAPACITY-1)){
			for(i = IDX_HEAD(*q); i <= IDX_TAIL(*q); i++){
				(*q).buffer[i - IDX_HEAD(*q)] = (*q).buffer[i];
			}
			IDX_TAIL(*q) -= IDX_HEAD(*q);
			IDX_HEAD(*q) = 0;
		}
		IDX_TAIL(*q)++;
	}
	TAIL(*q) = val;
}

void dequeue(Queue *q, Pesanan *val) {
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., HEAD dan IDX_HEAD "mundur";
        q mungkin kosong */
    *val = HEAD(*q);
	if (IDX_HEAD(*q) == IDX_TAIL(*q)){
		IDX_HEAD(*q) = IDX_UNDEF;
		IDX_TAIL(*q) = IDX_UNDEF;
	} else {
		IDX_HEAD(*q)++;
	}
}
