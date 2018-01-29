/**@author Agnieszka Pawicka
* @file sprawdzaniePrzesuniec.c */

#include "sprawdzaniePrzesuniec.h"

int sprawdzPrzesuniecie(int nr){
    if(nr==poprzedniKlikniety) return 0;///Sprawdzenie, czy gracz nie próbuje dokonać zerowego przesunięcia

    WSP N=numerNaWspolrzedne(nr);
    WSP poprzedni=numerNaWspolrzedne(poprzedniKlikniety);

    if(czySasiaduja(N, poprzedni)==0) return 0;///Warunek wykluczający przesuwanie o więcej niż jedno pole

    WSP delta;/**@var delta - przechowuje różnicę pomiędzy kierunkiem przesunięcia a końcem linii (a dokładniej między ich współrzędnymi) */
    delta.x=N.x-poprzedni.x;
    delta.y=N.y-poprzedni.y;
    WSP przedP=numerNaWspolrzedne(przedPoprzedniKlikniety);


    if(przedPoprzedniKlikniety==poprzedniKlikniety){ ///Przesuwanie pojedynczej kuli
        if( DANE[nr].kolor==0){///Sprawdzenie czy pole na które chcemy przesunąć kulę jest puste
            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, 0);
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

        if(pozaPlansza(N)==1) return 0;///Błąd: próba przesunięcia własnych kul poza planszę
    }



    if(przedP.x+delta.x==poprzedni.x && przedP.y+delta.y==poprzedni.y){///Przesuwanie dwóch kul równolegle do prostej wyznaczonej przez przesuwane kule

        if(DANE[nr].kolor==0){///Sprawdzenie, czy pole do którego chcemy przesunąć linię jest puste
            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, DANE[przedPoprzedniKlikniety].kolor);
            zmianaKoloru(przedPoprzedniKlikniety, 0);
            return 1;
        }


        if(DANE[nr].kolor==DANE[poprzedniKlikniety].kolor) return 0;///Błąd: próba przepchnięcia własnch kul
        if(wersja==4 && ((DANE[poprzedniKlikniety].kolor>2 && DANE[nr].kolor>2 )|| (DANE[poprzedniKlikniety].kolor<3 && DANE[nr].kolor<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika


        if(DANE[nr].kolor!=0){///Proba przepchnięcia kuli przeciwnika
            N.x+=delta.x;
            N.y+=delta.y;

            if(pozaPlansza(N)==0){///Sprawdzenie, czy za kulą przeciwnika znajduje się pole
                if(DANE[wspolrzedneNaNumer(N)].kolor==0) {///Sprawdzenie, czy pole za kulą przeciwnika jest puste
                    zmianaKoloru(wspolrzedneNaNumer(N), DANE[nr].kolor);
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

            }

            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, DANE[przedPoprzedniKlikniety].kolor);
            zmianaKoloru(przedPoprzedniKlikniety, 0);
            return 1;
        }
    }


    if(czySasiaduja(poprzedni, przedP)==1) {///Sprawdzenie, czy są przesuwane dwie kule
        N.x=przedP.x+delta.x;
        N.y=przedP.y+delta.y;

        if(pozaPlansza(N)==1) return 0;///Błąd: próba przesunięcia własnych kul poza planszę

        if(DANE[poprzedniKlikniety].kolor!=DANE[przedPoprzedniKlikniety].kolor) return 0;///Błąd: próba przesunięcia bokiem dwóch różnch kul

        if(DANE[nr].kolor==0 && DANE[wspolrzedneNaNumer(N)].kolor==0){///Sprawdzenie, czy docelowe pola są puste

            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, 0);
            zmianaKoloru(wspolrzedneNaNumer(N), DANE[przedPoprzedniKlikniety].kolor);
            zmianaKoloru(przedPoprzedniKlikniety, 0);
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
    }

    WSP posredni;
    posredni.x=(poprzedni.x+przedP.x)/2;
    posredni.y=(poprzedni.y+przedP.y)/2;


    if(przedP.x==poprzedni.x-2*delta.x && przedP.y==poprzedni.y-2*delta.y){///Przesuwanie trzech kul równolegle do wyznaczonej przez nie prostej

        if(DANE[nr].kolor==0){///Sprawdzenie, czy pole do którego chcemy przesunąć linię jest puste
            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, DANE[wspolrzedneNaNumer(posredni)].kolor);
            zmianaKoloru(wspolrzedneNaNumer(posredni), DANE[przedPoprzedniKlikniety].kolor);
            zmianaKoloru(przedPoprzedniKlikniety, 0);
            return 1;
        }

        if(DANE[nr].kolor==DANE[poprzedniKlikniety].kolor) return 0;///Błąd: próba przepchnięcia własnch kul
        if(wersja==4 && ((DANE[poprzedniKlikniety].kolor>2 && DANE[nr].kolor>2 )|| (DANE[poprzedniKlikniety].kolor<3 && DANE[nr].kolor<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika

        if(DANE[nr].kolor!=0){///Próba przepchnięcia kul przeciwnika
            WSP N1;
            WSP N2;
            N1.x=N.x+delta.x;
            N1.y=N.y+delta.y;
            N2.x=N.x+2*delta.x;
            N2.y=N.y+2*delta.y;

            if(pozaPlansza(N1)==1){///Sprawdzenie, czy za kulą przeciwnika jest koniec planszy

                zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
                zmianaKoloru(poprzedniKlikniety, DANE[wspolrzedneNaNumer(posredni)].kolor);
                zmianaKoloru(wspolrzedneNaNumer(posredni), DANE[przedPoprzedniKlikniety].kolor);
                zmianaKoloru(przedPoprzedniKlikniety, 0);

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


            if(DANE[wspolrzedneNaNumer(N1)].kolor==0){///Sprawdzenie, czy za kulą przeciwnika jest puste pole, przepchnięcie jednej kuli
                zmianaKoloru(wspolrzedneNaNumer(N1), DANE[nr].kolor);
                zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
                zmianaKoloru(poprzedniKlikniety, DANE[wspolrzedneNaNumer(posredni)].kolor);
                zmianaKoloru(wspolrzedneNaNumer(posredni), DANE[przedPoprzedniKlikniety].kolor);
                zmianaKoloru(przedPoprzedniKlikniety, 0);
                return 1;
            }


            if(DANE[wspolrzedneNaNumer(N1)].kolor==DANE[poprzedniKlikniety].kolor) return 0;///Błąd: próba przepchnięcia własnej kuli kulą przeciwnika
            if(wersja==4 && ((DANE[poprzedniKlikniety].kolor>2 && DANE[wspolrzedneNaNumer(N1)].kolor>2 )|| (DANE[poprzedniKlikniety].kolor<3 && DANE[wspolrzedneNaNumer(N1)].kolor<3))) return 0;///Błąd: próba przepchnięcia kul własnych lub sojusznika


            if(pozaPlansza(N2)==1){///Sprawdzenie, czy za dwiema kulami przeciwnika jest koniec planszy
                zmianaKoloru(wspolrzedneNaNumer(N1), DANE[nr].kolor);
                zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
                zmianaKoloru(poprzedniKlikniety, DANE[wspolrzedneNaNumer(posredni)].kolor);
                zmianaKoloru(wspolrzedneNaNumer(posredni), DANE[przedPoprzedniKlikniety].kolor);
                zmianaKoloru(przedPoprzedniKlikniety, 0);

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

            if(DANE[wspolrzedneNaNumer(N2)].kolor==0){///Sprawdzenie cz za kulami przeciwnika jest puste pole, przepchnięcie dwóch kul
                zmianaKoloru(wspolrzedneNaNumer(N2), DANE[wspolrzedneNaNumer(N1)].kolor);
                zmianaKoloru(wspolrzedneNaNumer(N1), DANE[nr].kolor);
                zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
                zmianaKoloru(poprzedniKlikniety, DANE[wspolrzedneNaNumer(posredni)].kolor);
                zmianaKoloru(wspolrzedneNaNumer(posredni), DANE[przedPoprzedniKlikniety].kolor);
                zmianaKoloru(przedPoprzedniKlikniety, 0);
                return 1;
            }
        }

    }

    else{///Próba przesunięcia trzech kul w bok
        WSP N1;
        WSP N2;
        N1.x=przedP.x+delta.x;
        N1.y=przedP.y+delta.y;
        N2.x=posredni.x+delta.x;
        N2.y=posredni.y+delta.y;

        if(pozaPlansza(N1)==1 || pozaPlansza(N2)==1) return 0;///Błąd: próba wypchnięcia własnch kul poza planszę

        if(DANE[poprzedniKlikniety].kolor!=DANE[przedPoprzedniKlikniety].kolor || DANE[poprzedniKlikniety].kolor!=DANE[wspolrzedneNaNumer(posredni)].kolor)return  0;///Błąd: próba przesunięcia bokiem 3 kul niejednakowego koloru

        if(DANE[nr].kolor==0 && DANE[wspolrzedneNaNumer(N1)].kolor==0 && DANE[wspolrzedneNaNumer(N2)].kolor==0){///Sprawdzenie, czy docelowe pola są puste
            zmianaKoloru(wspolrzedneNaNumer(N1), DANE[przedPoprzedniKlikniety].kolor);
            zmianaKoloru(wspolrzedneNaNumer(N2), DANE[wspolrzedneNaNumer(posredni)].kolor);
            zmianaKoloru(nr, DANE[poprzedniKlikniety].kolor);
            zmianaKoloru(poprzedniKlikniety, 0);
            zmianaKoloru(przedPoprzedniKlikniety, 0);
            zmianaKoloru(wspolrzedneNaNumer(posredni), 0);
            return  1;
        }
        else return 0;///Błąd: próba przesunięcia kul na niepuste pola
    }
    return 0;
}

void sprawdzPoczatekLinii(int nr){
    if(DANE[nr].kolor==0){///Błąd: próba przesunięcia pustego pola
        sprintf(t, "Nie można przesuwać pustego pola. Proszę podać początek przesuwanej linii");
        gtk_label_set_text(GTK_LABEL(info),t);
    }
    else if(DANE[nr].kolor!=Kto) {///Błąd: próba przesunięcia kul przeciwnika
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