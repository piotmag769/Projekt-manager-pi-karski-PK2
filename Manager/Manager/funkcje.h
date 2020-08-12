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

/** Funkcja pobiera dane z konsoli i wczytuje je do zmiennych.
@param argc liczba argument�w podanych w konsoli
@param argv tablica wska�nik�w na argumenty w  konsoli
@param p_liczba_zespolow wska�nik na liczb� zespo��w graj�cych w lidze
@param p_nazwa_zespolu wska�nik na nazw� zespo�u gracza
@param p_wejsciowy wska�nik na nazw� �cie�ki do pliku wej�ciowego
@param p_wyjsciowy wska�nik na nazw� �cie�ki do pliku wyj�ciowego
@return funkcja zwraca 0, je�eli pobieranie danych nie powiod�o sie prawid�owo, a 1 je�eli wczytywanie danych powiod�o sie prawid�owo
*/
int pobierz_dane(int argc, char** argv, int* p_liczba_zespolow, char** p_nazwa_zespolu, char** p_wejsciowy, char** p_wyjsciowy);

/** Funkcja wczytuje dany rodzaj nazw z pliku wej�ciowego do tablicy.
@param p_wejscie wska�nik na wska�nik do strumienia do pliku wej�ciowego
@param p_nazwy wska�nik na tablic� wska�nikow na nazwy danego typu
@param fraza fraza kluczowa, po kt�rej wyst�pieniu w pliku wej�ciowym nast�puje odczytywanie nazw danego typu
@param liczba_nazw liczba nazw danego typu, kt�r� trzeba wczyta�
@return funkcja zwraca 0, je�eli wczytywanie nie powiod�o sie prawid�owo, a 1 je�eli wczytywanie powiod�o sie prawid�owo
@warning funkcja alokuje pami��
*/
int czytaj_nazwy(FILE** p_wejscie, char** p_nazwy, char* fraza, int liczba_nazw);

/** Funkcja czyta wszystkie rodzaje danych z pliku wykorzystuj�c funkcj� czytaj_nazwy.
@param p_wejscie wska�nik na wska�nik do strumienia do pliku wej�ciowego
@param liczba_zespolow liczba zespo��w graj�cych w lidze
@param imiona wska�nik na tablic� z imionami
@param nazwiska wska�nik na tablic� z nazwiskami
@param p_zespoly wska�nik na wska�nik na tablic� z nazwami zespo��w
@param nazwa_zespolu wska�nik na nazw� zespo�u gracza
@return funkcja zwraca 0, je�eli wczytywanie nie powiod�o si� prawid�owo, a 1 je�eli wczytywanie powiod�o si� prawid�owo
@warning funkcja alokuje pami��
*/
int czytaj_dane_z_pliku(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly, char* nazwa_zespolu);

/** Funkcja generuje list� jednokierunkowa zespo��w, s�u��ca jako tabela.
@param ppHead wska�nik na wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param imiona wska�nik na tablic� z imionami
@param nazwiska wska�nik na tablic� z nazwiskami
@param zespoly wska�nik na tablic� z nazwami zespo��w
@param liczba_zespolow liczba zespo��w graj�cych w lidze
@warning funkcja alokuje pami��
*/
void generuj_zespoly(struct zespol** ppHead, char** imiona, char** nazwiska, char** zespoly, int liczba_zespolow);

/** Funkcja generuje list� cykliczn� u�ywan� do generowania mecz�w w kolejkach.
@param pkpHead wska�nik na wska�nik na pocz�tek listy cyklicznej u�ywanej do generowania mecz�w w kolejkach
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param liczba_zespolow liczba zespo��w graj�cych w lidze
@warning funkcja alokuje pami��
*/
void generuj_liste_do_kolejek(struct lk** pkpHead, struct zespol* pHead, int liczba_zespolow);

/** Funkcja sortuje tabel� zespo��w wedlug kolejno�ci punkt�w i umiej�tno�ci zawodnik�w z odpowiedni� wag�.
@param pHead wskaznik na pocz�tek listy jednokierunkowej zespo��w
@param liczba_zespolow liczba zespo��w graj�cych w lidze
*/
void sortuj_tabele(struct zespol* pHead, int liczba_zespolow);

/** Funkcja symuluje mecz pomi�dzy dwoma dru�ynami.
@param pT1 wska�nik na pierwszy z zespo��w
@param pT2 wska�nik na drugi z zespo��w
*/
void symuluj_mecz(struct zespol* pT1, struct zespol* pT2);

/** Funkcja umo�liwia transfer zawodnik�w lub trener�w pomi�dzy zespo�ami.
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param pMy wska�nik na zesp� gracza w tabeli
@param liczba_zespolow liczba zespo��w graj�cych w lidze
*/
void umozliw_transfer(struct zespol* pHead, struct zespol* pMy, int liczba_zespolow);

/** Funkcja pozwala u�ytkownikowi przeprowadza� zmiany w sk�adzie.
@param pMy wska�nik na zesp� gracza w tabeli
*/
void wybierz_sklad(struct zespol* pMy);

/** Funkcja przeprowadza kolejk� ligi.
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param pkpHead wska�nik na wska�nik na pocz�tek listy cyklicznej u�ywanej do generowania mecz�w w kolejkach
@param liczba_zespolow liczba zespo��w graj�cych w lidze
@param nr_kolejki numer przeprowadzanej kolejki
@param nazwa_zespolu wska�nik na nazw� zespo�u gracza
@param imiona wska�nik na tablic� z imionami
@param nazwiska wska�nik na tablic� z nazwiskami
@warning funkcja mo�e alokowa� pami��
*/
void przeprowadz_kolejke(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, int nr_kolejki, char* nazwa_zespolu, char** imiona, char** nazwiska);

/** Funkcja przeprowadza ca�y sezon ligi.
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param pkpHead wska�nik na wska�nik na pocz�tek listy cyklicznej u�ywanej do generowania mecz�w w kolejkach
@param liczba_zespolow liczba zespo��w graj�cych w lidze
@param nazwa_zespolu wska�nik na nazw� zespo�u gracza
@param imiona wska�nik na tablic� z imionami
@param nazwiska wska�nik na tablic� z nazwiskami
@warning funkcja mo�e alokowa� pami��
*/
void przeprowadz_lige(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, char* nazwa_zespolu, char** imiona, char** nazwiska);

/** Funkcja wypisuje zesp� na zadane wyj�cie.
@param p_wejscie wska�nik na wska�nik do strumienia do wyj�cia
@param pTemp wska�nik na wypisywany zesp� w tabeli
*/
void wypisz_zespol(FILE** p_wyjscie, struct zespol* pTemp);

/** Funkcja wypisuje tabel� ligi na standardowe wyj�cie.
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
*/
void wypisz_tabele(struct zespol* pHead);

/** Funkcja wpisuje ostateczne wyniki dru�yny gracza do pliku.
@param p_wejscie wska�nik na wska�nik do strumienia do wyj�cia
@param pHead wska�nik na pocz�tek listy jednokierunkowej zespo��w
@param nazwa_zespolu wska�nik na nazw� zespo�u gracza
*/
void wpisz_wyniki_do_pliku(FILE** p_wejscie, struct zespol* pHead, char* nazwa_zespolu);

/** Funkcja zwalnia zaalokowan� wcze�niej w programie pami��.
@param ppHead wska�nik na wska�nik na pocz�tek listy cyklicznej u�ywanej do generowania mecz�w w kolejkach
@param pkpHead wska�nik na wska�nik na pocz�tek listy cyklicznej u�ywanej do generowania mecz�w w kolejkach
@param imiona wska�nik na tablic� z imionami
@param nazwiska wska�nik na tablic� z nazwiskami
@param p_zespoly wska�nik na wska�nik na tablic� z nazwami zespo��w
@param liczba_zespolow liczba zespo��w graj�cych w lidze
*/
void zwolnij_wszystko(struct zespol** ppHead, struct lk** pkpHead, char** imiona, char** nazwiska, char*** p_zespoly, int liczba_zespolow);

#endif