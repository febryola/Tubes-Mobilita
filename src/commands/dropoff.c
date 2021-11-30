#include <stdio.h>
#include "../modules/adt.h"
#include "commands.h"

void dropOff(Stack *tas, LList *inprogress, POINT p, int *money, int *incTime, int *timeSpeed, boolean *canReturn, int *VIP, int *psnBerhasil) {
    Pesanan val;
    if (EQ(DROP_OFF(TOP(*tas)),p)) { /* harus memakai adt pesanan untuk menunjukkan point dropnya dimana */
        if (TYPE(ITEM(TOP(*tas))) == 'N') {
            printf("Pesanan Normal Item berhasil diantarkan\n");
            printf("Uang yang didapatkan: 200 Yen\n");
        } else if (TYPE(ITEM(TOP(*tas))) == 'H') {
            printf("Pesanan Heavy Item berhasil diantarkan\n");
            printf("Uang yang didapatkan: 400 Yen\n");
            *incTime -= 1;
            if (*incTime == 1) {
                *timeSpeed = 10;
                printf("Ability yang didapatkan: Speed Boost\n");
                printf("Karena berhasil mengantarkan Heavy Item, anda bergerak lebih cepat!\n");
            } else {
                printf("Tas Anda terlalu berat\n");
                printf("Gagal mendapatkan ability Speed Boost\n");
            }
        } else if (TYPE(ITEM(TOP(*tas))) == 'P') {
            printf("Pesanan Perishable Item berhasil diantarkan\n");
            printf("Uang yang didapatkan: 400 Yen\n");
            printf("Ability yang didapatkan: Increase Capacity\n");
            increaseTasCapacity(tas);
            printf("Kapasitas tas anda bertambah 1!\n");
        } else if (TYPE(ITEM(TOP(*tas))) == 'V') {
            printf("Pesanan VIP Item berhasil diantarkan\n");
            printf("Uang yang didapatkan: 600 Yen\n");
            printf("Ability yang didapatkan: Return To Sender\n");
            *canReturn = true;
            printf("Anda dapat menggunakan perintah RETURN!\n");
            *VIP = *VIP - 1;
        }
        *money += getItemPrice(ITEM(TOP(*tas)));
        pop(tas,&val);
        deleteFirst(inprogress, &val); // delete dari list inprogress
        *psnBerhasil = *psnBerhasil + 1;
    } else {
        printf("Tidak terdapat pesanan yang dapat diantarkan\n");
    }
}
