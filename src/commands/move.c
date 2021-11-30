#include <stdio.h>

#include "../modules/adt.h"
#include "../read_file.h"
#include "commands.h"

void move(Matrix adjMat, POINT *posNow, int *time, ListDin lBuilding, int *timestep, int saveTime, int *timeSpeed) {
    int ctr, rowIdx, input;
    int posSelected;

    // Adjacency HQ: Elemen ke-0, Adjacency A: elemen ke-1, dst
    ctr = 1;
    /*rowIdx = Name(*posNow) - 64;*/
    rowIdx = posisiToIdx(Name(*posNow));

    printf("Posisi yang dapat dicapai: \n");
    // HQ
    // useGadget == menggunakan pintu kemana saja
    if (((MAT_ELMT(adjMat, rowIdx, 0) == '1') || *timestep == 0) && ('8' != Name(*posNow))) {
        printf("%d. HQ (%x", ctr, Absis(ELMT_DIN(lBuilding, 0)));
        printf(",%x)\n", Ordinat(ELMT_DIN(lBuilding, 0)));
        ctr++;
    }
    // Iterasi kolom
    for (int j = 1; j < COLS(adjMat); j++) {
        if (((MAT_ELMT(adjMat, rowIdx, j) == '1') || *timestep == 0) && (Name(ELMT_DIN(lBuilding, j)) != Name(*posNow))) {
            printf("%d. ", ctr);
            displayElmtDin(lBuilding, j);
            printf("\n");
            ctr++;
        }
    }

    ctr--;

    // Handler jika input tidak valid
    do {
        printf("Posisi yang dapat dipilih? (Ketik 0 jika ingin kembali)\n");
        printf("ENTER COMMAND: ");
        startWord();
        input = charToInt(currentWord);
        if ((input < 0) || (input > ctr)) {
            printf("Input tidak valid. Ulangi. \n");
        }
    } while ((input < 0) || (input > ctr));

    // Select bangunan
    if (input != 0) {
        ctr = 0;
        posSelected = 0;
        for (int j = 0; j < COLS(adjMat); j++) {
            if (ctr == input) {
                break;
            } else {
                if (MAT_ELMT(adjMat, rowIdx, j) == '1' || (*timestep == 0 && (Name(ELMT_DIN(lBuilding, j)) != Name(*posNow)))) {
                    ctr++;
                }
                posSelected++;
            }
        }
        *posNow = ELMT_DIN(lBuilding, posSelected - 1);
        if (*timestep != 0) {
            if (*timeSpeed == 0) {
                *time += *timestep;
            } else {
                if (*timeSpeed % 2 != 0) {
                    *time += 1;
                }
                *timeSpeed -= 1;
                if (*timeSpeed == 0) {
                    printf("Ability Speed Boost telah habis\n");
                }
            }
        } else {
            *timestep = saveTime;
        }
    } else {
        printf("MOVE dibatalkan.\n");
    }
}
