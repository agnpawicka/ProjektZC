/**@file zmianyNotacjiIObrazow.c
 * @headerfile zmianyNotacjiIObrazow.h
 * Dokumentacja funkcji w pliku zmianyNotacjiIObrazow.h*/
#include "zmianyNotacjiIObrazow.h"

void zainicjalizujObrazki(){
	DIR* dir = opendir("Obrazki");
	if(dir){
		obrazki[0]="Obrazki/szare.png";
		obrazki[1]="Obrazki/czarnemale.png";
		obrazki[2]="Obrazki/bialemale.png";
		obrazki[3]="Obrazki/zielonemale.png";
		obrazki[4]="Obrazki/czerwonemale.png";
	}else{
		obrazki[0]="../Obrazki/szare.png";
		obrazki[1]="../Obrazki/czarnemale.png";
		obrazki[2]="../Obrazki/bialemale.png";
		obrazki[3]="../Obrazki/zielonemale.png";
		obrazki[4]="../Obrazki/czerwonemale.png";
	}
}
WSP numerNaWspolrzedne(int nr){
    WSP wsp;
    if(nr<5){
        wsp.x=0;
        wsp.y=nr;
        return  wsp;
    }
    if(nr<11){
        wsp.x=1;
        wsp.y=nr-5;
        return wsp;
    }
    if(nr<18){
        wsp.x=2;
        wsp.y=nr-11;
        return  wsp;
    }
    if(nr<26){
        wsp.x=3;
        wsp.y=nr-18;
        return  wsp;
    }
    if(nr<35){
        wsp.x=4;
        wsp.y=nr-26;
        return  wsp;
    }
    if(nr<43){
        wsp.x=5;
        wsp.y=nr-35+1;
        return  wsp;
    }
    if(nr<50){
        wsp.x=6;
        wsp.y=nr-43+2;
        return  wsp;
    }
    if(nr<56){
        wsp.x=7;
        wsp.y=nr-50+3;
        return  wsp;
    }
    if(nr<61){
        wsp.x=8;
        wsp.y=nr-56+4;
        return  wsp;
    }
}

int wspolrzedneNaNumer(WSP wsp){
    int numer=0;
    switch (wsp.x){
        case 0:
            break;
        case 1:
            numer+=5;
            break;
        case 2:
            numer+=11;
            break;
        case 3:
            numer+=18;
            break;
        case 4:
            numer+=26;
            break;
        case 5:
            numer+=35;
            break;
        case 6:
            numer+=43;
            break;
        case 7:
            numer+=50;
            break;
        case 8:
            numer+=56;
            break;
        default:
            break;
    }
    if(wsp.x<=4)numer+=wsp.y;
    else numer+=wsp.y-(wsp.x-4);
    return numer;
}

void Zmien(GtkWidget *guzik, GtkWidget *obraz, int *naJakiKolor){
    gtk_container_remove(GTK_CONTAINER(guzik), obraz);
    switch(*naJakiKolor){
        case 0:
            obraz=gtk_image_new_from_file(obrazki[0]);
            break;
        case 1:
            obraz=gtk_image_new_from_file(obrazki[1]);
            break;
        case 2:
            obraz=gtk_image_new_from_file(obrazki[2]);
            break;
        case 3:
            obraz=gtk_image_new_from_file(obrazki[3]);
            break;
        case 4:
            obraz=gtk_image_new_from_file(obrazki[4]);
            break;
        default:
            break;
    }
    gtk_container_add(GTK_CONTAINER(guzik), obraz);
    gtk_widget_show(obraz);
}
