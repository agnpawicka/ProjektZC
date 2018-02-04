/**@author Agnieszka Pawicka*/
/**@file 3graczy.c*/

/**@headerfile 3graczy.h*/
#include "3graczy.h"



static void plansza3(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        printf("%f %f\n", event->x, event->y);
        DWSP dwsp;
        dwsp.x = event->x;
        dwsp.y = event->y;
        WSP x = DrawNaMoje(dwsp);
        printf("%d %d moje\n", x.x, x.y);
        int nr=wspolrzedneNaNumer(x);
        if(Kto==0) return;///Sprawdzenie, czy gra wciąż trwa
        switch (ileKliknietych){///Sprawdzenie, któr etap ruchu trwa
            case 0:///początek, program dostał początek przesuwanej przez gracza linii
                sprawdzPoczatekLinii(nr);
                break;
            case 1:///program ma już dane o początku linii, sprawdzenie, czy dobrze podano koniec linii
                sprawdzKoniecLinii(nr);
                break;
            default:///program posiada już dane o przesuwanej linii, sprawdza czy dobrze podano kierunek przesunięcia
                if(sprawdzPrzesuniecie(nr)>0)///Dobrze podane przesunięcie
                {

                    narysuj();
                    gtk_widget_queue_draw(plansza);
                    if(Kto==2){///Zmiana w wyświetlanej informacji o tym, czyja kolej na ruch
                        sprintf(gracz, "Kolej gracza zielonego");
                        Kto=3;
                    }
                    else if(Kto==1){
                        sprintf(gracz, "Kolej gracza białego");
                        Kto=2;
                    }
                    else{
                        sprintf(gracz, "Kolej gracza czarnego");
                        Kto=1;
                    }
                    gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);

                    sprintf(t, "Proszę podać początek przesuwanej linii");
                    gtk_label_set_text(GTK_LABEL(info),t);

                    if(BialePunkty==6) {///Sprawdzenie, czy przypadkiem biały gracz nie wygrał
                        sprintf(t, "GRACZ GRAJĄCY BIAŁYMI KULAMI ZWCIĘŻYŁ");
                        gtk_label_set_text(GTK_LABEL(info),t);
                        Kto=0;
                    }
                    if(CzarnePunkty==6){///Sprawdzenie, cz przypadkiem czarny gracz nie wygrał
                        sprintf(t, "GRACZ GRAJĄCY CZARNYMI KULAMI ZWCIĘŻYŁ");
                        gtk_label_set_text(GTK_LABEL(info),t);
                        Kto=0;
                    }
                    if(ZielonePunkty==6){///Sprawdzenie, cz przypadkiem zielony gracz nie wygrał
                        sprintf(t, "GRACZ GRAJĄCY ZIELONYMI KULAMI ZWCIĘŻYŁ");
                        gtk_label_set_text(GTK_LABEL(info),t);
                        Kto=0;
                    }
                }
                else///Błędny kierunek, gracz jest zmuszony do rozpoczęcia ruchu od nowa
                {
                    sprintf(t, "Źle podany kierunek. Proszę podać początek przesuwanej linii");
                    gtk_label_set_text(GTK_LABEL(info),t);
                }
                ileKliknietych=0;
                break;
        }
        narysuj();
    }
}
/**@fn nowaGra3
 * Funkcja rozpocznająca nową grę, zeruje punkty, ustawia kule zgodnie z położeniem początkowym
 * @param widget - wskaźnik na przycisk
 * @param data - NULL konieczny ze względu na działanie GTK+
 */
static void nowaGra3(GtkWidget *widget, gpointer data){
    ileKliknietych=0;
    BialePunkty=0;
    CzarnePunkty=0;
    ZielonePunkty=0;
    Kto=2;

    /**Początkowe ustawienia informacji o grze*/
    sprintf(t, "Proszę podać początek przesuwanej linii");
    gtk_label_set_text(GTK_LABEL(info),t);

    sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);
    gtk_label_set_text(GTK_LABEL(PKT), pkt);

    sprintf(gracz, "Kolej gracza białego");
    gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);

    for(int i=0; i<61; i++){///Początkowe ustawienia kul na planszy
        WSP wsp=numerNaWspolrzedne(i);
        if(wsp.x<2 ) Dane[i]=1;
        else if(wsp.y>6 ) Dane[i]=3;
        else if((wsp.x==3 && wsp.y==0) || (wsp.x>=4 && wsp.x-wsp.y>2 )) Dane[i]= 2;
        else  Dane[i]=0;
    }
    narysuj();
    gtk_widget_queue_draw(plansza);
}
/**@fn zapiszGre3
 * Funkcja umożliwia zapisanie stanu gry (nie jest jednak możliwe zapisanie ukończonej gry).
 * Przy uruchomieniu program zawsze próbuje załadować ostatnią zapisaną grę.
 * Gra jest pamiętana tak długo, jak długo gracz nie zapisze nowej gry i jak długo plik do zapisu nie jest uszkodzony.
 * @param widget - wskaźnik na przycisk
 * @param data
 */
static void zapiszGre3(GtkWidget *widget, gpointer data){
    if(Kto==0) {
        sprintf(t, "Bez sensu zapiswać skończoną grę");
        gtk_label_set_text(GTK_LABEL(info),t);
        return;
    }

    /**@var zapisGry - wskaźnik na plik do zapisu danych*/
    FILE *zapisGry=fopen("3graczy.bin", "wb");

    if(zapisGry==NULL){///Nie udało się utworzyć/otworzyć pliku
        sprintf(t, "Problem z zapisem gry");
        gtk_label_set_text(GTK_LABEL(info),t);
        return;
    }

    /**Zapisanie danych o grze w tablicy "tablica"*/
    int tablica[66];
    tablica[0]=1;
    for(int i=0; i<61; i++) tablica[i+1]=Dane[i];
    tablica[62]=BialePunkty;
    tablica[63]=CzarnePunkty;
    tablica[64]=ZielonePunkty;
    tablica[65]=Kto;


    int udane=fwrite(&tablica, sizeof(int), 66, zapisGry);
    if(udane<66){///Problem z zapisem gry
        sprintf(t, "Problem z zapisem gry");
        gtk_label_set_text(GTK_LABEL(info),t);
        return;
    }
    else {
        sprintf(t, "Gra zapisana");
        gtk_label_set_text(GTK_LABEL(info),t);
    }
    fclose(zapisGry);
}
/**@fn Instrukcja3
 * Funkcja wyświetla nowe okno zawierające instrukcję gry oraz sposób przekazania intencji gracza do programu
 * @param widget - wskaźnik na przycisk
 * @param data -NULL
 */
static void Instrukcja3(GtkWidget *widget, gpointer data){

    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);///nowe okno
    gtk_window_set_title(GTK_WINDOW(window),"INSTRUKCJA");///dodany tytuł okna
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);///wyśrodkowane okno
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);///wielkość okna


    GtkWidget *INST;/**@var INST - wskaźnik na etkietę z instrukcją*/
    INST=gtk_label_new("Instrukcja:\n\nWERSJA DLA 3 OSÓB: \n\n"
                                "\"Obowiązują zasady 2-osobowego Abalone, z poniższmi wyjątkami:\n"
                               "•  Każdy gracz posiada po 11 kul\n"
                               "•  Gracz może użyć 3 swoich kul, żeby przepchnąć 2 kule różnych kolorów (przeciwników). \n"
                               "•  Każdy z graczy zdobywa punkt za kule, które udało mu się wypchnąć.\n"
                               "•   Wygrywa ten z graczy, który jako pierwszy wypchnie 6 kul przeciwników (bez względu na ich kolory).\"\n\n"
                               "Instrukcja wzorowana (z niewielkimi zmianami) na umieszczonej na stronie www.wydawnictworebel.pl");


    gtk_widget_show(INST);
    gtk_container_add(GTK_CONTAINER(window), INST);
    gtk_widget_show(window);
}


static gboolean clear3(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);
    return FALSE;
}

static gboolean konfig3(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
    if (surface) cairo_surface_destroy(surface);
    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width(widget),
                                                gtk_widget_get_allocated_height(widget));

    narysuj();
    return TRUE;
}


int main3(GtkWidget *widget, gpointer   data)
{
    struct main_args *mainowe=data;
    int argc = mainowe->args;
    char **argv = mainowe->argv;

    Kto=2;
    wersja=3;
    BialePunkty=0;
    CzarnePunkty=0;
    ZielonePunkty=0;

    gtk_init (&argc, &argv);///inicjalizacja gtk
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);///nowe okno

    gtk_window_set_title(GTK_WINDOW(window),"ABALONE, TRZECH GRACZY");///dodany tytuł okna
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);///wyśrodkowane okno

    GdkRGBA color;
    color.green=0.6;
    color.blue=0.2;
    color.red=0.4;
    color.alpha=1;
    gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &color);/// kolor okna

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);///zamknięcie okna


    GtkWidget *vbox;///stworzony pierwszy box (zamiennik grid'a)
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);///dodana do okna


    czyjaKolej = gtk_label_new("Kolej gracza białego");///czyja kolej
    gtk_box_pack_start(GTK_BOX(vbox), czyjaKolej, 0, 0, 0);


    PKT = gtk_label_new("Punkty gracza białego: 0  Punkty gracza czarnego: 0");
    gtk_box_pack_start(GTK_BOX(vbox), PKT, 0, 0, 0);

    GtkWidget *boxNaGuziki;
    boxNaGuziki = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), boxNaGuziki, 0, 0, 0);

    GtkWidget *NowaGra;///Dodanie przycisku "NOWA GRA", odwołanie do funkcji nowaGra
    NowaGra = gtk_button_new_with_label("NOWA GRA");
    g_signal_connect (G_OBJECT(NowaGra), "clicked", G_CALLBACK(nowaGra3), NULL);
    gtk_box_pack_start(GTK_BOX(boxNaGuziki), NowaGra, 1, 1, 0);


    GtkWidget *instrukcja;///Dodanie przycisku "INSTRUKCJA", odwołanie do funkcji instrukcja
    instrukcja = gtk_button_new_with_label("INSTRUKCJA");
    g_signal_connect (G_OBJECT(instrukcja), "clicked", G_CALLBACK(Instrukcja3), NULL);
    gtk_box_pack_start(GTK_BOX(boxNaGuziki), instrukcja, 1, 1, 0);


    GtkWidget *ZapiszGre;///Dodanie przcisku "ZAPISZ GRĘ", odwołanie do funkcji zapiszGre
    ZapiszGre = gtk_button_new_with_label("ZAPISZ GRĘ");
    g_signal_connect (G_OBJECT(ZapiszGre), "clicked", G_CALLBACK(zapiszGre3), NULL);
    gtk_box_pack_start(GTK_BOX(boxNaGuziki), ZapiszGre, 1, 1, 0);


    info = gtk_label_new("Proszę podać początek przesuwanej linii");///początkowe ustawienia informacji o ruchach
    gtk_box_pack_start(GTK_BOX(vbox), info, 0, 0, 0);


    ///stworzenie ramki do drawning area (dla animacji)
    ramka = gtk_frame_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), ramka, 0, 1, 0);

    ///dodanie drawning area
    plansza = gtk_drawing_area_new();
    gtk_widget_set_size_request(plansza, 540, 540);
    gtk_container_add(GTK_CONTAINER(ramka), plansza);
    g_signal_connect(plansza, "button-press-event", G_CALLBACK(plansza3), NULL);
    gtk_widget_set_events(plansza, gtk_widget_get_events(plansza) | GDK_BUTTON_PRESS_MASK);
    g_signal_connect(plansza, "draw", G_CALLBACK(clear3), NULL);
    g_signal_connect(plansza, "configure-event", G_CALLBACK(konfig3), NULL);



    /**@var zapisanaGra - wskaźnik na plik, który (jeśli istnieje) zawiera dane o stanie zapisanej gry*/
    FILE *zapisanaGra=fopen("3graczy.bin", "rb");


    /**@var ustawieniaPoczatkowe - 0 jeśli istnieje plik z zapisaną grą, którą udało się odtworzyć, 1 w przeciwnym przypadku */
    int ustawieniaPoczatkowe=0;

    if(zapisanaGra==NULL) ustawieniaPoczatkowe=1;
    else{
        int tablica[66];
        int udane=fread(&tablica, sizeof(int) , 66, zapisanaGra);
        if(udane==1 && tablica[0]==0 || udane<66) ustawieniaPoczatkowe=1;///Sprawdzenie, czy udało się wczytać zapisaną grę
        else if(udane==66){
            for(int i=0; i<61; i++){
                Dane[i]=tablica[i+1];
            }
            BialePunkty=tablica[62];
            CzarnePunkty=tablica[63];
            ZielonePunkty=tablica[64];
            Kto=tablica[65];

            /**Poniższe pięć linii zawiera ustawienie etykiet zgodnych ze stanem wczytanej gry (czyja kolej, stan punktacji) */
            if(Kto==2)sprintf(gracz, "Kolej gracza białego");
            else if(Kto==1)sprintf(gracz, "Kolej gracza czarnego");
            else sprintf(gracz, "Kolej gracza zielonego");
            gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);
            sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);///początkowe ustawienia "PKT"
            gtk_label_set_text(GTK_LABEL(PKT), pkt);

            fclose(zapisanaGra);
        }
    }
    WSP wsp[61];
    for (int i = 0; i < 61; i++)
        wsp[i] = numerNaWspolrzedne(i);///Przypisanie numerom współrzędnch do umiejscowienia przycisków

    if(ustawieniaPoczatkowe==1){///jeśli nie zapisano ostatniej gry lub nie udało się odczytać stanu gry

        /**Poniższe linie zawierają początkowe ustawienia punktacji oraz informację o tym, czyja kolej na ruch*/
        sprintf(gracz, "Kolej gracza białego");
        Kto=2;
        gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);
        BialePunkty=0;
        CzarnePunkty=0;
        ZielonePunkty=0;
        sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);
        gtk_label_set_text(GTK_LABEL(PKT), pkt);


        for(int i=0; i<61; i++) {///ustawienie kolorów nowej gry
            if(wsp[i].x<2 ) Dane[i]=1;
            else if(wsp[i].y>6 ) Dane[i]=3;
            else if((wsp[i].x==3 && wsp[i].y==0) || (wsp[i].x>=4 && wsp[i].x-wsp[i].y>2)) Dane[i]=2;
            else Dane[i]=0;
        }
    }
    narysuj();
    gtk_widget_queue_draw(plansza);



    gtk_widget_show_all(window);///Wyświetlenie całości
    gtk_main();

    return 0;
}
