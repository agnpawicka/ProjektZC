/**@author Agnieszka Pawicka*/
/**@file 4graczy.c*/

/**@headerfile 4graczy.h*/
#include "4graczy.h"

/**@fn plansza4
 * Funkcja odpowiedzialna za sprawdzenie poprawności ruchu i przekazanie informacji dalej*/
static void plansza4(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        DWSP dwsp;
        dwsp.x = event->x;
        dwsp.y = event->y;
        WSP x = DrawNaMoje(dwsp);
        int nr=wspolrzedneNaNumer(x);
        if(Kto==0 || czyAnimacja==1) return;///Sprawdzenie, czy gra wciąż trwa
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

                    if(Kto==2){///Zmiana w wyświetlanej informacji o tym, czyja kolej na ruch
                        sprintf(gracz, "Kolej gracza zielonego");
                        Kto=3;
                    }
                    else if(Kto==1){
                        sprintf(gracz, "Kolej gracza czerwonego");
                        Kto=4;
                    }
                    else if(Kto==3){
                        sprintf(gracz, "Kolej gracza czarnego");
                        Kto=1;
                    }
                    else{
                        sprintf(gracz, "Kolej gracza białego");
                        Kto=2;
                    }
                    gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);

                    sprintf(t, "Proszę podać początek przesuwanej linii");
                    gtk_label_set_text(GTK_LABEL(info),t);

                    if(BialePunkty+CzarnePunkty==6) {///Sprawdzenie, czy przypadkiem biało-czarni nie wygrali
                        sprintf(t, "GRACZE CZARNO-BIALI ZWCIĘŻYLI");
                        gtk_label_set_text(GTK_LABEL(info),t);
                        Kto=0;
                    }
                    if(ZielonePunkty+CzerwonePunkty==6){///Sprawdzenie, cz przypadkiem zielono-czerwoni nie wygrali
                        sprintf(t, "GRACZE CZERWONO-ZIELONI ZWCIĘŻYLI");
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


/**@fn clear4
 * funkcja konieczna dla dzialania wyswietlania*/
static gboolean clear4(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);
    return FALSE;
}

/**@fn konfig4
 * funkcja konieczna dla dzialania wyswietlania*/
static gboolean konfig4(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
    if (surface) cairo_surface_destroy(surface);
    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
                                                gtk_widget_get_allocated_width(widget),
                                                gtk_widget_get_allocated_height(widget));

    narysuj();
    return TRUE;
}


/**@fn nowaGra4
 * Funkcja rozpocznająca nową grę, zeruje punkty, ustawia kule zgodnie z położeniem początkowym
 * @param widget - wskaźnik na przycisk
 * @param data - NULL konieczny ze względu na działanie GTK+
 */
static void nowaGra4(GtkWidget *widget, gpointer data){
    ileKliknietych=0;
    BialePunkty=0;
    CzarnePunkty=0;
    ZielonePunkty=0;
    CzerwonePunkty=0;
    Kto=2;

    /**Początkowe ustawienia informacji o grze*/
    sprintf(t, "Proszę podać początek przesuwanej linii");
    gtk_label_set_text(GTK_LABEL(info),t);

    sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, ZielonePunkty+CzerwonePunkty);
    gtk_label_set_text(GTK_LABEL(PKT), pkt);

    sprintf(gracz, "Kolej gracza białego");
    gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);

    for(int i=0; i<61; i++){ ///Początkowe ustawienia kul na planszy
        WSP wsp=numerNaWspolrzedne(i);
        if(wsp.x<3 && wsp.y<=3 && wsp.y>=wsp.x ) Dane[i]=1;
        else if((wsp.x<4 && wsp.y>=5)||(wsp.x==4 && wsp.y>5) ) Dane[i]=3;
        else if(wsp.y>=5 && ((wsp.x==6 && wsp.y<7) || (wsp.x==7 && wsp.y<8) || wsp.x==8)) Dane[i]=2;
        else if(wsp.x>=4 && wsp.y<=3 && (wsp.x!=4 || wsp.y!=3))Dane[i]=4;
        else Dane[i]=0;
    }
    narysuj();
}
/**@fn zapiszGre4
 * Funkcja umożliwia zapisanie stanu gry (nie jest jednak możliwe zapisanie ukończonej gry).
 * Przy uruchomieniu program zawsze próbuje załadować ostatnią zapisaną grę.
 * Gra jest pamiętana tak długo, jak długo gracz nie zapisze nowej gry i jak długo plik do zapisu nie jest uszkodzony.
 * @param widget - wskaźnik na przycisk
 * @param data
 */
static void zapiszGre4(GtkWidget *widget, gpointer data){
    if(Kto==0) {
        sprintf(t, "Bez sensu zapiswać skończoną grę");
        gtk_label_set_text(GTK_LABEL(info),t);
        return;
    }

    /**@var zapisGry - wskaźnik na plik do zapisu danych*/
    FILE *zapisGry=fopen("4graczy.bin", "wb");

    if(zapisGry==NULL){///Nie udało się utworzyć/otworzyć pliku
        sprintf(t, "Problem z zapisem gry");
        gtk_label_set_text(GTK_LABEL(info),t);
        return;
    }

    /**Zapisanie danych o grze w tablicy "tablica"*/
    int tablica[67];
    tablica[0]=1;
    for(int i=0; i<61; i++) tablica[i+1]=Dane[i];
    tablica[62]=BialePunkty;
    tablica[63]=CzarnePunkty;
    tablica[64]=ZielonePunkty;
    tablica[65]=CzerwonePunkty;
    tablica[66]=Kto;


    int udane=fwrite(&tablica, sizeof(int), 67, zapisGry);
    if(udane<67){///Problem z zapisem gry
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
/**@fn Instrukcja4
 * Funkcja wyświetla nowe okno zawierające instrukcję gry oraz sposób przekazania intencji gracza do programu
 * @param widget - wskaźnik na przycisk
 * @param data -NULL
 */
static void Instrukcja4(GtkWidget *widget, gpointer data){

    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);///nowe okno
    gtk_window_set_title(GTK_WINDOW(window),"INSTRUKCJA");///dodany tytuł okna
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);///wyśrodkowane okno
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);///wielkość okna


    GtkWidget *INST;/**@var INST - wskaźnik na etkietę z instrukcją*/

    INST=gtk_label_new("Instrukcja:\n\nWERSJA DLA 4 OSÓB: \n\n"
                               "\"Obowiązują zasady 3-osobowego Abalone, z poniższymi wyjątkami:\n"
                               "•  Każdy z graczy posiada po 9 kul\n"
                               "•  Gracze po przeciwnych stronach planszy tworzą jeden zespół.\n"
                               "•  Gracze rozgrywają swoje tury zgodnie z kierunkiem ruchu wskazówek zegara.\n"
                               "•  Podczas ruchu każdy z graczy może korzystać z kul swojego partnera – o ile pierwsza przesunięta kula (ta, która popycha pozostałe) należy do niego.\n"
                               "•  Gracz może przepchnąć 2 kule przeciwników o różnych kolorach. \n"
                               "•  Wygrywa zespół, który jako pierwszy wypchnie 6 kul przeciwników (bez względu na ich kolory).\"\n\n"
                               "Instrukcja zaczerpnięta  bez zmian ze strony www.wydawnictworebel.pl");

    gtk_widget_show(INST);
    gtk_container_add(GTK_CONTAINER(window), INST);
    gtk_widget_show(window);
}

int main4(GtkWidget *widget, gpointer   data)
{
    czyAnimacja=0;
    struct main_args *mainowe=data;
    int argc = mainowe->args;
    char **argv = mainowe->argv;

    Kto=2;
    wersja=4;
    BialePunkty=0;
    CzarnePunkty=0;
    ZielonePunkty=0;
    CzerwonePunkty=0;

    gtk_init (&argc, &argv);///inicjalizacja gtk
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);///nowe okno

    gtk_window_set_title(GTK_WINDOW(window),"ABALONE, CZTERECH GRACZY");///dodany tytuł okna
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);///wyśrodkowane okno

    GdkRGBA color;
    color.green=0.623529;
    color.blue=0.372549;
    color.red=0.623529;
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
    g_signal_connect (G_OBJECT(NowaGra), "clicked", G_CALLBACK(nowaGra4), NULL);
    gtk_box_pack_start(GTK_BOX(boxNaGuziki), NowaGra, 1, 1, 0);


    GtkWidget *instrukcja;///Dodanie przycisku "INSTRUKCJA", odwołanie do funkcji instrukcja
    instrukcja = gtk_button_new_with_label("INSTRUKCJA");
    g_signal_connect (G_OBJECT(instrukcja), "clicked", G_CALLBACK(Instrukcja4), NULL);
    gtk_box_pack_start(GTK_BOX(boxNaGuziki), instrukcja, 1, 1, 0);


    GtkWidget *ZapiszGre;///Dodanie przcisku "ZAPISZ GRĘ", odwołanie do funkcji zapiszGre
    ZapiszGre = gtk_button_new_with_label("ZAPISZ GRĘ");
    g_signal_connect (G_OBJECT(ZapiszGre), "clicked", G_CALLBACK(zapiszGre4), NULL);
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
    g_signal_connect(plansza, "button-press-event", G_CALLBACK(plansza4), NULL);
    gtk_widget_set_events(plansza, gtk_widget_get_events(plansza) | GDK_BUTTON_PRESS_MASK);
    g_signal_connect(plansza, "draw", G_CALLBACK(clear4), NULL);
    g_signal_connect(plansza, "configure-event", G_CALLBACK(konfig4), NULL);

    /**@var zapisanaGra - wskaźnik na plik, który (jeśli istnieje) zawiera dane o stanie zapisanej gry*/
    FILE *zapisanaGra=fopen("4graczy.bin", "rb");


    /**@var ustawieniaPoczatkowe - 0 jeśli istnieje plik z zapisaną grą, którą udało się odtworzyć, 1 w przeciwnym przypadku */
    int ustawieniaPoczatkowe=0;

    if(zapisanaGra==NULL) ustawieniaPoczatkowe=1;
    else{
        int tablica[67];
        int udane=fread(&tablica, sizeof(int) , 67, zapisanaGra);
        if(udane==1 && tablica[0]==0 || udane<67) ustawieniaPoczatkowe=1;///Sprawdzenie, czy udało się wczytać zapisaną grę
        else if(udane==67){
            for(int i=0; i<61; i++){
                Dane[i]=tablica[i+1];
            }
            BialePunkty=tablica[62];
            CzarnePunkty=tablica[63];
            ZielonePunkty=tablica[64];
            CzerwonePunkty=tablica[65];
            Kto=tablica[66];

            /**Poniższe pięć linii zawiera ustawienie etykiet zgodnych ze stanem wczytanej gry (czyja kolej, stan punktacji) */
            if(Kto==2)sprintf(gracz, "Kolej gracza białego");
            else if(Kto==1)sprintf(gracz, "Kolej gracza czarnego");
            else if(Kto==3) sprintf(gracz, "Kolej gracza zielonego");
            else sprintf(gracz, "Kolej gracza czerwonego");
            gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);
            sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, CzerwonePunkty+ZielonePunkty);///początkowe ustawienia "PKT"
            gtk_label_set_text(GTK_LABEL(PKT), pkt);

            fclose(zapisanaGra);
        }
    }

    WSP wsp[61];
    for(int i=0; i<61; i++) wsp[i] = numerNaWspolrzedne(i);///Przypisanie numerom współrzędnch do umiejscowienia przycisków

    if(ustawieniaPoczatkowe==1){///jeśli nie zapisano ostatniej gry lub nie udało się odczytać stanu gry

        /**Poniższe linie zawierają początkowe ustawienia punktacji oraz informację o tym, czyja kolej na ruch*/
        sprintf(gracz, "Kolej gracza białego");
        Kto=2;
        gtk_label_set_text(GTK_LABEL(czyjaKolej), gracz);
        BialePunkty=0;
        CzarnePunkty=0;
        ZielonePunkty=0;
        CzerwonePunkty=0;

        sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, ZielonePunkty+CzerwonePunkty);
        gtk_label_set_text(GTK_LABEL(PKT), pkt);


        for(int i=0; i<61; i++) {///ustawienie kolorów nowej gry
            if(wsp[i].x<3 && wsp[i].y<=3 && wsp[i].y>=wsp[i].x ) Dane[i]=1;
            else if((wsp[i].x<4 && wsp[i].y>=5)||(wsp[i].x==4 && wsp[i].y>5) )Dane[i]=3;
            else if(wsp[i].y>=5 && ((wsp[i].x==6 && wsp[i].y<7) || (wsp[i].x==7 && wsp[i].y<8) || wsp[i].x==8)) Dane[i]=2;
            else if(wsp[i].x>=4 && wsp[i].y<=3 && (wsp[i].x!=4 || wsp[i].y!=3))Dane[i]=4;
            else Dane[i]=0;
        }
    }

    narysuj();
    gtk_widget_queue_draw(plansza);


    gtk_widget_show_all(window);///Wyświetlenie całości
    gtk_main();

    return 0;
}
