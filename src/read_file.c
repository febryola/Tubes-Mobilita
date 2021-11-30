#include <stdio.h>
#include <math.h>
#include "commands/commands.h"
#include "modules/adt.h"
#include "read_file.h"

boolean endWord;
Word currentWord;

void swap(Pesanan *xp, Pesanan *yp)
{
    Pesanan temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortPsn(Pesanan temp[],int length){
    for (int i=0;i<length-1;i++){
        for (int j=0;j<length-i-1;j++){
            if (temp[j].time > temp[j+1].time){
                swap(&temp[j],&temp[j+1]);
            }
        }
    }
}

void bacaFile (Word namafile, Matrix *peta, Matrix *adj, Queue *pesanan, ListDin *lBuilding){
    int row,col;
    FILE *fp;
    fp = fopen(namafile.contents,"r");

    /* Inisialisasi peta */
    startWordFile(fp);
    row = charToInt(currentWord);
    advWord();
    col = charToInt(currentWord);
    CreateMatrix(row+2,col+2,peta);
    initMap(peta);
    
    /* HQ */
    advWord();
    int rowHQ = charToInt(currentWord);
    advWord();
    int colHQ = charToInt(currentWord);
    setElmtMat(peta,'8',rowHQ,colHQ);

    /* Isi peta */
    advWord();
    int N = charToInt(currentWord);
    CreateListDin(lBuilding,N+1);
    for (int i=0;i<N;i++){
        advWord();
        char bangunan = currentWord.contents[0];
        advWord();
        int rowBangunan = charToInt(currentWord);
        advWord();
        int colBangunan = charToInt(currentWord);
        setElmtMat(peta,bangunan,rowBangunan,colBangunan);
        setElmtLDin(lBuilding,bangunan,rowBangunan,colBangunan,i+1);
    }
    setElmtLDin(lBuilding,'8',rowHQ,colHQ,0);

    /* Adj Mat */
    CreateMatrix(N+1,N+1,adj);
    for (int i=0;i<N+1;i++){
        for (int j=0;j<N+1;j++){
            advWord();
            setElmtMat(adj,currentWord.contents[0],i,j);
        }
    }

    /* Pesanan */
    Pesanan psn;
    Item item;
    int Ptval;
    advWord();
    int M = charToInt(currentWord);
    Pesanan temp[M];
    for (int i=0;i<M;i++){
        Ptval = -1;
        advWord();
        int tMasuk = charToInt(currentWord);
        advWord();
        POINT pickUp = elmtToPoint(*peta,currentWord.contents[0]);
	    Name(pickUp) = currentWord.contents[0];
        advWord();
        POINT dropOff = elmtToPoint(*peta,currentWord.contents[0]);
	    Name(dropOff) = currentWord.contents[0];
        advWord();
        char type = currentWord.contents[0];
        if (type == 'P'){
            advWord();
            Ptval = charToInt(currentWord);
        }
        createItem(&item,type,Ptval);
        SetPesanan(&psn,tMasuk,pickUp,dropOff,item,Ptval);
        if (type == 'P') {
            DPTIME(psn) = Ptval;
        }
        temp[i] = psn;
    }


    sortPsn(temp,M);

    for (int i=0;i<M;i++){
        enqueue(pesanan,temp[i]);
    }
    
}
