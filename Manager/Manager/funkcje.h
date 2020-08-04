/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef FUNKCJE
#define FUNKCJE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struktury.h"

int pobierz_dane(int argc, char** argv, int* liczba_zespolow, char** nazwa_zespolu, char** wejsciowy, char** wyjsciowy);

int czytaj_nazwy(FILE** p_wejscie, char** p_nazwy, char* fraza, int liczba_nazw);

int czytaj_dane_z_pliku(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly, char* nazwa_zespolu);

void generuj_zespoly(struct zespol** ppHead, char** imiona, char** nazwiska, char** zespoly, int liczba_zespolow, char* nazwa_zespolu);

void wypisz_zespol(FILE** p_wejscie, struct zespol* pTemp);

void wypisz_tabele(FILE** p_wejscie, struct zespol* pHead);

#endif