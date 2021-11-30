#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "modules/adt.h"
#include "main_menu.h"

int cekFileAda(char namaFile[]){
    FILE *fileKonfigurasi;
    char cwd[WM_CAPACITY];
    Word path,isi;

    getcwd(cwd, sizeof(cwd));
    path = concatKata(cwd,"/src/config/");
    isi = concatKata(path.contents,namaFile);
    if (fileKonfigurasi = fopen(isi.contents,"r")){
        fclose(fileKonfigurasi);
        return 1;
    }
    return 0;
}

Word getFullPath(char namaFile[]){
    FILE *fileKonfigurasi;
    char cwd[WM_CAPACITY];
    Word path,isi;

    getcwd(cwd, sizeof(cwd));
    path = concatKata(cwd,"/src/config/");
    isi = concatKata(path.contents,namaFile);
    return isi;
}

void MainMenu(Word *filePath){
    int pilihan;
    char namaFile[WM_CAPACITY];
    printf("SELAMAT DATANG DI PERMAINAN MOBITA\n");
    printf("1.NEW GAME\n");
    printf("2.EXIT\n");
    printf("Masukkan pilihan anda: ");
    startWord();
    pilihan = charToInt(currentWord);
    while ((pilihan != 1) && (pilihan != 2)){
        printf("Masukan pilihan salah, coba lagi!\n");
        printf("Masukkan pilihan anda: ");
        startWord();
        pilihan = charToInt(currentWord);
    }

    if (pilihan == 1){
        printf("Masukkan nama file konfigurasi level (dalam .txt): ");
        startWord();
        for (int i=0;i<currentWord.length;i++){
            namaFile[i] = currentWord.contents[i];
        }
        namaFile[currentWord.length] = '\0';
        while ((cekFileAda(namaFile) == 0)){
            printf("File tidak ditemukan, coba lagi!\n");
            printf("Masukkan nama file konfigurasi level (dalam .txt): ");
            startWord();
            for (int i=0;i<currentWord.length;i++){
                namaFile[i] = currentWord.contents[i];
            }
            namaFile[currentWord.length] = '\0';
        }
        *filePath = getFullPath(namaFile);
        printf("\n");
    }
    else if (pilihan == 2){
        exit(0);
    }
}
