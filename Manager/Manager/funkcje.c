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

int czytaj_nazwy(FILE** p_wejscie, char** p_nazwy, char* fraza, int liczba_nazw)
{
	fseek(*p_wejscie, 0, SEEK_SET);
	int i = 0;
	char napis[20];
	for (i = 0; i < 20; i++)
		napis[i] = NULL;

	int k = fscanf(*p_wejscie, "%s", napis);
	while (strcmp(fraza, napis) != 0 && k != EOF)
		k = fscanf(*p_wejscie, "%s", napis);

	if (k == EOF)
	{
		printf("\nBrak frazy kluczowej \"%s\" w pliku wejsciowym\n", fraza);
		return 0;
	}

	for (i = 0; i < liczba_nazw; i++)
	{
		int j = 0;
		for (j; j < 20; j++)
			napis[j] = NULL;

		k = fscanf(*p_wejscie, "%s", napis);
		if (k == EOF || strcmp(napis, "Imiona:") == 0 || strcmp(napis, "Nazwiska:") == 0 || strcmp(napis, "Zespoly:") == 0)
		{
			if (strcmp(fraza, "Imiona:") == 0)
				printf("\nBrak wystarczajacej ilosci imion w pliku wejsciowy (powinny byc %i)\n", liczba_nazw);
			else if (strcmp(fraza, "Nazwiska:") == 0)
				printf("\nBrak wystarczajacej ilosci nazwisk w pliku wejsciowy (powinny byc %i)\n", liczba_nazw);
			else
				printf("\nBrak wystarczajacej ilosci nazw zespolow w pliku wejsciowy (powinny byc %i)\n", liczba_nazw);
			return 0;
		}

		if (napis[0] < 65 || napis[0] > 90)
		{
			if (strcmp(fraza, "Imiona:") == 0)
				printf("\nPierwsza litera imienia musi byc wielka\n");
			else if (strcmp(fraza, "Nazwiska:") == 0)
				printf("\nPierwsza litera nazwiska musi byc wielka\n");
			else
				printf("\nPierwsza litera nazwy zespolu musi byc wielka\n");
			return 0;
		}

		for (j = 1; j < strlen(napis); j++)
			if (napis[j] < 97 || napis[j] > 122)
			{
				if (strcmp(fraza, "Imiona:") == 0)
					printf("\nWszystkie litery imienia poza pierwsza musza byc male\n");
				else if (strcmp(fraza, "Nazwiska:") == 0)
					printf("\nWszystkie litery nazwiska poza pierwsza musza byc male\n");
				else
					printf("\nWszystkie litery nazwy zespolu poza pierwsza musza byc male\n");
				return 0;
			}

		(p_nazwy)[i] = calloc(strlen(napis) + 1, sizeof(char));
		strcpy((p_nazwy)[i], napis);
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

	int poprawnosc = czytaj_nazwy(p_wejscie, imiona, "Imiona:", 22);

	if (poprawnosc == 0)
	{
		int i = 0;
		for (i; i < 22; i++)
			free(imiona[i]);

		return 0;
	}
	
	poprawnosc = czytaj_nazwy(p_wejscie, nazwiska, "Nazwiska:", 22);

	if (poprawnosc == 0)
	{
		int i = 0;
		for (i; i < 22; i++)
		{
			free(imiona[i]);
			free(nazwiska[i]);
		}

		return 0;
	}

	*p_zespoly = calloc(liczba_zespolow, sizeof(char*));

	poprawnosc = czytaj_nazwy(p_wejscie, *p_zespoly, "Zespoly:", liczba_zespolow);

	if (poprawnosc == 0)
	{
		int i = 0;
		for (i; i < 22; i++)
		{
			free(imiona[i]);
			free(nazwiska[i]);
		}

		for (i = 0; i < liczba_zespolow; i++)
			free((*p_zespoly)[i]);

		free(*p_zespoly);

		return 0;
	}

	return 1;
}

