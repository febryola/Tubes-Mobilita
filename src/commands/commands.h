#ifndef COMMAND_H
#define COMMAND_H

#include "../modules/adt.h"

/* buy.c */
void buy(POINT posNow, Matrix lokMat, ListGadget *l, int *money);

/* dropoff.c */
void dropOff(Stack *tas, LList *inprogress, POINT p, int *money, int *incTime, int* timeSpeed, boolean *canReturn, int *VIP, int* psnBerhasil);

/* help.c */
void help(boolean *canReturn);

/* inprogress.c */
void inProgress(LList pesanan);

/* inventory.c */
void inventory(ListGadget *l, int *time, int *incTime, int *saveTime, Stack *s, LList *inprogress, Gadget *gadgetUsed);

/* map.c */
void initMap (Matrix *peta);

void isiMap (Matrix *peta, int jumlah);

char posisiSkrg (POINT posNow, Matrix lokMat);

void printBerwarna (int pilihan, char bangunan);

int posisiToIdx(char bangunan);

boolean cekAdj (Matrix adjMat, char bangunan, char posisiSkrg);

boolean cekToDo (Matrix peta, char bangunan, LList toDo);

void Map (Matrix adjMat, Matrix lokMat, POINT posNow, LList toDo, Stack dropOff);

/* move.c */
void move(Matrix adjMat, POINT *posNow, int *time, ListDin lBuilding, int *timestep, int saveTime, int *timeSpeed);

/* pickup.c */
void pickUp(POINT posNow, Matrix LokMat, LList *todo, LList *inprogress, Stack *tas, int *incTime, int *timeSpeed, int VIP);

/* return.c */
void returnToSender(LList *inprogress, LList *todo, Stack *tas, boolean *canReturn);

/* todolist.c */
void todolist(LList toDo);

#endif
