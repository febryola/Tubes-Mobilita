#include <stdio.h>
#include "../modules/adt.h"
#include "commands.h"

boolean isCommandValid(char command){
    return (command == '0') || (command == '1') || (command == '2') || (command == '3') || (command == '4');
}

/* Proses: Menampilkan antarmuka pembelian gadget */
/* I.S. Mobita berada di Headquarter, banyak gadget dalam inventory tidak melebihi capacity. */
/*      Terdapat uang sebesar money yen, uang bisa kosong */
/* F.S. Jika list gadget tidak kosong dan uang cukup, gadget yang terbeli masuk ke inventory */
/* 		Jika pembelian gagal, menuliskan pesan. */
void buy(POINT posNow, Matrix lokMat, ListGadget *l, int *money){
    if (Name(posNow) == '8'){ // lagi di headquarter
        if(!isFullListGadget(*l)){ // masih bisa membeli gadget
            char command, gtype;
            int cost = 0;

            printf("Uang anda sekarang: %d Yen\n", *money);
            printf("Gadget yang tersedia:\n");
            printf("1. Kain Pembungkus Waktu (800 Yen)\n");
            printf("2. Senter Pembesar (1200 Yen)\n");
            printf("3. Pintu Kemana Saja (1500 Yen)\n");
            printf("4. Mesin Waktu (3000 Yen)\n");
            printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");

            printf("\nENTER COMMAND: ");
            startWord();
            while(!isCommandValid(currentWord.contents[0])){
                printf("Command tidak valid!\n");
                printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
                printf("\nENTER COMMAND: ");
                startWord();
            }
            if (currentWord.contents[0] != '0'){
                if (currentWord.contents[0] == '1'){
                    cost = 800; // Kain pembungkus waktu
                    gtype = 'A';
                } else if (currentWord.contents[0] == '2'){
                    cost = 1200; // Senter pembesar
                    gtype = 'B';
                } else if (currentWord.contents[0] == '3'){
                    cost = 1500; // Pintu kemana saja
                    gtype = 'C';
                } else if (currentWord.contents[0] == '4'){
                    cost = 3000; // Mesin waktu
                    gtype = 'D';
                }
                if (*money >= cost){
                    *money -= cost;
                    insertGadget(l, gtype);
                    printGadgetName(gtype);
                    printf(" berhasil dibeli.\n");
                } else {
                    printf("Uang tidak cukup untuk membeli Gadget!\n");
                }
            }
        } else { // list gadget penuh
            printf("Inventory anda penuh. Anda tidak bisa membeli gadget baru.\n");
        }
    } else {
        printf("Pembelian Gadget hanya bisa dilakukan di Headquarter.\n");
    }
}
