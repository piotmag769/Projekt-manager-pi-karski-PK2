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

int czytaj_dane_z_pliku(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly, char* nazwa_zespolu)
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

	poprawnosc = czytaj_nazwy(p_wejscie, *p_zespoly, "Zespoly:", liczba_zespolow - 1);

	if (poprawnosc == 0)
	{
		int i = 0;
		for (i; i < 22; i++)
		{
			free(imiona[i]);
			free(nazwiska[i]);
		}

		for (i = 0; i < liczba_zespolow - 1; i++)
			free((*p_zespoly)[i]);

		free(*p_zespoly);

		return 0;
	}

	(*p_zespoly)[liczba_zespolow - 1] = nazwa_zespolu;

	return 1;
}

void generuj_zespoly(struct zespol** ppHead, char** imiona, char** nazwiska, char** zespoly, int liczba_zespolow, char* nazwa_zespolu)
{
	int i = 0;
	struct zespol* pTemp = NULL;
	for (i; i < liczba_zespolow; i++)
	{
		if (i == 0)
		{
			*ppHead = malloc(sizeof(struct zespol));
			pTemp = *ppHead;
		}
		else
		{
			pTemp->pNext = malloc(sizeof(struct zespol));
			pTemp = pTemp->pNext;
		}

		pTemp->wages = 100000;
		pTemp->budget = 10000000;
		pTemp->nr_id = i + 1;
		pTemp->points = 0;
		pTemp->nazwa_druzyny = zespoly[i];
		pTemp->liczba_juniorow = 0;

		int j = 0;
		for (j; j < 11; j++)
		{
			pTemp->squad[j].imie = imiona[rand() % 22];
			pTemp->squad[j].nazwisko = nazwiska[rand() % 22];
			pTemp->squad[j].kontuzja = 0;
			pTemp->squad[j].klauzula_odstepnego = rand() % 1000000 + 100000;
			pTemp->squad[j].tygodniowka = rand() % 100000 + 10000;
			pTemp->squad[j].umiejetnosci = rand() % 100 + 1;
		}
		for (j = 0; j < 5; j++)
		{
			pTemp->bench[j].imie = imiona[rand() % 22];
			pTemp->bench[j].nazwisko = nazwiska[rand() % 22];
			pTemp->bench[j].kontuzja = 0;
			pTemp->bench[j].klauzula_odstepnego = rand() % 1000000 + 100000;
			pTemp->bench[j].tygodniowka = rand() % 100000 + 10000;
			pTemp->bench[j].umiejetnosci = rand() % 100 + 1;
		}

		pTemp->trainer.imie = imiona[rand() % 22];
		pTemp->trainer.nazwisko = nazwiska[rand() % 22];
		pTemp->trainer.klauzula_odstepnego = rand() % 1000000 + 100000;
		pTemp->trainer.tygodniowka = rand() % 100000 + 10000;
		pTemp->trainer.umiejetnosci = rand() % 100 + 1;

		pTemp->pNext = NULL;
	}
}

void wypisz_zespol(FILE** p_wejscie, struct zespol* pTemp)
{
	int i = 0;
	fprintf(*p_wejscie, "%s\n\nNumer id: %i\n\nPunkty: %i\n\nBudzet: %i\n\nTygodniowki: %i\n\nSklad podstawowy:\n", pTemp->nazwa_druzyny, pTemp->nr_id, pTemp->points, pTemp->budget, pTemp->wages);
	
	for (i; i < 11; i++)
		fprintf(*p_wejscie, "\n%-15s %-15s %-3i %-7i %-6i %-1i", pTemp->squad[i].imie, pTemp->squad[i].nazwisko, pTemp->squad[i].umiejetnosci, pTemp->squad[i].klauzula_odstepnego, pTemp->squad[i].tygodniowka, pTemp->squad[i].kontuzja);
	fprintf(*p_wejscie, "\n\nLawka:\n");
	for (i = 0; i < 5; i++)
		fprintf(*p_wejscie, "\n%-15s %-15s %-3i %-7i %-6i %-1i", pTemp->bench[i].imie, pTemp->bench[i].nazwisko, pTemp->bench[i].umiejetnosci, pTemp->bench[i].klauzula_odstepnego, pTemp->bench[i].tygodniowka, pTemp->bench[i].kontuzja);
	fprintf(*p_wejscie, "\n\nJuniorzy:\n");
	for (i = 0; i < pTemp->liczba_juniorow; i++)
		fprintf(*p_wejscie, "\n%-15s %-15s %-3i %-7i %-6i %-1i", pTemp->juniors[i].imie, pTemp->juniors[i].nazwisko, pTemp->juniors[i].umiejetnosci, pTemp->juniors[i].klauzula_odstepnego, pTemp->juniors[i].tygodniowka, pTemp->juniors[i].kontuzja);
}

void wypisz_tabele(FILE** p_wejscie, struct zespol* pHead)
{
	int i = 1;
	while (pHead)
	{
		fprintf(*p_wejscie, "\n%i. ", i);
		wypisz_zespol(p_wejscie, pHead);
		pHead = pHead->pNext;
		i++;
	}
}
