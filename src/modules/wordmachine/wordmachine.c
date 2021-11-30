#include <stdio.h>

#include "wordmachine.h"
#include "../charmachine/charmachine.h"

boolean endWord;
Word currentWord;

void ignoreBlank(){
	int i = 0;
    while ((currentChar == BLANK) || (currentChar == NEWLINE) || (currentChar == CARRIAGE_RETURN)){
        adv();
		i++;
		// avoid infinite loop
		if (i > 1000){
			break;
		}
    }
}

void startWord(){
	start();
	ignoreBlank();
	if (currentChar == MARK_LF || currentChar == MARK_CR){
		endWord = true;
	} else {
		endWord = false;
		copyWord();
	}
}

void startWordFile(FILE* file){
    startfile(file);
    ignoreBlank();
    if (currentChar == MARK_LF || currentChar == MARK_CR){
        endWord = true;
    } else {
        endWord = false;
        copyWord();
    }
}

void advWord(){
    ignoreBlank();
    if (currentChar == MARK_LF || currentChar == MARK_CR){
        endWord = true;
    } else {
        copyWord();
        ignoreBlank();
    }
}

void copyWord(){
    int i = 0;
    while ((currentChar != BLANK) && (currentChar != NEWLINE) && (currentChar != MARK_LF) && (currentChar != MARK_CR) && (i < WM_CAPACITY)){
        currentWord.contents[i] = currentChar;
        adv();
        i++;
    }
    currentWord.length = i;
}

Word stringToWord (char arr[]){
/* Mengubah input string menjadi type Word*/
	int i = 0;
	Word kata;
	while (arr[i] != '\0'){
		kata.contents[i] = arr[i];
		i++;
	}
	kata.contents[i] = '\0';
	kata.length = i;
	return kata;
}

Word concatKata (char arr1[], char arr2[]){
/* Menggabungkan 2 string menjadi 1 Word */
	int i,j = 0;
	Word kata1,kata2,kata3;
	kata1 = stringToWord(arr1);
	kata2 = stringToWord(arr2);
	i = 0;
	while (i<kata1.length){
		kata3.contents[j] = kata1.contents[i];
		i++;
		j++;
	}
	kata3.length = kata1.length;
	i = 0;
	while (i<kata2.length){
		kata3.contents[j] = kata2.contents[i];
		i++;
		j++;
	}
	kata3.contents[j] = '\0';
	kata3.length += kata2.length;
	return kata3;
}

boolean isWordEqual(Word kata1, Word kata2) {
	boolean sama = true;
	int i = 0;

	if (kata1.length == kata2.length){
		while ((sama) && (i<kata1.length)){
			if (kata1.contents[i] != kata2.contents[i]){
				sama = false;
			}
			i++;
		}
	}
	else{
		sama = false;
	}
	return sama;
}

boolean cekKataSama(char arr1[], char arr2[]){
/* Memeriksa apakah kedua string yang dimasukkan sama atau tidak*/
	int i = 0;
	Word kata1,kata2;
	
	kata1 = stringToWord(arr1);
	kata2 = stringToWord(arr2);
	return isWordEqual(kata1, kata2);
}


void printWord(Word kata)
{
    for (int i = 0; i < kata.length; i++)
    {
        printf("%c", kata.contents[i]);
    }   
}

int charToInt (Word kata){
    int total = 0,x;
    for (int i=0;i<kata.length;i++){
        x = kata.contents[i] - '0';
        total = total*10 + x;
    }
    return total;
}
