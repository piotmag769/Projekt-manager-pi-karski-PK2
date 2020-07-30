/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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

int czytaj_nazwy(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly, char* nazwa, int liczba_nazw)
{
	fseek(*p_wejscie, 0, SEEK_SET);
	int i = 0;
	char* fraza[10];
	for (i; i < 10; i++)
		fraza[i] = NULL;

	int k = fscanf(*p_wejscie, "%s", &fraza);
	while (strcmp(nazwa, fraza) != 0 && k != EOF)
		k = fscanf(*p_wejscie, "%s", &fraza);

	if (k == EOF)
	{
		printf("\nBrak frazy kluczowej \"%s\" w pliku wejsciowym\n", nazwa);
		return 0;
	}
	

	
	for (i = 0; i < liczba_nazw; i++)
	{

	}


	return 1;
}

int czytaj_dane_z_pliku(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly)
{
	if (!(*p_wejscie))
	{
		printf("\nPodano nieprawidlowa sciezke do pliku wejsciowego\n");
		return 0;
	}

	int poprawnosc = czytaj_nazwy(p_wejscie, liczba_zespolow, imiona, nazwiska, p_zespoly, "Imiona:", 22);

	if (poprawnosc == 0)
		return 0;
	
	poprawnosc = czytaj_nazwy(p_wejscie, liczba_zespolow, imiona, nazwiska, p_zespoly, "Nazwiska:", 22);

	if (poprawnosc == 0)
		return 0;

	poprawnosc = czytaj_nazwy(p_wejscie, liczba_zespolow, imiona, nazwiska, p_zespoly, "Zespoly:", liczba_zespolow);

	if (poprawnosc == 0)
		return 0;

	return 1;
}

