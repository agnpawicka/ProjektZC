/**@author Agnieszka Pawicka
* @file sprawdzaniePrzesuniec.h */

#ifndef PROJEKTZC_SPRAWDZANIEPRZESUNIEC_H
#define PROJEKTZC_SPRAWDZANIEPRZESUNIEC_H


/**@headerfile types.h */
/**@headerfile WspolneFunkcjeRoznychWersji.h"*/

#include "WspolneFunkcjeRoznchWersji.h"
#include "types.h"


/**@fn sprawdzPrzesuniecie
 * Funkcja sprawdza czy podany kierunek przesunięcia linii jest poprawny,
 * jeśli jest podaje odpowiednie parametry do zminy kolorów.
 * Zmiena też punktację.
 * @param nr - numer pola podanego jako kierunek przesunięcia
 * @return 0 gdy kierunek nie jest poprawny, 1 w przeciwnm przpadku
 */
int sprawdzPrzesuniecie(int nr);

/**@fn sprawdzPoczatekLinii
 * Funkcja sprawdza czy podano dobrą kulę jako początek przesuwanej linii, wypisuje komunikaty o błędach w odpowiedniej etykiecie.
 * @param nr - numer pola podanego jako początek linii
 */
void sprawdzPoczatekLinii(int nr);

/**@fn sprawdzKoniecLinii
 * Funkcja odwołuje się do funkcji, która sprawdza czy podano dobrą kulę jako koniec przesuwanej linii.
 * Wypisuje komunikaty o błędach w odpowiedniej etykiecie.
 * @param nr - numer pola podanego jako początek linii
 */
void sprawdzKoniecLinii(int nr);

#endif //PROJEKTZC_SPRAWDZANIEPRZESUNIEC_H
