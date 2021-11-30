#include <stdio.h>
#include <math.h>
#include "modules/adt.h"
#include "commands/commands.h"

void swap(Pesanan *xp, Pesanan *yp);

void sortPsn(Pesanan temp[],int length);

/* membaca file input dan mengisi  matrix peta, adjacency, dan queue pesanan */
void bacaFile (Word namafile, Matrix *peta, Matrix *adj, Queue *pesanan, ListDin *lBuilding);
