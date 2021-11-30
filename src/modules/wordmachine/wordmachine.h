/* File: wordmachine.h */
/* Definisi Word Engine */

#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include "../boolean.h"
#include "../charmachine/charmachine.h"

#define WM_CAPACITY 100
#define BLANK ' '
#define NEWLINE '\n'
#define CARRIAGE_RETURN '\r'

typedef struct {
   char contents[WM_CAPACITY]; /* container penyimpan kata, indeks yang dipakai [0..WM_CAPACITY-1] */
   int length;
} Word;

/* Word Engine State */
extern boolean endWord;
extern Word currentWord;

void ignoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang 
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void startWord();
/* I.S. : currentChar sembarang 
   F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void startWordFile(FILE* file);
/* I.S. : currentChar sembarang 
   F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void advWord();
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi 
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
   Proses : Akuisisi kata menggunakan procedure copyWord */

void copyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi; 
          currentChar = BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi WM_CAPACITY, maka sisa kata terpotong */

Word stringToWord (char arr[]);
/* Mengubah input string menjadi type Word*/

Word concatKata (char arr1[], char arr2[]);
/* Menggabungkan 2 string menjadi 1 Word */

boolean cekKataSama(char arr1[], char arr2[]);
/* Memeriksa apakah kedua string yang dimasukkan sama atau tidak*/

boolean isWordEqual(Word kata1, Word kata2);
/* Memeriksa apakah kedua word yang dimasukkan sama atau tidak*/

void printWord(Word kata);
/* I.S. : Sembarang 
   F.S. : kata tertulis di layar */

int charToInt (Word kata);

#endif

