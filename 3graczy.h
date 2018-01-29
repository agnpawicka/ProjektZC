/**@author Agnieszka Pawicka
 * @file 3graczy.h */

#ifndef PROJEKTZC_3GRACZY_H
#define PROJEKTZC_3GRACZY_H

/**@headerfile types.h */
/**@headerfile zmianyNotacjiIObrazow.h*/
/**@headerfile WspolneFunkcjeRoznychWersji.h"*/
/**@headerfile sprawdzaniePrzesuniec.h*/

#include "types.h"
#include "zmianyNotacjiIObrazow.h"
#include "WspolneFunkcjeRoznchWersji.h"
#include "sprawdzaniePrzesuniec.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

/**@fn main3
 * Funkcja udostępniania main.c, tworzy nowe okno i obsługuje grę trzyosobową
 * @param widget - nieużywana wartość wskaźnika na przycisk w main.c
 * @param data - dane z main.c takie jak int argc, char ** argv
 * @return zwraca 0 jeśli nie zwróci błędu
 */
int main3(GtkWidget *widget,
          gpointer   data);
#endif //PROJEKTZC_3GRACZY_H
