#ifndef ITEM_H
#define ITEM_H

#include "../boolean.h"

/* Struktur data Item
   Jenis tipe Item:
   - Normal Item, type 'N', expired -1
   - Heavy Item, type 'H', expired -1
   - Perishable Item, tipe 'P', dengan expiry tertentu.
*/

typedef struct item
{
   char type;
   int expired;
} Item;

#define TYPE_UNDEF 'X'
#define TYPE(x) (x).type
#define EXPIRED(x) (x).expired

/* KREATOR */
/* I.S. x bebas
   F.S. Item x terdefinisi dengan tipe itemType dan expired expiryTime
*/
void createItem(Item *x, char itemType, int expiryTime);

/* Mengecek apakah Item a dan b memiliki tipe dan expiry time sama */
boolean isItemEqual(Item a, Item b);

void printItemType(Item x);
/*mengembalikan nama item*/

int getItemPrice(Item x);
/* menampilkan harga dari setiap item */
#endif
