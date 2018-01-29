/**@author Agnieszka Pawicka */
/**@file types.h
 Plik  zawiera definicje struktur używanych w programie
 */

#ifndef PROJEKTZC_TYPES_H
#define PROJEKTZC_TYPES_H

#include <gtk/gtk.h>
#include <stdio.h>
/**@struct main_args - struktura przechowująca dane z main.c przekazywane modułom odpowiedzialnym za grę */
struct main_args{
    int args;
    char **argv;
};
/**@typedef wspolrzedne WSP
 * @struct wspolrzedne - struktura przechowująca dane o położeniu pola na planszy
 * @var x - współrzędna pozioma
 * @var y - współrzędna pionowa
 */
typedef struct wspolrzedne{
    int x;
    int y;
} WSP;

/**@typedef daneDotczacePlanszy doPlanszy
 * @struct daneDotczaxePlanszy - struktura przechowująca dane o konkretnym polu na planszy
 * @var kolor - dane o kolorze pola (czy pole jest puste, jaki jest kolor kuli znajdującej się na polu)
 * @var guzik - wskaźnik na przycisk pola na planszy
 * @var obraz - wskaźnik na obraz wyświetlony na przcisku (odpowiadający kolorowi)
 */

typedef struct daneDotyczacePlanszy{
    int kolor;
    GtkWidget *guzik;
    GtkWidget *obraz;
}doPlanszy;
#endif //PROJEKTZC_TYPES_H
