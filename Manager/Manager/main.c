/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	int liczba_zespolow = 12; //0
	char* nazwa_zespolu = "Atomowki"; //NULL
	char* wejsciowy = "Wejsciowy.txt"; //NULL
	char* wyjsciowy = "Wyjsciowy.txt"; //NULL
	int poprawnosc = pobierz_dane(argc, argv, &liczba_zespolow, &nazwa_zespolu, &wejsciowy, &wyjsciowy);
	if (poprawnosc == 0)
		return 0;
	char* imiona[22] = { NULL };
	char* nazwiska[22] = { NULL };
	char** zespoly = NULL;
	FILE* wejscie = fopen(wejsciowy, "r");
	poprawnosc = czytaj_dane_z_pliku(&wejscie, liczba_zespolow, imiona, nazwiska, &zespoly, nazwa_zespolu);
	if (poprawnosc == 0)
		return 0;
	struct zespol* pHead = NULL;
	generuj_zespoly(&pHead, imiona, nazwiska, zespoly, liczba_zespolow, nazwa_zespolu);
	FILE* pTemp = stdout;
	FILE** ppTemp = &pTemp;
	wypisz_tabele(ppTemp, pHead);
	return 0;
}