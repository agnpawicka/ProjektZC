/**@author Agnieszka Pawicka*/
/**@file zmianyNotacjiIObrazow.h
 Plik zawierający deklaracje funkcji pomocniczych takich jak zmiany w metodzie definiowania pola oraz zmiany wyświetlanych obrazów.
 */
#ifndef PROJEKTZC_ZMIANYNOTACJI_H
#define PROJEKTZC_ZMIANYNOTACJI_H


/**@headerfile types.h*/
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

/**@var obrazki - tablica nazw tekstur*/
char *obrazki[5];
cairo_surface_t *obraz[5];

/**@fn zainicjalizujObrazki
* Funkcja znajdująca  tekstury.s*/
void zainicjalizujObrazki();

/**@fn numerNaWspolrzedne
 * Funkcja na podstawie unikalnego numeru pola wylicza jego współrzędne na planszy
 * @param nr - numer pola
 * @return - współrzędne pola
 */
WSP numerNaWspolrzedne(int nr);
/**@fn wspolrzedneNaNumer
 * Funkcja na podstawie współrzędnch pola na planszy wylicza jego unikalny numer
 * @param wsp - współrzędne pola
 * @return - numer pola
 */
int wspolrzedneNaNumer(WSP wsp);
/**@fn Zmien
 * Funkcja przekolorowuje pole planszy zgodnie z ruchami graczy
 * @param guzik -wskaźnik na przycisk do przekolorowania
 * @param obraz - wskaźnik na obraz wyświetlony na przycisku(zgodn z jego aktualnym kolorem)
 * @param naJakiKolor - informacja o tym jaki kolor ma przbrać przycisk
 */
void Zmien(GtkWidget *guzik, GtkWidget *obraz, int *naJakiKolor);

/**@fn DrawNa Moje
 * Funkcja na podstawie współrzędnych drawning area wylicza współrzędne wewnętrzne
 * @param dwsp - współrzędne drawning area
 * @return - współrzędne wewnętrze
 */
WSP DrawNaMoje(DWSP dwsp);
/**@fn MojeNaDraw
 * Funkcja na podstawie współrzędnych wewnętrznych pola wylicza współrzędne na drawning area
 * @param wsp - współrzędne wewnętrzne
 * @return - współrzędne pola  drawning area
 */
DWSP MojeNaDraw(WSP wsp);
#endif //PROJEKTZC_ZMIANYNOTACJI_H
