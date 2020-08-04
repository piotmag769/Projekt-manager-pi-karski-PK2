/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STRUKTURY
#define STRUKTURY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lk
{
	int nr_id;
	struct lk* pNext;
};

struct zawodnik
{
	char* imie;
	char* nazwisko;
	int umiejetnosci;
	int kontuzja;
	int klauzula_odstepnego;
	int tygodniowka;
};

struct trener
{
	char* imie;
	char* nazwisko;
	int umiejetnosci;
	int klauzula_odstepnego;
	int tygodniowka;
};

struct zespol
{
	char* nazwa_druzyny;
	int nr_id;
	int points;
	int budget;
	int wages;
	int liczba_juniorow;
	struct zawodnik squad[11];
	struct zawodnik bench[5];
	struct zawodnik juniors[5];
	struct trener trainer;
	struct zespol* pNext;
};

#endif