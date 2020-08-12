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
@param argc liczba argumentów podanych w konsoli
@param argv tablica wskaŸników na argumenty w  konsoli
@param p_liczba_zespolow wskaŸnik na liczbê zespo³ów graj¹cych w lidze
@param p_nazwa_zespolu wskaŸnik na nazwê zespo³u gracza
@param p_wejsciowy wskaŸnik na nazwê œcie¿ki do pliku wejœciowego
@param p_wyjsciowy wskaŸnik na nazwê œcie¿ki do pliku wyjœciowego
@return funkcja zwraca 0, je¿eli pobieranie danych nie powiod³o sie prawid³owo, a 1 je¿eli wczytywanie danych powiod³o sie prawid³owo
*/
int pobierz_dane(int argc, char** argv, int* p_liczba_zespolow, char** p_nazwa_zespolu, char** p_wejsciowy, char** p_wyjsciowy);

/** Funkcja wczytuje dany rodzaj nazw z pliku wejœciowego do tablicy.
@param p_wejscie wskaŸnik na wskaŸnik do strumienia do pliku wejœciowego
@param p_nazwy wskaŸnik na tablicê wskaŸnikow na nazwy danego typu
@param fraza fraza kluczowa, po której wyst¹pieniu w pliku wejœciowym nastêpuje odczytywanie nazw danego typu
@param liczba_nazw liczba nazw danego typu, któr¹ trzeba wczytaæ
@return funkcja zwraca 0, je¿eli wczytywanie nie powiod³o sie prawid³owo, a 1 je¿eli wczytywanie powiod³o sie prawid³owo
@warning funkcja alokuje pamiêæ
*/
int czytaj_nazwy(FILE** p_wejscie, char** p_nazwy, char* fraza, int liczba_nazw);

/** Funkcja czyta wszystkie rodzaje danych z pliku wykorzystuj¹c funkcjê czytaj_nazwy.
@param p_wejscie wskaŸnik na wskaŸnik do strumienia do pliku wejœciowego
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
@param imiona wskaŸnik na tablicê z imionami
@param nazwiska wskaŸnik na tablicê z nazwiskami
@param p_zespoly wskaŸnik na wskaŸnik na tablicê z nazwami zespo³ów
@param nazwa_zespolu wskaŸnik na nazwê zespo³u gracza
@return funkcja zwraca 0, je¿eli wczytywanie nie powiod³o siê prawid³owo, a 1 je¿eli wczytywanie powiod³o siê prawid³owo
@warning funkcja alokuje pamiêæ
*/
int czytaj_dane_z_pliku(FILE** p_wejscie, int liczba_zespolow, char** imiona, char** nazwiska, char*** p_zespoly, char* nazwa_zespolu);

/** Funkcja generuje listê jednokierunkowa zespo³ów, s³u¿¹ca jako tabela.
@param ppHead wskaŸnik na wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param imiona wskaŸnik na tablicê z imionami
@param nazwiska wskaŸnik na tablicê z nazwiskami
@param zespoly wskaŸnik na tablicê z nazwami zespo³ów
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
@warning funkcja alokuje pamiêæ
*/
void generuj_zespoly(struct zespol** ppHead, char** imiona, char** nazwiska, char** zespoly, int liczba_zespolow);

/** Funkcja generuje listê cykliczn¹ u¿ywan¹ do generowania meczów w kolejkach.
@param pkpHead wskaŸnik na wskaŸnik na pocz¹tek listy cyklicznej u¿ywanej do generowania meczów w kolejkach
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
@warning funkcja alokuje pamiêæ
*/
void generuj_liste_do_kolejek(struct lk** pkpHead, struct zespol* pHead, int liczba_zespolow);

/** Funkcja sortuje tabelê zespo³ów wedlug kolejnoœci punktów i umiejêtnoœci zawodników z odpowiedni¹ wag¹.
@param pHead wskaznik na pocz¹tek listy jednokierunkowej zespo³ów
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
*/
void sortuj_tabele(struct zespol* pHead, int liczba_zespolow);

/** Funkcja symuluje mecz pomiêdzy dwoma dru¿ynami.
@param pT1 wskaŸnik na pierwszy z zespo³ów
@param pT2 wskaŸnik na drugi z zespo³ów
*/
void symuluj_mecz(struct zespol* pT1, struct zespol* pT2);

/** Funkcja umo¿liwia transfer zawodników lub trenerów pomiêdzy zespo³ami.
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param pMy wskaŸnik na zespó³ gracza w tabeli
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
*/
void umozliw_transfer(struct zespol* pHead, struct zespol* pMy, int liczba_zespolow);

/** Funkcja pozwala u¿ytkownikowi przeprowadzaæ zmiany w sk³adzie.
@param pMy wskaŸnik na zespó³ gracza w tabeli
*/
void wybierz_sklad(struct zespol* pMy);

/** Funkcja przeprowadza kolejkê ligi.
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param pkpHead wskaŸnik na wskaŸnik na pocz¹tek listy cyklicznej u¿ywanej do generowania meczów w kolejkach
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
@param nr_kolejki numer przeprowadzanej kolejki
@param nazwa_zespolu wskaŸnik na nazwê zespo³u gracza
@param imiona wskaŸnik na tablicê z imionami
@param nazwiska wskaŸnik na tablicê z nazwiskami
@warning funkcja mo¿e alokowaæ pamiêæ
*/
void przeprowadz_kolejke(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, int nr_kolejki, char* nazwa_zespolu, char** imiona, char** nazwiska);

/** Funkcja przeprowadza ca³y sezon ligi.
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param pkpHead wskaŸnik na wskaŸnik na pocz¹tek listy cyklicznej u¿ywanej do generowania meczów w kolejkach
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
@param nazwa_zespolu wskaŸnik na nazwê zespo³u gracza
@param imiona wskaŸnik na tablicê z imionami
@param nazwiska wskaŸnik na tablicê z nazwiskami
@warning funkcja mo¿e alokowaæ pamiêæ
*/
void przeprowadz_lige(struct zespol* pHead, struct lk** pkpHead, int liczba_zespolow, char* nazwa_zespolu, char** imiona, char** nazwiska);

/** Funkcja wypisuje zespó³ na zadane wyjœcie.
@param p_wejscie wskaŸnik na wskaŸnik do strumienia do wyjœcia
@param pTemp wskaŸnik na wypisywany zespó³ w tabeli
*/
void wypisz_zespol(FILE** p_wyjscie, struct zespol* pTemp);

/** Funkcja wypisuje tabelê ligi na standardowe wyjœcie.
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
*/
void wypisz_tabele(struct zespol* pHead);

/** Funkcja wpisuje ostateczne wyniki dru¿yny gracza do pliku.
@param p_wejscie wskaŸnik na wskaŸnik do strumienia do wyjœcia
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej zespo³ów
@param nazwa_zespolu wskaŸnik na nazwê zespo³u gracza
*/
void wpisz_wyniki_do_pliku(FILE** p_wejscie, struct zespol* pHead, char* nazwa_zespolu);

/** Funkcja zwalnia zaalokowan¹ wczeœniej w programie pamiêæ.
@param ppHead wskaŸnik na wskaŸnik na pocz¹tek listy cyklicznej u¿ywanej do generowania meczów w kolejkach
@param pkpHead wskaŸnik na wskaŸnik na pocz¹tek listy cyklicznej u¿ywanej do generowania meczów w kolejkach
@param imiona wskaŸnik na tablicê z imionami
@param nazwiska wskaŸnik na tablicê z nazwiskami
@param p_zespoly wskaŸnik na wskaŸnik na tablicê z nazwami zespo³ów
@param liczba_zespolow liczba zespo³ów graj¹cych w lidze
*/
void zwolnij_wszystko(struct zespol** ppHead, struct lk** pkpHead, char** imiona, char** nazwiska, char*** p_zespoly, int liczba_zespolow);

#endif