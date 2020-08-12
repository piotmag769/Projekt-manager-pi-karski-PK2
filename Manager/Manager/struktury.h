/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STRUKTURY
#define STRUKTURY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Element cyklicznej listy jednokierunkowej u�ywanej do generowania mecz�w w kolejkach. */
struct lk
{
	int nr_id;			///<numer identyfikacyjny zespo�u (to�samy z numerem w strukturze zesp�l)
	struct lk* pNext;	///<wska�nik na nastepny element listy cyklicznej
};

/** Struktura reprezentuj�ca zawodnika gr�jacego w klubie. */
struct zawodnik
{
	char* imie;					///<imi� zawodnika	
	char* nazwisko;				///<nazwisko zawodnika
	int umiejetnosci;			///<umiej�tno�ci zawodnika
	int kontuzja;				///<warto�� okreslaj�ca, czy zawodnik jest kontuzjowany: 0 - nie, 1 - tak
	int klauzula_odstepnego;	///<kwota, za kt�r� mo�na kupi� zawodnika
	int tygodniowka;			///<tygodniowe wynagrodzenie zawodnika
};

/** Struktura reprezentuj�ca trenera klubu. */
struct trener
{
	char* imie;					///<imi� trenera
	char* nazwisko;				///<nazwisko trenera
	int umiejetnosci;			///<umiej�tno�ci trenera
	int klauzula_odstepnego;	///<kwota, za kt�r� mo�na kupi� trenera
	int tygodniowka;			///<tygodniowe wynagrodzenie trenera
};

/** Element listy jednokierunkowej reprezentuj�cej tabel� zespo��w. */
struct zespol
{
	char* nazwa_druzyny;		///<nazwa dru�yny
	int nr_id;					///<numer identyfikacyjny dru�yny (to�samy z numerem w strukturze lk)
	int points;					///<liczba punkt�w dru�yny
	int budget;					///<bud�et dru�yny na transfery
	int wages;					///<bud�et dru�yny na tygodni�wki
	int liczba_juniorow;		///<liczba junior�w znajduj�cych si� obecnie w dru�ynie
	struct zawodnik squad[11];	///<tablica zawieraj�ca zawodnik�w sk�adu podstawowego
	struct zawodnik bench[5];	///<tablica zawieraj�ca zawodnik�w rezerwowych
	struct zawodnik juniors[5];	///<tablica zawieraj�ca junior�w
	struct trener trainer;		///<trener dru�yny
	struct zespol* pNext;		///<wska�nik na nast�pn� dru�yn� w tabeli
};

#endif