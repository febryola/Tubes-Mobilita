#include <stdio.h>
#include<stdlib.h>

#include "commands/commands.h"
#include "modules/adt.h"
#include "main_menu.h"
#include "read_file.h"

#if defined(__WIN32) || defined(__WIN64) // Powershell
    #define clearscreen system("cls")
#else // Bash
    #define clearscreen system("clear")
#endif

/* Proses: iterasi elemen di inprogress dan tas, dan menghapus semua item yang sudah perish */
/* I.S. Terdefinisi */
/* F.S. Jika time-TIME() elemen dari list lebih dari PTIME, elemen terhapus */
/*      Item di-pop dari tas */
// TODO: pindahin entah ke mana
void perishExpiredItem(LList *inprogress, Stack *tas){
    Pesanan val,psn;
    Stack dummy;
    int i = 0;
    Address p = *inprogress; // iterasi inprogress
    while(p != NULL){
        if(PTIME(INFO(p)) == 0){ // countdown perish item sudah 0
            deleteAt(inprogress, i, &val);
        }
        p = NEXT(p);
        i++;
    }

    //tas
    CreateStack(&dummy);
    TASCAPACITY(dummy) = TASCAPACITY(*tas);
    while (!isEmptyStack(*tas)){
        pop(tas,&psn);
        if(PTIME(psn) != 0){
            push(&dummy,psn);
        }
    }

    while (!isEmptyStack(dummy)){
        pop(&dummy,&psn);
        push(tas,psn);
    }
}


void reducePerish(Stack *tas, LList *inprogress, int time){
    Address p = *inprogress;
    Pesanan pesan;
    Stack dummy;

    //reduce inprogress
    while (p != NULL){
        if (TYPE(ITEM(INFO(p))) == 'P'){
            PTIME(INFO(p)) = PTIME(INFO(p)) - time;
            if (PTIME(INFO(p)) < 0){
                PTIME(INFO(p)) = 0;
            }
        }
        p = NEXT(p);
    }

    //reduce tas
    CreateStack(&dummy);
    TASCAPACITY(dummy) = TASCAPACITY(*tas);
    while (!isEmptyStack(*tas)){
        pop(tas,&pesan);
        if (TYPE(ITEM(pesan)) == 'P'){
            PTIME(pesan) = PTIME(pesan) - time;
            if (PTIME(pesan) < 0){
                PTIME(pesan) = 0;
            }
        }
        push(&dummy,pesan);
    }

    while (!isEmptyStack(dummy)){
        pop(&dummy,&pesan);
        push(tas,pesan);
    }
}

int main(){
    Matrix peta,adj;
    Queue pesanan;
    ListDin lBuilding;
    char command[50];
    Word fileKonfig;
    POINT posisi;
    Stack tas;
    ListGadget gadgetInventory;
    LList todo, inprogress;
    Gadget gadgetUsed;

    int money = 0; // uang Mobita
    int time = 0; // waktu berjalan
    int incTime = 1; // skala penambahan waktu
    int saveTime = 0; // tempat penyimpan waktu sebelum ability
    int timeSpeed = 0; // menyimpan ability Speed Boost
    boolean canReturn = false; // kondisi apakah Mobita bisa return
    int VIP = 0; // efek dari pesanan VIP
    int psnBerhasil = 0; //jumlah pesanan yang berhasil diantarkan

    CreateListGadget(&gadgetInventory);
    CreateStack(&tas);
    CreateQueue(&pesanan);
    MainMenu(&fileKonfig);
    bacaFile(fileKonfig,&peta,&adj,&pesanan,&lBuilding);
    posisi = elmtToPoint(peta,'8');
    Name(posisi) = '8';

    // temporary variables
    Pesanan val;

    do{
        if ((isEmpty(pesanan)) && (isEmptyLL(todo)) && (isEmptyLL(inprogress)) && (isEmptyStack(tas)) && (Name(posisi) == '8')) {
            printf("Game selesai!\n");
            break;
        }
        else {
            printf("\n\n");
            printf("Mobita berada di titik %c",MAT_ELMT(peta,Absis(posisi),Ordinat(posisi)));
            TulisPOINT(posisi);
            printf("\n");
            printf("Waktu: %d\n", time);
            printf("Uang yang dimiliki: %d Yen\n", money);
            printf("Banyak pesanan VIP: %d\n", VIP);
            printf("ENTER COMMAND: ");
            startWord();
            for (int i = 0; i < currentWord.length; i ++) {
                command[i] = currentWord.contents[i];
            }
            command[currentWord.length] = '\0';
            clearscreen;

            if (cekKataSama(command,"MOVE")){
                int tempTime = time;
                move(adj,&posisi,&time,lBuilding,&incTime,saveTime,&timeSpeed);

                // tiap pindah waktu, pindahin pesanan dari queue pesanan ke linkedlist todo
                int i = 0;
                for (int j=tempTime;j<=time;j++){
                    while(TIME(HEAD(pesanan)) == j){
                        if (TYPE(ITEM(HEAD(pesanan))) == 'V') {
                            VIP++;
                        }
                        dequeue(&pesanan, &val);
                        insertLastLL(&todo, val);
                        i++;
                    }
                }

                tempTime = time - tempTime;
                reducePerish(&tas,&inprogress,tempTime);

                if (i != 0){
                    printf("%d pesanan baru masuk!",i);
                }

                // tiap pindah waktu, item yang lewat time limit perish
                perishExpiredItem(&inprogress, &tas);

            }
            else if (cekKataSama(command,"PICK_UP")){
                pickUp(posisi, peta, &todo, &inprogress, &tas, &incTime, &timeSpeed, VIP);
            }
            else if (cekKataSama(command,"DROP_OFF")){
                dropOff(&tas,&inprogress,posisi,&money,&incTime,&timeSpeed,&canReturn,&VIP,&psnBerhasil);

                if ((isEmpty(pesanan)) && (isEmptyLL(todo)) && (isEmptyLL(inprogress)) && (isEmptyStack(tas)) && (Name(posisi) != '8')) {
                    printf("Pesanan sudah habis. Silahkan kembali ke Headquarter.\n");
                }

            }
            else if (cekKataSama(command,"MAP")){
                Map(adj,peta,posisi,todo,tas);
            }
            else if (cekKataSama(command,"TO_DO")){
                todolist(todo);
            }
            else if (cekKataSama(command,"IN_PROGRESS")){
                inProgress(inprogress);
            }
            else if (cekKataSama(command,"BUY")){
                buy(posisi, peta, &gadgetInventory, &money);
            }
            else if (cekKataSama(command,"INVENTORY")){
                inventory(&gadgetInventory,&time,&incTime,&saveTime,&tas, &inprogress, &gadgetUsed);
                if (gadgetUsed == 'C') {
                    // Pintu kemana saja digunakan
                    move(adj,&posisi,&time,lBuilding,&incTime,saveTime,&timeSpeed);
                }
            }
            else if (cekKataSama(command,"HELP")){
                help(&canReturn);
            }
            else if (cekKataSama(command,"RETURN")){
                returnToSender(&inprogress, &todo, &tas, &canReturn);

            }
            else if (cekKataSama(command,"EXIT")){
                printf("TERIMA KASIH SUDAH BERMAIN\n");
            }
            else{
                printf("Masukan command tidak valid, coba lagi!");
            }
        }
    }while(!cekKataSama(command,"EXIT"));

    printf("\n-------------Statistik Akhir-------------\n");
    printf("Jumlah pesanan yang berhasil diantar: %d\n",psnBerhasil);
    printf("Waktu yang terlampaui: %d\n",time);

    exit(0);
}
