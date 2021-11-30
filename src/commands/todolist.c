#include <stdio.h>
#include "commands.h"

#include "../modules/pesanan/pesanan.h"
#include "../modules/item/item.h"

void todolist(LList toDo){
    printf("Pesanan pada To Do List:\n");
    Address p = toDo;
    int i = 1;
    while(p != NULL){
        if (TYPE(ITEM(INFO(p))) == 'P'){
            printf("%d. %c -> %c (Perishable Item), sisa waktu: %d\n", i,Name(PICK_UP(INFO(p))),Name(DROP_OFF(INFO(p))),(PTIME(INFO(p))/*-TIME(INFO(p))*/));
        }
        else if (TYPE(ITEM(INFO(p))) == 'N'){
            printf("%d. %c -> %c (Normal Item)\n", i,Name(PICK_UP(INFO(p))),Name(DROP_OFF(INFO(p))));
        }
        else if (TYPE(ITEM(INFO(p))) == 'H'){
            printf("%d. %c -> %c (Heavy Item)\n", i,Name(PICK_UP(INFO(p))),Name(DROP_OFF(INFO(p))));
        }
        else { // TYPE(ITEM(INFO(p))) == 'V'
            printf("%d. %c -> %c (VIP Item)\n", i,Name(PICK_UP(INFO(p))),Name(DROP_OFF(INFO(p))));
        }
        i++;
        p = NEXT(p);
    }
}
