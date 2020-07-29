/** @file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury.h"
#include "funkcje.h"

int main(int argc, char** argv)
{
	int liczba_zespolow = 0;
	char* nazwa_zespolu = NULL;
	char* wejsciowy = NULL;
	char* wyjsciowy = NULL;
	int poprawnosc = pobierz_dane(argc, argv, &liczba_zespolow, &nazwa_zespolu, &wejsciowy, &wyjsciowy);
	if (poprawnosc == 0)
		return 0;

	return 0;
}