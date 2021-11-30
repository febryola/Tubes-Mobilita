#include <stdio.h>
#include "commands.h"

#include "../modules/adt.h"

void inProgress(LList inprogress) {
    int ctr;
    Pesanan pesan;

    if (!isEmptyLL(inprogress)) {
        ctr = 0;
        Address p = inprogress;
        
        printf("Pesanan yang sedang diantarkan: \n");
        while(p != NULL) {
            pesan = INFO(p);
            ctr++;
            if (TYPE(ITEM(pesan)) == 'N'){
                printf("%d. Normal Item (Tujuan: %c)\n",ctr,Name(DROP_OFF(pesan)));
            }
            else if (TYPE(ITEM(pesan)) == 'H'){
                printf("%d. Heavy Item (Tujuan: %c)\n",ctr,Name(DROP_OFF(pesan)));
            }
            else if (TYPE(ITEM(pesan)) == 'P'){
                printf("%d. Perishable Item (Tujuan: %c) (Waktu tersisa: %d)\n",ctr,Name(DROP_OFF(pesan)),PTIME(pesan));
            }
            else { // TYPE(ITEM(pesan)) == 'V'
                printf("%d. VIP Item (Tujuan: %c)\n",ctr,Name(DROP_OFF(pesan)));
            }
            p = NEXT(p);
        }
    } 
    
    else {
        printf("Pesanan kosong.\n");
    }
}
