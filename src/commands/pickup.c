#include <stdio.h>
#include "commands.h"

#include "../modules/adt.h"

/* Proses: mengambil item jika ada pesanan yang harus diambil pada lokasi. */
/* I.S. posNow, LokMat, todo, inprogress, tas terdefinisi */
/* F.S. Jika ada pesanan pada lokasi dan tas tidak penuh, */
/* 			- Item didelete dari todo */
/* 			- Item di-insertLast ke inprogress */
/* 			- Item dimasukkan ke tas */
/* 			Jika tidak ada pesanan pada lokasi, ditampilkan pesan. */
void pickUp(POINT posNow, Matrix LokMat, LList *todo, LList *inprogress, Stack *tas, int *incTime, int *timeSpeed, int VIP){
	Pesanan thisPesanan;

	boolean pesananFound = false;
	boolean adaPesanan = false;
	int i = 0;
	Address p = *todo;
	while(!pesananFound && (p != NULL)){ // iterasi todo, cari yang posisinya sesuai dengan posNow
	    if (VIP > 0) {
            if(EQ(PICK_UP(INFO(p)), posNow)){
                adaPesanan = true;
            }

            if(EQ(PICK_UP(INFO(p)), posNow) && TYPE(ITEM(INFO(p))) == 'V'){
                pesananFound = true;
                deleteAt(todo, i, &thisPesanan); // delete pesanan dari todo
                thisPesanan = INFO(p);
            } else {
                p = NEXT(p);
                i++;
            }
	    } else {
            if(EQ(PICK_UP(INFO(p)), posNow)){
                pesananFound = true;
                deleteAt(todo, i, &thisPesanan); // delete pesanan dari todo
                thisPesanan = INFO(p);
            } else {
                p = NEXT(p);
                i++;
            }
	    }
	}

	if (pesananFound){ // ketemu

		if (!isFullStack(*tas)){ // kalo tasnya tidak penuh

			insertFirst(inprogress, thisPesanan); // taroh pesanan ke inprogress
			push(tas, thisPesanan); // taroh itemnya ke tas

			// output tipe pesanan
			printf("Pesanan berupa ");
			printItemType(ITEM(thisPesanan));
			printf(" berhasil diambil!\n");
			// output tujuan pesanan
			printf("Tujuan Pesanan: %c\n", Name(DROP_OFF(thisPesanan)));

			if(TYPE(ITEM(thisPesanan)) == 'H'){ // heavyItem menambah incTime
				*incTime += 1;
				if (*timeSpeed != 0) {
                    *timeSpeed = 0;
                    printf("Anda mendapatkan pesanan Heavy Item\n");
                    printf("Ability Speed Boost hilang\n");
				}
			}

		} else { // tas penuh
			printf("Tas anda penuh. Anda tidak dapat menambah pesanan lagi.\n");
		}

	} else if (adaPesanan) {
		printf("Pesanan tidak dapat diambil. Selesaikan pesanan VIP terlebih dahulu.");
	} else { // tidak ada pesanan di posisi itu
	    printf("Pesanan tidak ditemukan!");
	}
}
