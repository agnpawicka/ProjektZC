/**@author Agnieszka Pawicka*/
/**@file main.c*/
/**
    Funkcja main tworzy aplikację oraz wyświetla okno dające użytwokwinkowi cztery możliwości:
    * rozegranie gry dwuosobowej
    * rozegranie gry trzyosobowej
    * rozegranie gry czteroosobowej
    * zamknięcie aplikacji
    Rozegranie dowolnej wersji gry wiąże się z otwarciem nowego okna od parametrów int argc, char **argv z funkcji main.
    Moduły "2graczy", "3graczy", "4graczy" tworzą wymienione wyżej okna i obsługują ich działanie.

    Po otwarciu kolejnego (nie pierwszego) okna gry wszystkie poprzednie przestają działać. Jest to spowodowane nadpisaniem danych o planszy.
*/

#include <gtk/gtk.h>
#include "2graczy.h"
#include "3graczy.h"
#include "4graczy.h"
#include "types.h"

/**@fn static void activate
 * @param app- aplikacja którą tworzy main
 * @param data - dane przekazywane modułom odpowiedzialnym za grę
 Funkcja dodaje okno i przyciski przekierowujące dalej
 *@var window - wskaźnik na okno
 *@var grid - wskaźnik na siatkę
 *@var button - wskaźnik na przycisk (tylko do deklaracji przycisku oraz określenia jego roli)
 *@var informacja - wskaźnik na etykietę z informacją nad przyciskami
 * */

static void activate (GtkApplication *app, gpointer data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *informacja;

    /**Ustawienie koloru tła*/
    GdkRGBA color;
    color.red = 0.2;
    color.green = 0.6;
    color.blue = 0.623;
    color.alpha=1;

    /**tworzenie okna o tytule "Abalone" z ustawieniem jego wielkości oraz koloru tła*/
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Abalone");
    gtk_container_set_border_width (GTK_CONTAINER (window), 100);
    gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &color);


    /**tworzenie siatki oraz dodanie jej do okna*/
    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);


    /**dodanie informacji dla użytkowników*/
    informacja=gtk_label_new("Możliwe jest rozgrywanie JEDNEJ GRY w danym momencie!");
    gtk_grid_attach(GTK_GRID(grid), informacja, 0, 0, 73, 1);

    /**przycisk przekierowujący do gry dwuosobowej*/
    button = gtk_button_new_with_label ("Wersja dla dwóch osób");
    g_signal_connect (button, "clicked", G_CALLBACK (main2), data);
    gtk_grid_attach (GTK_GRID (grid), button, 30, 10, 13, 3);

    /**przycisk przekierowujący do gry trzyosobowej*/
    button = gtk_button_new_with_label ("Wersja dla trzech osób");
    g_signal_connect (button, "clicked", G_CALLBACK (main3), data);
    gtk_grid_attach (GTK_GRID (grid), button, 30, 20, 13, 3);

    /**przycisk przekierowujący do gry czteroosobowej*/
    button = gtk_button_new_with_label ("Wersja dla czterech osób");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (main4), data);
    gtk_grid_attach (GTK_GRID (grid), button, 30, 30, 13, 3);

    /**przycisk wyłączający aplikację*/
    button = gtk_button_new_with_label ("Wyjscie");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach (GTK_GRID (grid), button, 30, 40, 13, 3);

    /**<okno zawsze w centrum ekranu*/
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

    gtk_widget_show_all (window);

}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;
    /**@var x - wartośći int argc, char **argv */
    struct main_args x;
    x.args=argc;
    x.argv=argv;
    gpointer  data = &x;

    app = gtk_application_new ("start.gtk.o", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), data);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}