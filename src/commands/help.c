#include <stdio.h>
#include "commands.h"
#include "../modules/boolean.h"

void help(boolean *canReturn) {
    printf("MENU HELP\n");
    printf("1. MOVE       -> Menampilkan pilihan lokasi serta pindah ke lokasi yang ada\n");
    printf("2. PICK_UP    -> Mengambil item jika ada pesanan yang harus diambil pada lokasi\n");
    printf("3. DROP_OFF   -> Mengantarkan item ke lokasi jika item di tumpukan teratas sesuai pesanan\n");
    printf("4. MAP        -> Menampilkan peta\n");
    printf("5. TO_DO      -> Menampilkan pesanan yang masuk To Do List\n");
    printf("6. IN_PROGESS -> Menampilkan pesanan yang sedang dikerjakan\n");
    printf("7. BUY        -> Menampilkan gadget yang dapat dibeli dan membelinya (Hanya dapat dipanggil di HQ)\n");
    printf("8. INVENTORY  -> Menampilkan list isi inventory\n");
    printf("9. HELP       -> Menampilkan menu ini\n");
    printf("10. EXIT      -> Keluar dari permainan\n");
    if(canReturn){
        printf("11. RETURN    -> Mengembalikan item di tumpukan teratas kembali ke posisi pick up");
    }
}
