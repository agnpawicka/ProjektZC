/**@author Agnieszka Pawicka
* @file WspolneFunkcjeRoznchWersji.c */

#include "WspolneFunkcjeRoznchWersji.h"

int czySasiaduja(WSP a, WSP b){
    if(a.x==b.x && (a.y==b.y+1 || a.y+1==b.y) ) return 1;
    if(a.y==b.y  && (a.x==b.x+1 ||a.x+1==b.x)) return 1;
    if(a.x-b.x==a.y-b.y && (a.x==b.x+1 ||a.x+1==b.x))return 1;
    return 0;///nie sąsiadują
}

int pozaPlansza(WSP N){
    if((N.x>=0 && N.x<5 && N.y>=0 && N.y<N.x+5) ||(N.x>=5 && N.x<9 && N.y>=N.x-4 && N.y<9)) return 0;
    return 1;///N jest poza planszą
}

int czyDobryKoniec(int a, int b){
    if(wersja==4){///Wersja czteroosobowa, kolory sojusznicze dopuszczalne
        if((Dane[a]>2 && Dane[b]<3) || (Dane[a]<3 && Dane[b]>2)) return 0;///wrogi kolor

        WSP A=numerNaWspolrzedne(a);
        WSP B=numerNaWspolrzedne(b);

        if(czySasiaduja(A, B)==1) return 1;

        WSP posredni;

        if(A.x==B.x){
            if(A.y==B.y) return 1;
            posredni.x=A.x;
            posredni.y=B.y+1;
            if(A.y==B.y+2 && (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b])) return  1;
            posredni.y=A.y+1;
            if(A.y+2==B.y && (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b])) return  1;
        }

        if(A.y==B.y){
            posredni.x=A.x+1;
            posredni.y=B.y;
            if(A.x+2==B.x && (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b])) return 1;
            posredni.x=B.x+1;
            if(A.x==B.x+2 && (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b])) return 1;
        }

        posredni.x=A.x+1;
        posredni.y=A.y+1;
        if((A.x+2==B.x && A.y+2==B.y) &&  (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b]) ) return 1;
        posredni.x=B.x+1;
        posredni.y=B.y+1;
        if((A.x==B.x+2 && A.y==B.y+2) && (Dane[wspolrzedneNaNumer(posredni)]==Dane[a] || Dane[wspolrzedneNaNumer(posredni)]==Dane[b])  ) return 1;
        return 0;
    }
    /**Pozostałe wersje gry*/
    if(Dane[a]!=Dane[b]) return 0;///inny kolor

    WSP A=numerNaWspolrzedne(a);
    WSP B=numerNaWspolrzedne(b);
    if(czySasiaduja(A, B)==1) return 1;
    WSP posredni;

    if(A.x==B.x){
        if(A.y==B.y) return 1;
        posredni.x=A.x;
        posredni.y=B.y+1;
        if(A.y==B.y+2 && Dane[wspolrzedneNaNumer(posredni)]==Dane[a]) return  1;
        posredni.y=A.y+1;
        if(A.y+2==B.y && Dane[wspolrzedneNaNumer(posredni)]==Dane[a]) return  1;
    }

    if(A.y==B.y){
        posredni.x=A.x+1;
        posredni.y=B.y;
        if(A.x+2==B.x && Dane[wspolrzedneNaNumer(posredni)]==Dane[a]) return 1;
        posredni.x=B.x+1;
        if(A.x==B.x+2 && Dane[wspolrzedneNaNumer(posredni)]==Dane[a]) return 1;
    }

    posredni.x=A.x+1;
    posredni.y=A.y+1;
    if((A.x+2==B.x && A.y+2==B.y) &&  Dane[wspolrzedneNaNumer(posredni)]==Dane[a] ) return 1;
    posredni.x=B.x+1;
    posredni.y=B.y+1;
    if((A.x==B.x+2 && A.y==B.y+2) && Dane[wspolrzedneNaNumer(posredni)]==Dane[a]  ) return 1;
    return 0;
}

void zmianaKoloru(int nr, int kolor){
    Dane[nr]=kolor;
}

void narysuj(){
    cairo_t *cr;
    cr = cairo_create(surface);

    cairo_set_source_rgba(cr, 0.2, 0.6, 0.623, 1);
    cairo_paint(cr);

    for(int i=0; i<61; i++){ ;
        cairo_set_source_surface(cr, obraz[Dane[i]], dwspDane[i].x, dwspDane[i].y);
        cairo_paint(cr);
        dwspDane[i]=MojeNaDraw(numerNaWspolrzedne(i));
    }
}
