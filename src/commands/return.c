#include <stdio.h>
#include "../modules/adt.h"

/* Proses: Mengembalikan item di tumpukan teratas kembali ke lokasi pick up */
/* F.S. Jika item teratas bukan VIP item dan dan canReturn = true,
/*			pesanan di tumpukan teratas tas dan paling pertama di inprogress akan dikembalikan ke todo */
/*			Time limit perishable item akan di-reset */
void returnToSender(LList *inprogress, LList *todo, Stack *tas, boolean *canReturn){
	if(*canReturn){
		if(!isEmptyStack(*tas)){
		Pesanan val;
			if ((TYPE(ITEM(INFO(FIRST(*inprogress)))) != 'V')){ // teratas bukan VIP Item
				pop(tas, &val);
				deleteFirst(inprogress, &val);
				PTIME(val) = EXPIRED(ITEM(val)); // reset perish countdown time
				insertLastLL(todo, val);

				printItemType(ITEM(val));
				printf(" berhasil dikembalikan ke Pick Up Point %c\n", Name(PICK_UP(val)));

				*canReturn = false;
			} else { // teratas VIP Item
				printf("VIP Item tidak bisa dikembalikan!\n");
			}
		}
		else{
			printf("Tas kosong!\n");
		}
	} else { // canReturn = false
		printf("Mobita tidak memliki Ability Return To Sender!\n");
	}
}