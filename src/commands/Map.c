#include <stdio.h>
#include "commands.h"

#include "../modules/adt.h"

/* Inisialisasi map, mengisi matrix map dengan '*' dan ' '*/
void initMap (Matrix *peta){
    int i,j;
    for (i=0;i<ROWS(*peta);i++){
        for (j=0;j<COLS(*peta);j++){
            if ((i == 0) || (j == 0) || (i == ROWS(*peta)-1) || (j == COLS(*peta)-1)){
                setElmtMat(peta,'*',i,j);
            }
            else{
                setElmtMat(peta,' ',i,j);
            }
        }
    }
}

/* mengisi map dengan bangunan sesuai dengan lokasi (index matrix) */
void isiMap (Matrix *peta, int jumlah){
    int i,row,col;
    char val;
    for (i=0;i<jumlah;i++){
        scanf(" %c %d %d",&val,&row,&col);
        setElmtMat(peta,val,row,col);
    }
}

/* mengubah koordinat dari posisi menjadi nama bangunan pada posisi sekarang */
char posisiSkrg (POINT posNow, Matrix lokMat){
    int x = Absis(posNow), y = Ordinat(posNow);
    char posisi = MAT_ELMT(lokMat,x,y);
    return posisi;
}

/* mencetak bangunan sesuai dengan warna */
void printBerwarna (int pilihan, char bangunan){
    switch (pilihan){
    case 1:
        print_yellow(bangunan);
        break;
    case 2:
        print_blue(bangunan);
        break;
    case 3:
        print_red(bangunan);
        break;
    case 4:
        print_green(bangunan);
        break;
    case 5:
        print_black(bangunan);
        break;
    case 7:
        print_cyan(bangunan);
        break;
    default:
        printf("%c",bangunan);
        break;
    }
}

/* konversi bangunan menjadi index matrix Adj */
int posisiToIdx(char bangunan){
    int idx;
    if (bangunan == '8'){
        idx = 0;
    }
    else{
        idx = bangunan-64;
    }
    return idx;
}

/* memeriksa apakah bangunan adjacent dengan posisi sekarang */
boolean cekAdj (Matrix adjMat, char bangunan, char posisiSkrg){
    boolean adj = false;
    int letakAdjMat = posisiToIdx(bangunan), posisi = posisiToIdx(posisiSkrg);
    if (MAT_ELMT(adjMat,posisi,letakAdjMat) == '1'){
        adj = true;
    }
    return adj;
}

boolean cekVIP (Matrix peta, char bangunan, LList toDo){
    boolean ada = false;
    POINT point = elmtToPoint(peta,bangunan);
    Address p = toDo;
    while (!ada && (p != NULL)){
        if (TYPE(ITEM(INFO(p))) == 'V'){
            if (EQ(PICK_UP(INFO(p)), point)){
                ada = true;
            }
        }
        p = NEXT(p);
    }
    return ada;
}

/* memeriksa apakah bangunan ada pada toDo */
boolean cekToDo (Matrix peta, char bangunan, LList toDo){
    boolean ada = false;
    POINT point = elmtToPoint(peta,bangunan);
    Address p = toDo;
    while (!ada && (p != NULL)){
        if (EQ(PICK_UP(INFO(p)), point)){
            ada = true;
        }
        else{
            p = NEXT(p);
        }
    }
    return ada;
}

/* mencetak peta */
void Map (Matrix adjMat, Matrix lokMat, POINT posNow, LList toDo, Stack tas){
    int i,j,warna;
    char bangunan;
    Pesanan drop;
    
    if (!isEmptyStack(tas)){
        pop(&tas,&drop);
    }

    for (i=0;i<ROWS(lokMat);i++){
        for (j=0;j<COLS(lokMat);j++){
            warna = 6;
            bangunan = MAT_ELMT(lokMat,i,j);
            if (bangunan!='*' && bangunan!=' '){
                warna = 5;
            }
            if (cekAdj(adjMat,bangunan,posisiSkrg(posNow,lokMat))){
                warna = 4;
            }
            if (!isEmptyLL(toDo) && cekToDo(lokMat,bangunan,toDo)){
                warna = 3;
            }
            if (!isEmptyLL(toDo) && cekVIP(lokMat,bangunan,toDo)){
                warna = 7;
            }
            if (bangunan == Name(DROP_OFF(drop))){
                warna = 2;
            }
            if (bangunan == posisiSkrg(posNow,lokMat)){
                warna = 1;
            }
            printBerwarna(warna,bangunan);
        }
        printf("\n");
    }
    printf("\n");
}
