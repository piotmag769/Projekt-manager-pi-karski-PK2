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
	char napis[15];
	for (i = 0; i < 15; i++)
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
		for (j; j < 15; j++)
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

void generuj_zespoly(struct zespol** ppHead, char** imiona, char** nazwiska, char** zespoly, int liczba_zespolow)
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

void generuj_liste_do_kolejek(struct lk** pkpHead, struct zespol* pHead, int liczba_zespolow)
{
	*pkpHead = malloc(sizeof(struct lk));
	(*pkpHead)->nr_id = 1;
	struct lk* pTemp = *pkpHead;
	int i = 1;
	for (i; i < liczba_zespolow - 1; i++)
	{
		pTemp->pNext = malloc(sizeof(struct lk));
		pTemp = pTemp->pNext;
		pTemp->nr_id = i + 1;
	}
	pTemp->pNext = *pkpHead;
}

void generuj_juniorow(struct zespol* pHead, char** imiona, char** nazwiska)
{
	while (pHead)
	{
		pHead->juniors[pHead->liczba_juniorow].imie = imiona[rand() % 22];
		pHead->juniors[pHead->liczba_juniorow].nazwisko = nazwiska[rand() % 22];
		pHead->juniors[pHead->liczba_juniorow].klauzula_odstepnego = rand() % 1000000 + 100000;
		pHead->juniors[pHead->liczba_juniorow].tygodniowka= rand() % 100000 + 10000;
		pHead->juniors[pHead->liczba_juniorow].umiejetnosci = rand() % 99 + 1;
		pHead->juniors[pHead->liczba_juniorow].kontuzja = 0;
		pHead->liczba_juniorow++;
		pHead = pHead->pNext;
	}
}

void generuj_kontuzje(struct zespol* pHead, struct zespol* pMy)
{
	while (pHead)
	{
		int a = 0;

		for (a; a < pHead->liczba_juniorow; a++)
			pHead->juniors[a].kontuzja = 0;

		struct zawodnik* pT1 = NULL;
		a = rand() % 2;
		if (a == 1)
		{
			a = rand() % 5;
			pT1 = pHead->bench + a;
		}
		if (a == 0)
		{
			a = rand() % 11;
			pT1 = pHead->squad + a;
		}

		pT1->kontuzja = 1;

		if (pHead != pMy)
		{
			struct zawodnik* pT2 = pHead->juniors;
			for (a = 1; a < pHead->liczba_juniorow; a++)
				if (pT2->umiejetnosci < (pHead->juniors + a)->umiejetnosci)
					pT2 = pHead->juniors + a;
			struct zawodnik T;
			T = *pT1;
			*pT1 = *pT2;
			*pT2 = T;
		}

		pHead = pHead->pNext;
	}
}

void sortuj_tabele(struct zespol* pHead, int liczba_zespolow)
{
	struct zespol* pTemp;
	int k = 0;
	for (k; k < liczba_zespolow-1; k++)
	{
		pTemp = pHead;
		int j = 0;
		for (j; j < liczba_zespolow - 1 - k; j++)
		{
			if (pTemp->points < pTemp->pNext->points)
			{
				struct zespol T = *pTemp;
				struct zespol* T1 = pTemp->pNext;
				T.pNext = pTemp->pNext->pNext;
				*pTemp = *(pTemp->pNext);
				pTemp->pNext = T1;
				*T1 = T;
			}
			if (pTemp->points == pTemp->pNext->points)
			{
				int a1 = 0;
				int a2 = 0;
				int i = 0;
				for (i; i < 11; i++)
				{
					a1 += 3 * pTemp->squad[i].umiejetnosci;
					a2 += 3 * pTemp->pNext->squad[i].umiejetnosci;
				}
				for (i = 0; i < 5; i++)
				{
					a1 += pTemp->bench[i].umiejetnosci;
					a2 += pTemp->pNext->bench[i].umiejetnosci;
				}

				a1 += 15 * pTemp->trainer.umiejetnosci;
				a2 += 15 * pTemp->pNext->trainer.umiejetnosci;

				if (a1 < a2)
				{
					struct zespol T = *pTemp;
					struct zespol* T1 = pTemp->pNext;
					T.pNext = pTemp->pNext->pNext;
					*pTemp = *(pTemp->pNext);
					pTemp->pNext = T1;
					*T1 = T;
				}
			}
			pTemp = pTemp->pNext;
		}
	}
}

void symuluj_mecz(struct zespol* pT1, struct zespol* pT2)
{
	int a1 = 0;
	int a2 = 0;
	int i = 0;
	for (i; i < 11; i++)
	{
		a1 += 3*pT1->squad[i].umiejetnosci;
		a2 += 3*pT2->squad[i].umiejetnosci;
	}
	for (i = 0; i < 5; i++)
	{
		a1 += pT1->bench[i].umiejetnosci;
		a2 += pT2->bench[i].umiejetnosci;
	}

	a1 += 15*pT1->trainer.umiejetnosci;
	a2 += 15*pT2->trainer.umiejetnosci;
	if (a1 - a2 > -200 && a1 - a2 < 200)
	{
		a1 = rand() % 4;
		a2 = a1;
		pT1->points += 1;
		pT2->points += 1;
	}
	else if (a1 > a2)
	{
		a2 = rand() % 3;
		a1 = a2 + 1 + rand() % 3;
		pT1->points += 3;
	}
	else if (a1 < a2)
	{
		a1 = rand() % 3;
		a2 = a1 + 1 + rand() % 3;
		pT2->points += 3;
	}
	printf("\n%-15s %-1i - %1i %15s\n", pT1->nazwa_druzyny, a1, a2, pT2->nazwa_druzyny);
}

void umozliw_transfer(struct zespol* pHead, struct zespol* pMy, int liczba_zespolow)
{
	int a = 0;
	int k = 0;
	while (1)
	{
		printf("\nMozesz przeprowadzic jeden transfer przed kazda kolejka. Wpisz numer druzyny, ktorej zawodnika/trenera chcesz pozyskac (jesli nie chcesz przeprowadzac transferow wpisz 0): ");
		k = scanf("%i", &a);
		while (a<0 || a>liczba_zespolow || k == 0)
		{
			printf("\nWpisales nieprawidlowy numer. Wpisz numer druzyny, ktorej zawodnika/trenera chcesz pozyskac (jesli nie chcesz przeprowadzac transferow wpisz 0): ");
			if (k == 0)
				getchar();
			k = scanf("%i", &a);
		}
		if (a == 0)
			break;
		struct zespol* pTemp = pHead;
		int i = 1;
		for (i; i < a; i++)
			pTemp = pTemp->pNext;

		printf("\nWybierz, czy chcesz kupic zawodnika:\n-ze skladu podstawowego - wybierz 1\n-z rezerwy - wybierz 2\n-z juniorow - wybierz 3\n-trenera - wybierz 4\n-jesli nie chcesz wykonac transferow - wybierz 0\n");
		k = scanf("%i", &a);
		while (a<0 || a>3 || k == 0)
		{
			printf("\nWpisales nieprawidlowy numer. Wybierz, czy chcesz kupic zawodnika:\n-ze skladu podstawowego - wybierz 1\n-z rezerwy - wybierz 2\n-z juniorow - wybierz 3\n-trenera - wybierz 4\n-jesli nie chcesz wykonac transferow - wybierz 0\n");
			if (k == 0)
				getchar();
			k = scanf("%i", &a);
		}
		struct zawodnik* pT1 = NULL;
		if (a == 0)
			break;
		if (a == 4)
		{
			int b = pMy->budget + pMy->trainer.klauzula_odstepnego - pTemp->trainer.klauzula_odstepnego;
			int w = pMy->wages + pMy->trainer.tygodniowka - pTemp->trainer.tygodniowka;
			int c = pTemp->budget + pTemp->trainer.klauzula_odstepnego - pMy->trainer.klauzula_odstepnego;
			int y = pTemp->wages + pTemp->trainer.tygodniowka - pMy->trainer.tygodniowka;
			if (b < 0 || w < 0 || c < 0 || y < 0)
				printf("\nJednej z druzyn nie stac na dokonanie tego transferu. Nowy bilans wynosilby:\n-dla Twojej druzyny: budzet - %i, tygodniowki - %i\n-dla druzyny przeciwnej: budzet - %i, tygodniowki - %i\nMozesz nadal dokonac innego transferu\n", b, w, c, y);
			else
			{
				printf("\nMozesz dokonac tego transferu. Nowy bilans wynosilby:\n-dla Twojej druzyny: budzet - %i, tygodniowki - %i\n-dla druzyny przeciwnej: budzet - %i, tygodniowki - %i\nWybierz, czy chcesz przeprowadzic ten transfer - tak - 1, nie - 0: ", b, w, c, y);
				k = scanf("%i", &a);
				while (a < 0 || a > 1 || k == 0)
				{
					printf("\nPodano nieprawidlowy numer. Wybierz, czy chcesz przeprowadzic ten transfer - tak - 1, nie - 0: ");
					if (k == 0)
						getchar();
					k = scanf("%i", &a);
				}
				if (a == 0)
					printf("\nWybrano brak realizacji transferu. Mozesz nadal dokonac innego transferu\n");
				if (a == 1)
				{
					printf("\nZrealizowano transfer. Nowy wyglad tabeli:\n");
					struct trener T;
					T = pTemp->trainer;
					pTemp->trainer = pMy->trainer;
					pMy->trainer = T;
					pMy->budget = b;
					pTemp->budget = c;
					pMy->wages = w;
					pTemp->wages = y;
					wypisz_tabele(pHead);
					break;
				}
			}
		}
		else 
		{
			int j = 0;
			if (a == 1)
			{
				pT1 = pTemp->squad;
				j = 11;
			}
			if (a == 2)
			{
				pT1 = pTemp->bench;
				j = 5;
			}
			if (a == 3)
			{
				pT1 = pTemp->juniors;
				j = pTemp->liczba_juniorow;
			}

			printf("\nWybierz numer zawodnika, ktorego chcesz kupic (jesli nie chcesz przeprowadzac transferow, wybierz 0): ");
			k = scanf("%i", &a);
			while (a < 0 || a > j || k == 0)
			{
				printf("\nPodano nieprawidlowy numer. Wybierz numer zawodnika, ktorego chcesz kupic (jesli nie chcesz przeprowadzac transferow, wybierz 0): ");
				if (k == 0)
					getchar();
				k = scanf("%i", &a);
			}
			if (a == 0)
				break;
			
			pT1 += a - 1;

			if (pT1->kontuzja == 1)
				printf("\nNie mozesz kupic kontuzjowanego zawodnika. Mozesz nadal dokonac innego transferu\n");
			else 
			{
				printf("\nWybierz zawodnika, ktorego chcesz sprzedac:\n-ze skladu podstawowego - wybierz 1\n-z rezerwy - wybierz 2\n-z juniorow - wybierz 3\n-jesli nie chcesz wykonac transferow - wybierz 0\n");
				k = scanf("%i", &a);
				while (a < 0 || a > 4 || k == 0)
				{
					printf("\nPodano nieprawidlowy numer. Wybierz zawodnika, ktorego chcesz sprzedac:\n-ze skladu podstawowego - wybierz 1\n-z rezerwy - wybierz 2\n-z juniorow - wybierz 3\n-jesli nie chcesz wykonac transferow - wybierz 0\n");
					if (k == 0)
						getchar();
					k = scanf("%i", &a);
				}
				if (a == 0)
					break;
				struct zawodnik* pT2 = NULL;
				if (a == 1)
				{
					pT2 = pMy->squad;
					j = 11;
				}
				if (a == 2)
				{
					pT2 = pMy->bench;
					j = 5;
				}
				if (a == 3)
				{
					pT2 = pMy->juniors;
					j = pMy->liczba_juniorow;
				}

				printf("\nWybierz numer zawodnika, ktorego chcesz sprzedac (jesli nie chcesz przeprowadzac transferow, wybierz 0): ");
				k = scanf("%i", &a);
				while (a < 0 || a > j || k == 0)
				{
					printf("\nPodano nieprawidlowy numer. Wybierz numer zawodnika, ktorego chcesz sprzedac (jesli nie chcesz przeprowadzac transferow, wybierz 0): ");
					if (k == 0)
						getchar();
					k = scanf("%i", &a);
				}
				if (a == 0)
					break;

				pT2 += a - 1;

				if (pT2->kontuzja == 1)
					printf("\nNie mozesz sprzedac kontuzjowanego zawodnika. Mozesz nadal dokonac innego transferu\n");
				else
				{
					int b = pMy->budget + pT2->klauzula_odstepnego - pT1->klauzula_odstepnego;
					int w = pMy->wages + pT2->tygodniowka - pT1->tygodniowka;
					int c = pTemp->budget + pT1->klauzula_odstepnego - pT2->klauzula_odstepnego;
					int y = pTemp->wages + pT1->tygodniowka - pT2->tygodniowka;
					if (b < 0 || w < 0 || c < 0 || y < 0)
						printf("\nJednej z druzyn nie stac na dokonanie tego transferu. Nowy bilans wynosilby:\n-dla Twojej druzyny: budzet - %i, tygodniowki - %i\n-dla druzyny przeciwnej: budzet - %i, tygodniowki - %i\nMozesz nadal dokonac innego transferu\n", b, w, c, y);
					else
					{
						printf("\nMozesz dokonac tego transferu. Nowy bilans wynosilby:\n-dla Twojej druzyny: budzet - %i, tygodniowki - %i\n-dla druzyny przeciwnej: budzet - %i, tygodniowki - %i\nWybierz, czy chcesz przeprowadzic ten transfer - tak - 1, nie - 0: ", b, w, c, y);
						k = scanf("%i", &a);
						while (a < 0 || a > 1 || k == 0)
						{
							printf("\nPodano nieprawidlowy numer. Wybierz, czy chcesz przeprowadzic ten transfer - tak - 1, nie - 0: ");
							if (k == 0)
								getchar();
							k = scanf("%i", &a);
						}
						if (a == 0)
							printf("\nWybrano brak realizacji transferu. Mozesz nadal dokonac innego transferu\n");
						if (a == 1)
						{
							printf("\nZrealizowano transfer. Nowy wyglad tabeli:\n");
							struct zawodnik T;
							T = *pT2;
							*pT2 = *pT1;
							*pT1 = T;
							pMy->budget = b;
							pTemp->budget = c;
							pMy->wages = w;
							pTemp->wages = y;
							wypisz_tabele(pHead);
							break;
						}
					}
				}
			}
		}
	}
}

void wybierz_sklad(struct zespol* pMy)
{
	struct zawodnik* pT1 = NULL;
	int a = 0;
	for (a; a < 11; a++)
		if (pMy->squad[a].kontuzja==1)
		{
			pT1 = pMy->squad + a;
			break;
		}

	if (pT1 == NULL)
	{
		for (a = 0; a < 5; a++)
			if (pMy->bench[a].kontuzja == 1)
			{
				pT1 = pMy->bench + a;
				break;
			}
	}

	printf("\nW Twojej druzynie kontuzjowany jest %s %s. Wybierz numer zawodnika z juniorow, ktorym chcesz go zastapic: ", pT1->imie, pT1->nazwisko);
	int k = scanf("%i", &a);
	while (a<1 || a>pMy->liczba_juniorow || k == 0)
	{
		printf("\nPodano nieprawidlowy numer. Wybierz numer zawodnika z juniorow, ktorym chcesz astapic kontuzjowanego gracza: ");
		if (k == 0)
			getchar();
		k = scanf("%i", &a);
	}

	struct zawodnik* pT2 = pMy->juniors + a - 1;

	struct zawodnik T;
	T = *pT2;
	*pT2 = *pT1;
	*pT1 = T;

	printf("\Obecny sklad Twojej druzyny:\n");

	FILE* pTemp = stdout;
	FILE** ppTemp = &pTemp;
	wypisz_zespol(ppTemp, pMy);

	//while (1)
	{
		//niewymuszone zmiany w skladzie
	}
}

void przeprowadz_kolejke(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, int nr_kolejki, char* nazwa_zespolu, char** imiona, char** nazwiska)
{
	struct zespol* pMy = pHead; 
	while (strcmp(pMy->nazwa_druzyny, nazwa_zespolu) != 0)
		pMy = pMy->pNext;

	if (nr_kolejki == 1 || nr_kolejki == 5 || nr_kolejki == 9 || nr_kolejki == 13 || nr_kolejki == 17)
		generuj_juniorow(pHead, imiona, nazwiska);

	generuj_kontuzje(pHead, pMy);

	wypisz_tabele(pHead);

	umozliw_transfer(pHead, nazwa_zespolu, liczba_zespolow);

	wybierz_sklad(pMy);

	printf("\nWyniki meczow %i. kolejki:\n", nr_kolejki);

	int a1 = (*pkpHead)->nr_id;
	int a2 = liczba_zespolow;
	struct zespol* T1 = pHead;
	struct zespol* T2 = pHead;
	while (T1->nr_id != a1)
		T1 = T1->pNext;
	while (T2->nr_id != a2)
		T2 = T2->pNext;
	symuluj_mecz(T1, T2);
	struct lk* L1;
	struct lk* L2;
	int i = 1;
	for (i; i < liczba_zespolow / 2; i++)
	{
		L1 = *pkpHead;
		L2 = *pkpHead;
		T1 = pHead;
		T2 = pHead;
		int j = 0;
		for (j; j < i; j++)
			L1 = L1->pNext;
		for (j = 0; j < liczba_zespolow - 1 - i; j++)
			L2 = L2->pNext;
		while (T1->nr_id != L1->nr_id)
			T1 = T1->pNext;
		while (T2->nr_id != L2->nr_id)
			T2 = T2->pNext;
		symuluj_mecz(T1, T2);
	}
	(*pkpHead) = (*pkpHead)->pNext;
	sortuj_tabele(pHead, liczba_zespolow);
}

void przeprowadz_lige(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, char* nazwa_zespolu, char** imiona, char** nazwiska)
{
	int i = 0;
	for (i; i < 2 * liczba_zespolow - 2; i++)
		przeprowadz_kolejke(pHead, pkpHead, liczba_zespolow, i + 1, nazwa_zespolu, imiona, nazwiska);
	wypisz_tabele(pHead);
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
	fprintf(*p_wejscie, "\n");
}

void wypisz_tabele(struct zespol* pHead)
{
	int i = 1;
	while (pHead)
	{
		FILE* pTemp = stdout;
		FILE** ppTemp = &pTemp;
		printf("\n%i. ", i);
		wypisz_zespol(ppTemp, pHead);
		pHead = pHead->pNext;
		i++;
	}
}

void wpisz_wyniki_do_pliku()
{

}

void zwolnij_wszystko()
{

}
