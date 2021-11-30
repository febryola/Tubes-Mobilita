#ifndef GADGET_H
#define GADGET_H

/* Tipe Gadget */

/* 
	Jenis-jenis gadget, gadgetType dilambangkan dengan:
	1. Kain Pembungkus Waktu (800 Yen), gadgetType 'A'
	2. Senter Pembesar (1200 Yen), gadgetType 'B'
	3. Pintu Kemana Saja (1500 Yen) gadgetType 'C'
	4. Mesin Waktu (3000 Yen) gadgetType 'D'
*/

typedef char Gadget;

boolean isGadgetValid(Gadget x);

/* Proses: Menuliskan output nama Gadget secara lengkap */
void printGadgetName(Gadget x);

int displayGadgetPrice(Gadget x);
/* menampilkan harga dari setiap gadget */
#endif