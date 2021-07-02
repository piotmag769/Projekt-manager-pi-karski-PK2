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
	int liczba_zespolow = 0;
	char* nazwa_zespolu = NULL;
	char* wejsciowy = NULL;
	char* wyjsciowy = NULL;
	int poprawnosc = pobierz_dane(argc, argv, &liczba_zespolow, &nazwa_zespolu, &wejsciowy, &wyjsciowy);
	if (poprawnosc == 0)
		return 0;
	char* imiona[22] = { NULL };
	char* nazwiska[22] = { NULL };
	char** zespoly = NULL;
	FILE* wejscie = fopen(wejsciowy, "r");
	poprawnosc = czytaj_dane_z_pliku(&wejscie, liczba_zespolow, imiona, nazwiska, &zespoly, nazwa_zespolu);
	fclose(wejscie);
	if (poprawnosc == 0)
		return 0;
	struct zespol* pHead = NULL;
	generuj_zespoly(&pHead, imiona, nazwiska, zespoly, liczba_zespolow);
	struct lk* kpHead = NULL;
	generuj_liste_do_kolejek(&kpHead, pHead, liczba_zespolow);
	przeprowadz_lige(pHead, &kpHead, liczba_zespolow, nazwa_zespolu, imiona, nazwiska);
	FILE* wyjscie = fopen(wyjsciowy, "w");
	wpisz_wyniki_do_pliku(&wyjscie, pHead, nazwa_zespolu);
	fclose(wyjscie);
	zwolnij_wszystko(&pHead, &kpHead, imiona, nazwiska, &zespoly, liczba_zespolow);
	return 0;
}