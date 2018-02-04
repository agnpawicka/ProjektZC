/**@author Agnieszka Pawicka
 * @file WspolneFunkcjeRoznychWersji.h */


/**Jak są przechowywane dane o planszy?
    Plansza do Abalone ma kształt sześciokąta o bokach długości odpowiadającej pięciu polom.
    Para boków równoległych planszy jest wyświetlana pionowo.

    Pola planszy są ustawione w dziewięciu kolumnach numerowanch od 0 (od lewej).
    Numer kolumny w której znajduje się pole stanowi jego współrzędną x.
    Kolejne kolumny są przesunięte w dół o długość odpowiadającą połowie pola.

    Niech X oznacza współrzędną x danego pola.Współrzędną y (oznaczoną Y) pola jest:
        - jeżeli X=0, Y jest liczbą naturalną z zakresu od 0 do 4 włącznie, z zachowaniem zasady, że Y pola znajdującego się wyżej jest większe,
        - jeżeli X>0:
            - jeżeli istnieje pole A o współrzednej x równej X-1 i położone o pół długości pola wyżej, Y jest równe współrzędnej y pola A,
            - jeżeli istnieje pole A o współrzednej x równej X i położone o długość pola wyżej, Y jest równe współrzędnej y pola A zmniejszonej o 1,
            - jeżeli istnieje pole A o współrzednej x równej X i położone o długość pola niżej, Y jest równe współrzędnej y pola A zwiększonej o 1.

    Inaczej można wyobrazić sobie układ współrzędnych, w którym oś OY jest obrócona o 30 stopni w kierunku zgodnym ze wskazówkami zegara (kąt pomiędzy osiami jest wtedy równy 60 stopni).
    Współrzędne pola odzwierciedlają położenie środka pola w tym układzie współrzędnch.

    Unikalne numery pól są liczbami porządkowymi (numerowanymi od 0) porządku leksykograficznego zbioru par współrzędnch pola, gdzie współrzędna x jest pierwszm elementem pary.

    Położenie przycisku pola jest wyliczane na podstawie współrzędnych pola.
    Wskaźnik na przycisk, dane o kolorze i wskaźnik na wyświetlany obraz są przechowywane w tablicy struktur.
    Kluczem do danych w tablicy struktur jest numer pola.
*/

/**O programie i grze:
 * Przesunięcie kul na planszy wymaga trzech danych (w postaci odpowiednio "klikniętych" pól planszy)
    Jako, że możliwe jest przesuwanie jednej, dwóch lub trzech kul znajdujących się w jednej linii, należy podać początek oraz koniec linii.
    W przypadku pojedynczej kuli początek i koniec są tym samym polem.
    W przypadku trzech kul początek i koniec linii nie sąsiadują ze sobą.
    Trzecią informacją jest kierunek przesunięcia kul. Musi być to przyciśnięcie przycisku sąsiadującego z tym, który określiliśmy jako koniec linii.
    Cała podana linia kul (jeśli ruch jest poprawny) powinna przesunąć się w kierunku zgodnym z kierunkiem przesunięcia końca linii na pole "kliknięte" jako trzecie.


   * Terminologia:
    Przez przesunięcie rozumiane jest przestawienie swoich kul.
    Przez przepchnięcie rozumiane jest przestawienie kul przeciwnika przez przeważającą liczbę własnych kul.
    Przez wypchnięcie rozumiane jest przepchnięcie kul przeciwnika poza planszę (równoznaczne ze zdobyciem punktu).



    *Na początku program zawsze sprawdza czy jest w stanie załadować ostatnio zapisaną grę (i czy taka istnieje).
    Jeśli nie jest to możliwe program wyświetla planszę z ustawieniami początkowykmi, tj. kule znajdują się na początkowych pozycjach,
    żaden z graczy nie ma punktów oraz kolej na ruch gracza grającego białymi kulami/

   * Może się zdarzyć, że po załadowaniu starej gry i zakończeniu jej nie zapiszemy innej,
    wtedy po ponownym uruchomieniu program nadal będzie wyświetlał ostatnio zapisaną grę.

    *Zapisanie gry umożliwia przycisk "ZAPISZ GRĘ", rozpoczęcie nowej gry przycisk "NOWA GRA".
    Jeżeli gracz ma wątpliwości co do zasad, przycisk "INSTRUKCJA" tworzy nowe okno wyświetlające instrukcję gry.
 */


#ifndef PROJEKTZC_WSPOLNEFUNKCJEROZNCHWERSJI_H
#define PROJEKTZC_WSPOLNEFUNKCJEROZNCHWERSJI_H

/**@headerfile types.h */
/**@headerfile zmianyNotacjiIObrazow.h*/

#include "types.h"
#include "zmianyNotacjiIObrazow.h"
#include <stdio.h>
#include <stdlib.h>


/**@var Dane[61]
 * tablica przechowująca dane o polu*/
int Dane[61];

extern cairo_surface_t *surface;
GtkWidget *ramka;
GtkWidget *plansza;

/**@var wersja - przechowuje informację iluosobowa wersja jest rozgrwana*/
int wersja;

/**@var Kto - przechowuje informację o tym, który gracz powinien w danym momencie wykonać ruch*/
int Kto;

/**@var ileKliknietych - informacja o tym, ile poprawnych kliknięć w ruchu wykonano
 * W przypadku błędów często zerowana*/
int ileKliknietych;

/**@var poprzedniKlikniety - informacja o końcu przesuwanej linii (przechowuje unikalny numer pola)*/
int poprzedniKlikniety;

/**@var przedPoprzedniKlikniety - informacja o początku przesuwanej linii (przechowuje unikalny numer pola)*/
int przedPoprzedniKlikniety;


/**@var BialePunkty - liczba punktów zdobytych przez gracza grającego białymi kulami*/
int BialePunkty;

/**@var CzarnePunkty - liczba punktów zdobytych przez gracza grającego czarnymi kulami*/
int CzarnePunkty;


/**@var ZielonePunkty - liczba punktów zdobytych przez gracza grającego zielonymi kulami*/
int ZielonePunkty;

/**@var CzerwonePunkty - liczba punktów zdobytych przez gracza grającego czerwonymi kulami*/
int CzerwonePunkty;

/**@var PKT - wskaźnik na etykietę wyświetlającą punktację w danym momencie gry */
GtkWidget *PKT;

/**@var info - wskaźnik na etykietę wyświetlającą polecenia dotyczące tury i błęd ruchu*/
GtkWidget *info;

/**@var czyjaKolej - wskaźnik na etykietę wyświetlającą czyja kolej na ruch*/
GtkWidget *czyjaKolej;

/**gracz, t, pkt są pomocniczymi wartościami przydatnymi do wyświetlania informacji o grze */
char gracz[25];
char t[80];
char pkt[83];


/**@fn czySasiaduja
 * Funkcja na podstawie współrzędnych dwóch pól sprawdza, czy pola znajdują się obok siebie na planszy
 * @param a - współrzędne pierwszego pola
 * @param b - współrzędne drugiego pola
 * @return: 1 jeśli pola sąsiadują, 0 w przeciwnym przypadku
 */
int czySasiaduja(WSP a, WSP b);

/**@fn pozaPlansza
 * Funkcja sprawdza, czy pole o podanych współrzędnych należy do planszy
 * @param N - współrzędne pola
 * @return 0 jeśli pole należy do planszy, 1 w przeciwnym przypadku
 */
int pozaPlansza(WSP N);

/**@fn czyDobryKoniec
 * Funkcja sprawdza, czy koniec i początek przesuwanej linii:
 * -mają ten sam kolor lub kolor sojuszniczy (patrz: gra czteroosobowa),
 * -znajdują się w jednej linii,
 * -nie są od siebie zbyt odległe,
 * -jeśli przedstawiają trz kule, czy kula w środku ma odpowiedni kolor.
 * @param a - numer pierwszego pola
 * @param b - numer drugiego pola
 * @return 1 jeśli parametry spełniają warunki, 0 w przeciwnym przypadku
 */
int czyDobryKoniec(int a, int b);


/**@fn zmianaKoloru
 * Funkcja odwołująca się do funkcji Zmien (zmianyNotacjiIObrazow) oraz zmieniające dane o kolorze pola.
 * @param nr - numer pola zmienianego
 * @param kolor - nowy kolor pola nr
 */
void zmianaKoloru(int nr, int kolor);

/**@fn narysuj
 * funksja rysuje odpowiednią planszę na drawning area
 * */
void narysuj();

#endif //PROJEKTZC_WSPOLNEFUNKCJEROZNCHWERSJI_H
