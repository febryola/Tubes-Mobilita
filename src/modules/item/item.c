#include "../boolean.h"
#include "item.h"

#include <stdio.h>

/* KREATOR */
/* I.S. x bebas
   F.S. Item x terdefinisi dengan tipe itemType dan expired expiryTime
*/
void createItem(Item *x, char itemType, int expiryTime){
	TYPE(*x) = itemType;
	EXPIRED(*x) = expiryTime;
}

boolean isItemEqual(Item a, Item b){
   return (TYPE(a) == TYPE(b)) && (EXPIRED(a) == EXPIRED(b));
}

void printItemType(Item x){
	switch(TYPE(x)){
		case 'P':
			printf("Perishable Item");
            break;
		case 'N':
			printf("Normal Item");
            break;
		case 'H':
			printf("Heavy Item");
            break;
		case 'V':
			printf("VIP Item");
            break;
	}
}
/*mengembalikan nama item*/

int getItemPrice(Item x){
    int money;
    if(TYPE(x) == 'P'){
        money = 400;
    } else if (TYPE(x) == 'N'){
        money = 200;
    } else if (TYPE(x) == 'H'){
        money = 400;
    } else if (TYPE(x) == 'V'){
        money = 600;
    }
    return money;
}