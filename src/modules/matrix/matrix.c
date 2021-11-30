/* ********** Definisi TYPE Matrix dengan Index dan elemen integer ********** */

#ifndef Matrix_H
#define Matrix_H

#include <stdio.h>
#include <math.h>
#include "../boolean.h"
#include "../point/point.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define ROW_CAP 100
#define COL_CAP 100

typedef int Index; /* Index baris, kolom */
typedef char MatElType;
typedef struct
{
   MatElType contents[ROW_CAP][COL_CAP];
   int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
   int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
void CreateMatrix(int nRow, int nCol, Matrix *m){
	(*m).rowEff = nRow;
	(*m).colEff = nCol;
}

/* *** Selektor *** */
#define ROWS(M) (M).rowEff
#define COLS(M) (M).colEff
#define MAT_ELMT(M, i, j) (M).contents[(i)][(j)]

/* *** Selektor "DUNIA Matrix" *** */
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
boolean isIdxValidMat(int i, int j){
	return (i >= 0) && (i < ROW_CAP) && (j >= 0) && (j < COL_CAP);
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
/* Mengirimkan Index baris terbesar m */
Index getLastIdxRow(Matrix m){
	return ROWS(m)-1;
}
/* Mengirimkan Index kolom terbesar m */
Index getLastIdxCol(Matrix m){
	return COLS(m)-1;
}
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
boolean isIdxEffMat(Matrix m, Index i, Index j){
	return (i >= 0) && (i < ROWS(m)) && (j >= 0) && (j < COLS(m));
}
/* Mengirimkan elemen m(i,i) */
MatElType getElmtDiagonal(Matrix m, Index i){
	return MAT_ELMT(m,i,i);
}

/* ********** Assignment  Matrix ********** */
/* Melakukan assignment MRes = MIn */
void copyMatrix(Matrix mIn, Matrix *mRes){
	CreateMatrix(ROWS(mIn), COLS(mIn), mRes);
	int i, j;
	for (i = 0; i < ROWS(mIn); i++){
		for(j = 0; j < COLS(mIn); j++){
			MAT_ELMT(*mRes, i, j) = MAT_ELMT(mIn, i, j);
		}
	}
}

/* ********** KELOMPOK BACA/TULIS ********** */
/* I.S. isIdxValidMat(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
void readMatrix(Matrix *m, int nRow, int nCol){
	CreateMatrix(nRow, nCol, m);
	int i, j;
	for(i = 0; i < ROWS(*m); i++){
		for(j = 0; j < COLS(*m); j++){
			scanf(" %c", &MAT_ELMT(*m, i, j));
		}
	}
}
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
void displayMatrix(Matrix m){
	int i, j;
	for(i = 0; i < ROWS(m); i++){
		for(j = 0; j < COLS(m); j++){
			printf("%c", MAT_ELMT(m, i, j));
			if (j < COLS(m) -1){
				printf(" ");
			}
		}
		if (i < ROWS(m)-1){
			printf("\n");
		}
	}
}

void setElmtMat (Matrix *m, char val, int row, int col){
   MAT_ELMT(*m,row,col) = val;
}
/*Memasukkan elemen ke dalam sebuah matriks pada indeks tertentu*/

POINT elmtToPoint(Matrix m, MatElType bangunan){
	POINT p;
	int row,col;
	for (int i=0;i<ROWS(m);i++){
		for (int j=0;j<COLS(m);j++){
			if (MAT_ELMT(m,i,j) == bangunan){
				row = i;
				col = j;
				break;
			}
		}
	}
	p = MakePOINT(row,col);
	Name(p) = bangunan;
	return p;
}
/* convert dari bangunan menjadi koordinat(type Point) */

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrix addMatrix(Matrix m1, Matrix m2){
	Matrix m;
	CreateMatrix(ROWS(m1), COLS(m1), &m);
	int i, j;
	for(i = 0; i < ROWS(m); i++){
		for(j = 0; j < COLS(m); j++){
			MAT_ELMT(m, i, j) = MAT_ELMT(m1, i, j) + MAT_ELMT(m2, i, j);
		}
	}
	return m;
}
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
Matrix subtractMatrix(Matrix m1, Matrix m2){
	Matrix m;
	CreateMatrix(ROWS(m1), COLS(m1), &m);
	int i, j;
	for(i = 0; i < ROWS(m); i++){
		for(j = 0; j < COLS(m); j++){
			MAT_ELMT(m, i, j) = MAT_ELMT(m1, i, j) - MAT_ELMT(m2, i, j);
		}
	}
	return m;
}
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
Matrix multiplyMatrix(Matrix m1, Matrix m2){
	Matrix m;
	CreateMatrix(ROWS(m1), COLS(m2), &m);
	int i, j, k;
	for(i = 0; i < ROWS(m1); i++){
		for(j = 0; j < COLS(m2); j++){
			MAT_ELMT(m, i, j) = 0;
			for(k = 0; k < COLS(m1); k++){
				MAT_ELMT(m, i, j) += (MAT_ELMT(m1, i, k) * MAT_ELMT(m2, k, j));
			}
		}
	}
	return m;
}
/* Mengirim hasil perkalian setiap elemen m dengan x */
Matrix multiplyConst(Matrix m, MatElType x){
	Matrix mk;
	CreateMatrix(ROWS(m), COLS(m), &mk);
	int i, j;
	for(i = 0; i < ROWS(m); i++){
		for(j = 0; j < COLS(m); j++){
			MAT_ELMT(mk, i, j) = MAT_ELMT(m, i, j) * x;
		}
	}
	return mk;
}
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
void pMultiplyConst(Matrix *m, MatElType k){
	int i, j;
	for(i = 0; i < ROWS(*m); i++){
		for(j = 0; j < COLS(*m); j++){
			MAT_ELMT(*m, i, j) *= k;
		}
	}
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isEqual(Matrix m1, Matrix m2){
	boolean check;
	check = ((ROWS(m1) * COLS(m1)) == (ROWS(m2) * COLS(m2)))
	&& (ROWS(m1) == ROWS(m2))
	&& (COLS(m1) == COLS(m2))
	&& (getLastIdxCol(m1) == getLastIdxCol(m2))
	&& (getLastIdxRow(m1) == getLastIdxRow(m2));
	int i = 0, j = 0;
	for(i = 0; i < ROWS(m1); i++){
		for(j = 0; j < COLS(m1); j++){
			if (MAT_ELMT(m1, i, j) != MAT_ELMT(m2, i, j)) check = false;
		}
	}
	return check;
}
/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isNotEqual(Matrix m1, Matrix m2){
	return !isEqual(m1, m2);
}
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
boolean isSizeEqual(Matrix m1, Matrix m2){
	return (ROWS(m1) * COLS(m1)) == (ROWS(m2) * COLS(m2));
}

/* ********** Operasi lain ********** */
/* Mengirimkan banyaknya elemen m */
int count(Matrix m){
	return ROWS(m) * COLS(m);
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSquare(Matrix m){
	return ROWS(m) == COLS(m);
}
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m)
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
boolean isSymmetric(Matrix m){
	boolean check = isSquare(m);
	int i = 0, j = 0;
	while(check && i < ROWS(m)){
		while(check && j < i){
			check = MAT_ELMT(m, i, j) == MAT_ELMT(m, j, i);
			if (check) j++;
		}
		if (check) i++;
	}
	return check;
}
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
boolean isIdentity(Matrix m){
	boolean check = isSquare(m);
	int i = 0, j = 0;
	while(check && i < ROWS(m)){
		while(check && j < COLS(m)){
			if (i == j){
				check = MAT_ELMT(m, i, j) == 1;
			} else {
				check = MAT_ELMT(m, i, j) == 0;
			}
			j++;
		}
		i++;
	}
	return check;
}
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
boolean isSparse(Matrix m){
	int i, j, counter;
	for(i = 0; i < ROWS(m); i++){
		for(j = 0; j < COLS(m); j++){
			if (MAT_ELMT(m, i, j) != 0){
				counter++;
			}
		}
	}
	return counter <= 0.05 * count(m);
}
/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
Matrix inverse1(Matrix m){
	return multiplyConst(m, -1);
}
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void pInverse1(Matrix *m){
	pMultiplyConst(m, -1);
}
// mengembalikan matriks minor
Matrix minor(Matrix m, int r, int c){ // fungsi antara saja
	Matrix mc;
	CreateMatrix(ROWS(m)-1, COLS(m)-1, &mc);
	int i, j, ic = 0, jc = 0;
	for(i = 0; i < ROWS(m); i++){ // loop baris m
		if (i != r){ // biar hemat beberapa putaran sj
			for(j = 0; j < COLS(m); j++){ // loop kolom m
				if (j != c){ //
					MAT_ELMT(mc, ic, jc) = MAT_ELMT(m, i, j);
					if (jc == COLS(mc)-1){ // increment indeks ngisi mc
						jc = 0;
						ic++;
					} else{
						jc++;
					}
				}
			}
		}
	}
	return mc;
}

/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void transpose(Matrix *m){
	Matrix temp;
	CreateMatrix(COLS(*m), ROWS(*m), &temp);
	int i, j;
	for(i = 0; i < ROWS(temp); i++){
		for(j = 0; j < COLS(temp); j++){
			MAT_ELMT(temp, i, j) = MAT_ELMT(*m, j, i);
		}
	}
	copyMatrix(temp, m);
}

#endif
