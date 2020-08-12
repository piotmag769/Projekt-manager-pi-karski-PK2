/** @file */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STRUKTURY
#define STRUKTURY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Element cyklicznej listy jednokierunkowej u¿ywanej do generowania meczów w kolejkach. */
struct lk
{
	int nr_id;			///<numer identyfikacyjny zespo³u (to¿samy z numerem w strukturze zespól)
	struct lk* pNext;	///<wskaŸnik na nastepny element listy cyklicznej
};

/** Struktura reprezentuj¹ca zawodnika gr¹jacego w klubie. */
struct zawodnik
{
	char* imie;					///<imiê zawodnika	
	char* nazwisko;				///<nazwisko zawodnika
	int umiejetnosci;			///<umiejêtnoœci zawodnika
	int kontuzja;				///<wartoœæ okreslaj¹ca, czy zawodnik jest kontuzjowany: 0 - nie, 1 - tak
	int klauzula_odstepnego;	///<kwota, za któr¹ mo¿na kupiæ zawodnika
	int tygodniowka;			///<tygodniowe wynagrodzenie zawodnika
};

/** Struktura reprezentuj¹ca trenera klubu. */
struct trener
{
	char* imie;					///<imiê trenera
	char* nazwisko;				///<nazwisko trenera
	int umiejetnosci;			///<umiejêtnoœci trenera
	int klauzula_odstepnego;	///<kwota, za któr¹ mo¿na kupiæ trenera
	int tygodniowka;			///<tygodniowe wynagrodzenie trenera
};

/** Element listy jednokierunkowej reprezentuj¹cej tabelê zespo³ów. */
struct zespol
{
	char* nazwa_druzyny;		///<nazwa dru¿yny
	int nr_id;					///<numer identyfikacyjny dru¿yny (to¿samy z numerem w strukturze lk)
	int points;					///<liczba punktów dru¿yny
	int budget;					///<bud¿et dru¿yny na transfery
	int wages;					///<bud¿et dru¿yny na tygodniówki
	int liczba_juniorow;		///<liczba juniorów znajduj¹cych siê obecnie w dru¿ynie
	struct zawodnik squad[11];	///<tablica zawieraj¹ca zawodników sk³adu podstawowego
	struct zawodnik bench[5];	///<tablica zawieraj¹ca zawodników rezerwowych
	struct zawodnik juniors[5];	///<tablica zawieraj¹ca juniorów
	struct trener trainer;		///<trener dru¿yny
	struct zespol* pNext;		///<wskaŸnik na nastêpn¹ dru¿ynê w tabeli
};

#endif