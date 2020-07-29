/** @file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury.h"
#include "funkcje.h"

int pobierz_dane(int argc, char** argv, int* liczba_zespolow, char** nazwa_zespolu, char** wejsciowy, char** wyjsciowy)
{
	int i = 0;
	for (i; i < argc; i++)
	{
		if (strcmp(argv[i], "-we") == 0)
			*wejsciowy = argv[i + 1];
		if (strcmp(argv[i], "-wy") == 0)
			*wyjsciowy = argv[i + 1];
		if (strcmp(argv[i], "-l") == 0)
			*liczba_zespolow = atoi(argv[i + 1]);
		if (strcmp(argv[i], "-z") == 0)
			*nazwa_zespolu = argv[i + 1];
	}

	if (*liczba_zespolow < 10 || *liczba_zespolow>20 || (*liczba_zespolow) % 2 != 0)
	{
		printf("\nLiczba zespolow musi byc liczba pomiedzy 10 i 20 oraz byc parzysta\n");
		return 0;
	}

	if (*nazwa_zespolu == NULL)
	{
		printf("\nNie podano nazwy zespolu\n");
		return 0;
	}

	if (*wejsciowy == NULL)
	{
		printf("\nNie podano nazwy pilku wejsciowego\n");
		return 0;
	}

	if (*wyjsciowy == NULL)
	{
		printf("\nNie podano nazwy pilku wyjsciowego\n");
		return 0;
	}

	return 1;
}




