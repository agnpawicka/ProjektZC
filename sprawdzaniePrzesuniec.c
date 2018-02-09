/**@author Agnieszka Pawicka
* @file sprawdzaniePrzesuniec.c */

#include "sprawdzaniePrzesuniec.h"

DWSP POPKLIK;/**@var POPKLIK - wspolrzedne pierwszej z przesuwanych kul */
DWSP PPKLIK;/**@var PPKLIK - wspolrzedne drugiej z przesuwanych kul */
DWSP trzeci;/**@var ptrzeci - wspolrzedne trzeciej z przesuwanych kul */
DWSP pozycja;/**@var pozycja - roznice polozen kul przy przesunieciach */
DWSP czwarty;/**@var czwarty - wspolrzedne czwartej z przesuwanych kul */
DWSP piaty;/**@var piaty - wspolrzedne piatej z przesuwanych kul */

WSP przedP;/**@przedP - współrzędne przedPoprzedniKlikniety*/
WSP poprzedni;/**@poprzedni - wspolrzedne poprzedniKlikniety*/
WSP delta;/**@var delta - przechowuje różnicę pomiędzy kierunkiem przesunięcia a końcem linii (a dokładniej między ich współrzędnymi) */

WSP N;/**@N - współrzędne Nr*/
WSP N1;/**@N2 - współrzędne pola na które mogą sięgnąć przesunięcia 3 kul (jesli 3 przepchną jedną)*/
WSP N2;/**@N2 - współrzędne pola na które najdalej mogą sięgnąć przesunięcia 3 kul(jesli 3 przepchną 2)*/
WSP posredni;/**@posredni - współrzędne kuli srodkowej prz przesunieciu trzech*/
int licznik=0;
int Nr;
/**poniższe 11 funkcji obsługuje animacje różnch ruchów*/
gboolean funkcja(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    dwspDane[poprzedniKlikniety].x=POPKLIK.x;
    dwspDane[poprzedniKlikniety].y=POPKLIK.y;
    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, 0);
        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja2(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=POPKLIK.x;
    dwspDane[poprzedniKlikniety].y=POPKLIK.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;
    narysuj();
    gtk_widget_queue_draw(plansza);

    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);
        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja3(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=POPKLIK.x;
    dwspDane[poprzedniKlikniety].y=POPKLIK.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[Nr].x=trzeci.x;
    dwspDane[Nr].y=trzeci.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(wspolrzedneNaNumer(N), Dane[Nr]);
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[Nr]=MojeNaDraw(numerNaWspolrzedne(Nr));
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja4(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=POPKLIK.x;
    dwspDane[poprzedniKlikniety].y=POPKLIK.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[Nr].x=trzeci.x;
    dwspDane[Nr].y=trzeci.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[Nr]=MojeNaDraw(numerNaWspolrzedne(Nr));
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja5(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=POPKLIK.x;
    dwspDane[poprzedniKlikniety].y=POPKLIK.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;
    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, 0);
        zmianaKoloru(wspolrzedneNaNumer(N), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja6(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;
    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[wspolrzedneNaNumer(posredni)]);
        zmianaKoloru(wspolrzedneNaNumer(posredni), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja7(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;
    czwarty.x+=pozycja.x;
    czwarty.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;

    dwspDane[wspolrzedneNaNumer(N)].x=czwarty.x;
    dwspDane[wspolrzedneNaNumer(N)].y=czwarty.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[wspolrzedneNaNumer(posredni)]);
        zmianaKoloru(wspolrzedneNaNumer(posredni), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        dwspDane[wspolrzedneNaNumer(N)]=MojeNaDraw(N);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja8(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;
    czwarty.x+=pozycja.x;
    czwarty.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;

    dwspDane[wspolrzedneNaNumer(N)].x=czwarty.x;
    dwspDane[wspolrzedneNaNumer(N)].y=czwarty.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(wspolrzedneNaNumer(N1), Dane[Nr]);
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[wspolrzedneNaNumer(posredni)]);
        zmianaKoloru(wspolrzedneNaNumer(posredni), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        dwspDane[wspolrzedneNaNumer(N)]=MojeNaDraw(N);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja9(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;
    czwarty.x+=pozycja.x;
    czwarty.y+=pozycja.y;
    piaty.x+=pozycja.x;
    piaty.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;

    dwspDane[wspolrzedneNaNumer(N)].x=czwarty.x;
    dwspDane[wspolrzedneNaNumer(N)].y=czwarty.y;


    dwspDane[wspolrzedneNaNumer(N1)].x=piaty.x;
    dwspDane[wspolrzedneNaNumer(N1)].y=piaty.y;

    narysuj();
    gtk_widget_queue_draw(plansza);

    licznik++;
    if(licznik==20) {
        Dane[wspolrzedneNaNumer(N1)]=Dane[Nr];
        Dane[Nr]=Dane[poprzedniKlikniety];
        Dane[poprzedniKlikniety]=Dane[wspolrzedneNaNumer(posredni)];
        Dane[wspolrzedneNaNumer(posredni)]=Dane[przedPoprzedniKlikniety];
        Dane[przedPoprzedniKlikniety]=0;

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        dwspDane[wspolrzedneNaNumer(N)]=MojeNaDraw(N);
        dwspDane[wspolrzedneNaNumer(N1)]=MojeNaDraw(N1);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja10(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;
    czwarty.x+=pozycja.x;
    czwarty.y+=pozycja.y;
    piaty.x+=pozycja.x;
    piaty.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;

    dwspDane[wspolrzedneNaNumer(N)].x=czwarty.x;
    dwspDane[wspolrzedneNaNumer(N)].y=czwarty.y;


    dwspDane[wspolrzedneNaNumer(N1)].x=piaty.x;
    dwspDane[wspolrzedneNaNumer(N1)].y=piaty.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(wspolrzedneNaNumer(N2), Dane[wspolrzedneNaNumer(N1)]);
        zmianaKoloru(wspolrzedneNaNumer(N1), Dane[Nr]);
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, Dane[wspolrzedneNaNumer(posredni)]);
        zmianaKoloru(wspolrzedneNaNumer(posredni), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(przedPoprzedniKlikniety, 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        dwspDane[wspolrzedneNaNumer(N)]=MojeNaDraw(N);
        dwspDane[wspolrzedneNaNumer(N1)]=MojeNaDraw(N1);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}

gboolean funkcja11(gpointer data){
    czyAnimacja=1;
    POPKLIK.x+=pozycja.x;
    POPKLIK.y+=pozycja.y;
    PPKLIK.x+=pozycja.x;
    PPKLIK.y+=pozycja.y;

    trzeci.x+=pozycja.x;
    trzeci.y+=pozycja.y;

    dwspDane[poprzedniKlikniety].x=trzeci.x;
    dwspDane[poprzedniKlikniety].y=trzeci.y;

    dwspDane[przedPoprzedniKlikniety].x=PPKLIK.x;
    dwspDane[przedPoprzedniKlikniety].y=PPKLIK.y;

    dwspDane[wspolrzedneNaNumer(posredni)].x=POPKLIK.x;
    dwspDane[wspolrzedneNaNumer(posredni)].y=POPKLIK.y;

    narysuj();
    gtk_widget_queue_draw(plansza);
    licznik++;
    if(licznik==20) {
        zmianaKoloru(wspolrzedneNaNumer(N1), Dane[przedPoprzedniKlikniety]);
        zmianaKoloru(wspolrzedneNaNumer(N2), Dane[wspolrzedneNaNumer(posredni)]);
        zmianaKoloru(Nr, Dane[poprzedniKlikniety]);
        zmianaKoloru(poprzedniKlikniety, 0);
        zmianaKoloru(przedPoprzedniKlikniety, 0);
        zmianaKoloru(wspolrzedneNaNumer(posredni), 0);

        dwspDane[poprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(poprzedniKlikniety));
        dwspDane[przedPoprzedniKlikniety]=MojeNaDraw(numerNaWspolrzedne(przedPoprzedniKlikniety));
        dwspDane[wspolrzedneNaNumer(posredni)]=MojeNaDraw(posredni);
        narysuj();
        gtk_widget_queue_draw(plansza);
        czyAnimacja=0;
        return FALSE;
    }
    return TRUE;
}



int sprawdzPrzesuniecie(int nr){
    Nr=nr;
    if(nr==poprzedniKlikniety) return 0;///Sprawdzenie, czy gracz nie próbuje dokonać zerowego przesunięcia

     N=numerNaWspolrzedne(nr);
     poprzedni=numerNaWspolrzedne(poprzedniKlikniety);

    if(czySasiaduja(N, poprzedni)==0) return 0;///Warunek wykluczający przesuwanie o więcej niż jedno pole


    delta.x=N.x-poprzedni.x;
    delta.y=N.y-poprzedni.y;
    przedP=numerNaWspolrzedne(przedPoprzedniKlikniety);


    if(przedPoprzedniKlikniety==poprzedniKlikniety){ ///Przesuwanie pojedynczej kuli
        if( Dane[nr]==0){///Sprawdzenie czy pole na które chcemy przesunąć kulę jest puste
            //////////////////////////////////////////////////////////////////
            /**animacja dodana*/
            DWSP pop=MojeNaDraw(poprzedni);
            DWSP NR=MojeNaDraw(N);

            pozycja.x=(NR.x-pop.x)/20;
            pozycja.y=(NR.y-pop.y)/20;

            POPKLIK.x=pozycja.x+pop.x;
            POPKLIK.y=pozycja.y+pop.y;
            licznik=0;
            g_timeout_add(50, (GSourceFunc)funkcja, NULL);
            ///////////////////////////////////////////////////////////////////
            return 1;
        }
        else return 0;///Błąd: próba przesunięcia pojednczej kuli na niepuste pole
    }


    if(nr==przedPoprzedniKlikniety){/**Ujednolicenie kierunków:
     * gdy gracz próbuje przesunąć linię (z dwóch kul) równolegle do prostej którą linia wyznacza, ma dwa sposoby "wyklikania" ruchu.
     * Ten warunek sprowadza jeden ze sposobów do drugiego, co pozwala na niepisanie symetrycznych przypadków
     */
        przedPoprzedniKlikniety=poprzedniKlikniety;
        przedP=poprzedni;
        poprzedni=N;
        poprzedniKlikniety=nr;
        N.x=poprzedni.x+delta.x;
        N.y=poprzedni.y+delta.y;
        nr=wspolrzedneNaNumer(N);
        Nr=nr;

        if(pozaPlansza(N)==1) return 0;///Błąd: próba przesunięcia własnych kul poza planszę
    }



    if(przedP.x+delta.x==poprzedni.x && przedP.y+delta.y==poprzedni.y){///Przesuwanie dwóch kul równolegle do prostej wyznaczonej przez przesuwane kule

        if(Dane[nr]==0){///Sprawdzenie, czy pole do którego chcemy przesunąć linię jest puste
            //////////////////////////////////////////////////////////////////
            /**animacja dodana*/
            DWSP pop=MojeNaDraw(poprzedni);
            DWSP NR=MojeNaDraw(N);
            PPKLIK=MojeNaDraw(przedP);
            pozycja.x=(NR.x-pop.x)/20;
            pozycja.y=(NR.y-pop.y)/20;

            POPKLIK.x=pozycja.x+pop.x;
            POPKLIK.y=pozycja.y+pop.y;
            PPKLIK.x+=pozycja.x;
            PPKLIK.y+=pozycja.y;

            licznik=0;
            g_timeout_add(50, (GSourceFunc)funkcja2, NULL);

            ///////////////////////////////////////////////////////////////////

            return 1;
        }


        if(Dane[nr]==Dane[poprzedniKlikniety]) return 0;///Błąd: próba przepchnięcia własnch kul
        if(wersja==4 && ((Dane[poprzedniKlikniety]>2 && Dane[nr]>2 )|| (Dane[poprzedniKlikniety]<3 && Dane[nr]<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika


        if(Dane[nr]!=0){///Proba przepchnięcia kuli przeciwnika
            N.x+=delta.x;
            N.y+=delta.y;

            if(pozaPlansza(N)==0){///Sprawdzenie, czy za kulą przeciwnika znajduje się pole
                if(Dane[wspolrzedneNaNumer(N)]==0) {///Sprawdzenie, czy pole za kulą przeciwnika jest puste

                    //////////////////////////////////////////////////////////////////
                    /**animacja dodana*/
                    DWSP pop=MojeNaDraw(poprzedni);
                    DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                    PPKLIK=MojeNaDraw(przedP);
                    pozycja.x=(NR.x-pop.x)/20;
                    pozycja.y=(NR.y-pop.y)/20;
                    trzeci=MojeNaDraw(numerNaWspolrzedne(Nr));

                    trzeci.x+=pozycja.x;
                    trzeci.y+=pozycja.y;
                    POPKLIK.x=pozycja.x+pop.x;
                    POPKLIK.y=pozycja.y+pop.y;
                    PPKLIK.x+=pozycja.x;
                    PPKLIK.y+=pozycja.y;

                    licznik=0;
                    g_timeout_add(50, (GSourceFunc)funkcja3, NULL);

                    ///////////////////////////////////////////////////////////////////

                    return 1;
                }
                else return 0;///Błąd: próba przesunięcia dwoma kulami co najmniej dwóch kul
            }
            else{///Za kulą przeciwnika jest koniec planszy -> wypchnięto kulę przeciwnika, zmiana punktacji

                if(Kto==2) BialePunkty++;///Wypchnięto kulę przeciwnika, zmiana punktacji
                else if(Kto==1) CzarnePunkty++;
                else if(Kto==3) ZielonePunkty++;
                else CzerwonePunkty++;
                if(wersja==2)sprintf(pkt, "Punkty gracza białego: %d  Punkty gracza czarnego: %d", BialePunkty, CzarnePunkty);
                else if(wersja==3)sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);
                else sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, ZielonePunkty+CzerwonePunkty);
                gtk_label_set_text(GTK_LABEL(PKT), pkt);

                //////////////////////////////////////////////////////////////////
                /**animacja dodana*/
                DWSP pop=MojeNaDraw(poprzedni);
                DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                PPKLIK=MojeNaDraw(przedP);
                pozycja.x=(NR.x-pop.x)/20;
                pozycja.y=(NR.y-pop.y)/20;
                trzeci=MojeNaDraw(numerNaWspolrzedne(Nr));

                trzeci.x+=pozycja.x;
                trzeci.y+=pozycja.y;
                POPKLIK.x=pozycja.x+pop.x;
                POPKLIK.y=pozycja.y+pop.y;
                PPKLIK.x+=pozycja.x;
                PPKLIK.y+=pozycja.y;

                licznik=0;
                g_timeout_add(50, (GSourceFunc)funkcja4, NULL);

                ///////////////////////////////////////////////////////////////////

                return 1;
            }
        }
    }


    if(czySasiaduja(poprzedni, przedP)==1) {///Sprawdzenie, czy są przesuwane dwie kule
        N.x=przedP.x+delta.x;
        N.y=przedP.y+delta.y;

        if(pozaPlansza(N)==1) return 0;///Błąd: próba przesunięcia własnych kul poza planszę

        if(Dane[poprzedniKlikniety]!=Dane[przedPoprzedniKlikniety]) return 0;///Błąd: próba przesunięcia bokiem dwóch różnch kul

        if(Dane[nr]==0 && Dane[wspolrzedneNaNumer(N)]==0){///Sprawdzenie, czy docelowe pola są puste
            //////////////////////////////////////////////////////////////////
            /**animacja dodana*/
            DWSP pop=MojeNaDraw(poprzedni);
            DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
            PPKLIK=MojeNaDraw(przedP);
            pozycja.x=(NR.x-pop.x)/20;
            pozycja.y=(NR.y-pop.y)/20;
            POPKLIK.x=pozycja.x+pop.x;
            POPKLIK.y=pozycja.y+pop.y;
            PPKLIK.x+=pozycja.x;
            PPKLIK.y+=pozycja.y;

            licznik=0;
            g_timeout_add(50, (GSourceFunc)funkcja5, NULL);

            ///////////////////////////////////////////////////////////////////

            return 1;

        }
        else return 0;///Błąd: próba przesunięcia kul na niepuste pole
    }


    if(przedP.x==poprzedni.x+2*delta.x && przedP.y==poprzedni.y+2*delta.y){/**Ujednolicenie kierunków:
     * gdy gracz próbuje przesunąć linię (z trzech kul) równolegle do prostej którą linia wyznacza, ma dwa sposoby "wyklikania" ruchu.
     * Ten warunek sprowadza jeden ze sposobów do drugiego, co pozwala na niepisanie symetrycznych przypadków
     */
        przedP=poprzedni;
        przedPoprzedniKlikniety=poprzedniKlikniety;
        poprzedni.x+=2*delta.x;
        poprzedni.y+=2*delta.y;
        poprzedniKlikniety=wspolrzedneNaNumer(poprzedni);
        N.x=poprzedni.x+delta.x;
        N.y=poprzedni.y+delta.y;

        if(pozaPlansza(N)==1) return 0;///Błąd: próba przesunięcia własnch kul poza planszę
        nr=wspolrzedneNaNumer(N);
        Nr=nr;
    }

    posredni;
    posredni.x=(poprzedni.x+przedP.x)/2;
    posredni.y=(poprzedni.y+przedP.y)/2;


    if(przedP.x==poprzedni.x-2*delta.x && przedP.y==poprzedni.y-2*delta.y){///Przesuwanie trzech kul równolegle do wyznaczonej przez nie prostej

        if(Dane[nr]==0){///Sprawdzenie, czy pole do którego chcemy przesunąć linię jest puste
            //////////////////////////////////////////////////////////////////
            /**animacja dodana*/
            DWSP pop=MojeNaDraw(poprzedni);
            DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
            PPKLIK=MojeNaDraw(przedP);
            pozycja.x=(NR.x-pop.x)/20;
            pozycja.y=(NR.y-pop.y)/20;
            trzeci=MojeNaDraw(poprzedni);
            POPKLIK=MojeNaDraw(posredni);

            trzeci.x+=pozycja.x;
            trzeci.y+=pozycja.y;
            POPKLIK.x+=pozycja.x;
            POPKLIK.y+=pozycja.y;
            PPKLIK.x+=pozycja.x;
            PPKLIK.y+=pozycja.y;

            licznik=0;
            g_timeout_add(50, (GSourceFunc)funkcja6, NULL);

            ///////////////////////////////////////////////////////////////////
            return 1;
        }

        if(Dane[nr]==Dane[poprzedniKlikniety]) return 0;///Błąd: próba przepchnięcia własnch kul
        if(wersja==4 && ((Dane[poprzedniKlikniety]>2 && Dane[nr]>2 )|| (Dane[poprzedniKlikniety]<3 && Dane[nr]<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika

        if(Dane[nr]!=0){///Próba przepchnięcia kul przeciwnika
            N1.x=N.x+delta.x;
            N1.y=N.y+delta.y;
            N2.x=N.x+2*delta.x;
            N2.y=N.y+2*delta.y;

            if(pozaPlansza(N1)==1){///Sprawdzenie, czy za kulą przeciwnika jest koniec planszy
                //////////////////////////////////////////////////////////////////
                /**animacja dodana*/
                DWSP pop=MojeNaDraw(poprzedni);
                DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                PPKLIK=MojeNaDraw(przedP);
                pozycja.x=(NR.x-pop.x)/20;
                pozycja.y=(NR.y-pop.y)/20;
                trzeci=MojeNaDraw(poprzedni);
                POPKLIK=MojeNaDraw(posredni);
                czwarty=MojeNaDraw(N);


                czwarty.x+=pozycja.x;
                czwarty.y+=pozycja.y;
                trzeci.x+=pozycja.x;
                trzeci.y+=pozycja.y;
                POPKLIK.x+=pozycja.x;
                POPKLIK.y+=pozycja.y;
                PPKLIK.x+=pozycja.x;
                PPKLIK.y+=pozycja.y;

                licznik=0;
                g_timeout_add(50, (GSourceFunc)funkcja7, NULL);

                ///////////////////////////////////////////////////////////////////


                if(Kto==2) BialePunkty++;///Wypchnięto kulę przeciwnika, zmiana punktacji
                else if(Kto==1) CzarnePunkty++;
                else if(Kto==3)ZielonePunkty++;
                else CzerwonePunkty++;
                if(wersja==2)sprintf(pkt, "Punkty gracza białego: %d  Punkty gracza czarnego: %d", BialePunkty, CzarnePunkty);
                else if(wersja==3)sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);
                else sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, ZielonePunkty+CzerwonePunkty);
                gtk_label_set_text(GTK_LABEL(PKT), pkt);


                return 1;
            }


            if(Dane[wspolrzedneNaNumer(N1)]==0){///Sprawdzenie, czy za kulą przeciwnika jest puste pole, przepchnięcie jednej kuli
                //////////////////////////////////////////////////////////////////
                /**animacja dodana*/
                DWSP pop=MojeNaDraw(poprzedni);
                DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                PPKLIK=MojeNaDraw(przedP);
                pozycja.x=(NR.x-pop.x)/20;
                pozycja.y=(NR.y-pop.y)/20;
                trzeci=MojeNaDraw(poprzedni);
                POPKLIK=MojeNaDraw(posredni);
                czwarty=MojeNaDraw(N);


                czwarty.x+=pozycja.x;
                czwarty.y+=pozycja.y;
                trzeci.x+=pozycja.x;
                trzeci.y+=pozycja.y;
                POPKLIK.x+=pozycja.x;
                POPKLIK.y+=pozycja.y;
                PPKLIK.x+=pozycja.x;
                PPKLIK.y+=pozycja.y;

                licznik=0;
                g_timeout_add(50, (GSourceFunc)funkcja8, NULL);

                ///////////////////////////////////////////////////////////////////

                return 1;
            }


            if(Dane[wspolrzedneNaNumer(N1)]==Dane[poprzedniKlikniety]) return 0;///Błąd: próba przepchnięcia własnej kuli kulą przeciwnika
            if(wersja==4 && ((Dane[poprzedniKlikniety]>2 && Dane[wspolrzedneNaNumer(N1)]>2 )|| (Dane[poprzedniKlikniety]<3 && Dane[wspolrzedneNaNumer(N1)]<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika


            if(pozaPlansza(N2)==1){///Sprawdzenie, czy za dwiema kulami przeciwnika jest koniec planszy

                //////////////////////////////////////////////////////////////////
                /**animacja dodana*/
                DWSP pop=MojeNaDraw(poprzedni);
                DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                PPKLIK=MojeNaDraw(przedP);
                pozycja.x=(NR.x-pop.x)/20;
                pozycja.y=(NR.y-pop.y)/20;
                trzeci=MojeNaDraw(poprzedni);
                POPKLIK=MojeNaDraw(posredni);
                czwarty=MojeNaDraw(N);
                piaty=MojeNaDraw(N1);

                piaty.x+=pozycja.x;
                piaty.y+=pozycja.y;
                czwarty.x+=pozycja.x;
                czwarty.y+=pozycja.y;
                trzeci.x+=pozycja.x;
                trzeci.y+=pozycja.y;
                POPKLIK.x+=pozycja.x;
                POPKLIK.y+=pozycja.y;
                PPKLIK.x+=pozycja.x;
                PPKLIK.y+=pozycja.y;

                licznik=0;
                g_timeout_add(50, (GSourceFunc)funkcja9, NULL);

                ///////////////////////////////////////////////////////////////////
                if(Kto==2) BialePunkty++;///Wypchnięcie kuli przeciwnika, zmiana punktacji
                else if(Kto==1) CzarnePunkty++;
                else if(Kto==3)ZielonePunkty++;
                else CzerwonePunkty++;
                if(wersja==2)sprintf(pkt, "Punkty gracza białego: %d  Punkty gracza czarnego: %d", BialePunkty, CzarnePunkty);
                else if(wersja==3)sprintf(pkt, "Biały: %d pkt  Zielony: %d pkt Czarny: %d pkt", BialePunkty, ZielonePunkty, CzarnePunkty);
                else sprintf(pkt, "CzarnoBiali: %d pkt  ZielonoCzerwoni: %d pkt", BialePunkty+CzarnePunkty, ZielonePunkty+CzerwonePunkty);
                gtk_label_set_text(GTK_LABEL(PKT), pkt);
                return 1;
            }

            if(Dane[wspolrzedneNaNumer(N2)]==0){///Sprawdzenie cz za kulami przeciwnika jest puste pole, przepchnięcie dwóch kul
                //////////////////////////////////////////////////////////////////
                /**animacja dodana*/
                DWSP pop=MojeNaDraw(poprzedni);
                DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
                PPKLIK=MojeNaDraw(przedP);
                pozycja.x=(NR.x-pop.x)/20;
                pozycja.y=(NR.y-pop.y)/20;
                trzeci=MojeNaDraw(poprzedni);
                POPKLIK=MojeNaDraw(posredni);
                czwarty=MojeNaDraw(N);
                piaty=MojeNaDraw(N1);

                piaty.x+=pozycja.x;
                piaty.y+=pozycja.y;
                czwarty.x+=pozycja.x;
                czwarty.y+=pozycja.y;
                trzeci.x+=pozycja.x;
                trzeci.y+=pozycja.y;
                POPKLIK.x+=pozycja.x;
                POPKLIK.y+=pozycja.y;
                PPKLIK.x+=pozycja.x;
                PPKLIK.y+=pozycja.y;

                licznik=0;
                g_timeout_add(50, (GSourceFunc)funkcja10, NULL);

                ///////////////////////////////////////////////////////////////////

                return 1;
            }
        }

    }

    else{///Próba przesunięcia trzech kul w bok
        N1.x=przedP.x+delta.x;
        N1.y=przedP.y+delta.y;
        N2.x=posredni.x+delta.x;
        N2.y=posredni.y+delta.y;

        if(pozaPlansza(N1)==1 || pozaPlansza(N2)==1) return 0;///Błąd: próba wypchnięcia własnch kul poza planszę

        if(Dane[poprzedniKlikniety]!=Dane[przedPoprzedniKlikniety] || Dane[poprzedniKlikniety]!=Dane[wspolrzedneNaNumer(posredni)])return  0;///Błąd: próba przesunięcia bokiem 3 kul niejednakowego koloru

        if(Dane[nr]==0 && Dane[wspolrzedneNaNumer(N1)]==0 && Dane[wspolrzedneNaNumer(N2)]==0){///Sprawdzenie, czy docelowe pola są puste
            //////////////////////////////////////////////////////////////////
            /**animacja dodana*/
            DWSP pop=MojeNaDraw(poprzedni);
            DWSP NR=MojeNaDraw(numerNaWspolrzedne(Nr));
            PPKLIK=MojeNaDraw(przedP);
            pozycja.x=(NR.x-pop.x)/20;
            pozycja.y=(NR.y-pop.y)/20;
            trzeci=MojeNaDraw(poprzedni);
            POPKLIK=MojeNaDraw(posredni);
            trzeci.x+=pozycja.x;
            trzeci.y+=pozycja.y;
            POPKLIK.x+=pozycja.x;
            POPKLIK.y+=pozycja.y;
            PPKLIK.x+=pozycja.x;
            PPKLIK.y+=pozycja.y;

            licznik=0;
            g_timeout_add(50, (GSourceFunc)funkcja11, NULL);

            ///////////////////////////////////////////////////////////////////
            return  1;
        }
        else return 0;///Błąd: próba przesunięcia kul na niepuste pola
    }
    return 0;
}

void sprawdzPoczatekLinii(int nr){
    if(Dane[nr]==0){///Błąd: próba przesunięcia pustego pola
        sprintf(t, "Nie można przesuwać pustego pola. Proszę podać początek przesuwanej linii");
        gtk_label_set_text(GTK_LABEL(info),t);
    }
    else if(Dane[nr]!=Kto) {///Błąd: próba przesunięcia kul przeciwnika
        sprintf(t, "Łapy precz od kul przeciwnika! Początek SWOJEJ linii!");
        gtk_label_set_text(GTK_LABEL(info),t);
    }
    else{///Poprawnie podany początek przesuwanej linii
        sprintf(t, "Proszę podać drugi koniec przesuwanej linii");
        gtk_label_set_text(GTK_LABEL(info),t);
        ileKliknietych=1;
        przedPoprzedniKlikniety=nr;
    }
}

void sprawdzKoniecLinii(int nr){
    poprzedniKlikniety=nr;
    if(czyDobryKoniec(przedPoprzedniKlikniety,  poprzedniKlikniety)>0){///Poprawny koniec linii
        sprintf(t, "Proszę podać kierunek od końca linii");
        gtk_label_set_text(GTK_LABEL(info),t);
        ileKliknietych=2;
    }
    else{///Źle podany koniec linii, gracz jest zmuszony do rozpoczęcia ruchu od nowa
        sprintf(t, "Źle podany koniec linii. Proszę podać początek przesuwanej linii");
        gtk_label_set_text(GTK_LABEL(info),t);
        ileKliknietych=0;
    }
}