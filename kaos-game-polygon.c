#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Screen dimension in pixels
#define W_W 1000
#define H_W 1000

//Polygon type and radius dimension
#define N_POL 3
#define RADI ( H_W / 2 )

//Predefined operation, divide by 2
#define DIV 2

//N_PLACES 0:Next vertex selected not the same vertex, 1:Not the next vertex in order, and so on ...
#define N_PLACES 0
//Cancel N_PLACES. If ALL is 1, all vertex is possible selected. If ALL is 0, acts N_PLACES.
#define ALL 1

typedef struct punt{
    int x;
    int y;
} t_punt;


void    _wait_for(int n);
void    _init_aleat();
int    _aleat(int n);
int    _aleat_diff(int n_pol, int vertex);
int    _nplaces_away_from_vertex(int vertex, int n_places, int n_pol);
int     _genera_poligon(t_punt POLIGON[], int n, int r);
int     kaos( Display *foli, Window finestra, GC gc, int x, int y, unsigned int width, unsigned int height);

 
int main(void) {
   Display *foli;
   Window finestra;
   XEvent event;
   int id_foli;
   int x, y;
 
   foli = XOpenDisplay(NULL);
   if (foli == NULL) {fprintf(stderr, "No puc crear la zona de dibuix \n"); exit(1);}
 
   id_foli = XDefaultScreen(foli);
   finestra = XCreateSimpleWindow(foli, RootWindow(foli, id_foli), 10, 10, W_W, H_W, 1, BlackPixel(foli, id_foli), WhitePixel(foli, id_foli));
   XSelectInput(foli, finestra, ExposureMask | KeyPressMask);
   XMapWindow(foli, finestra);
 
   _init_aleat();
   x = _aleat(W_W);
   y = _aleat(H_W);
   while (1) {
    XNextEvent(foli, &event);
    switch(event.type){
        case Expose:    kaos(foli, finestra, DefaultGC(foli, id_foli), x, y, W_W, H_W);
                        break;
        case KeyPress:  break;
        default:        break;
    }
   }
   XCloseDisplay(foli);
   return 0;
}

int kaos( Display *foli, Window finestra, GC gc, int x_0, int y_0, unsigned int width, unsigned int height){
int i;
int vertex;
t_punt POLIGON[N_POL], punt;

 punt.x = x_0;
 punt.y = y_0;

 //Constructing and painting the polygon
 _genera_poligon(POLIGON, N_POL, RADI);
 for ( i = 0; i < N_POL; i++ )  XFillRectangle(foli, finestra, gc, POLIGON[i].x, POLIGON[i].y, 4, 4);

 vertex = _aleat(N_POL);
 for ( i = 0; i < 10000000; i++ ) {
    _wait_for(100);
    XFillRectangle(foli, finestra, gc, punt.x, punt.y, 1, 1);
    switch ( ALL ){
        case 1: vertex = _aleat( N_POL );
                break;
        case 0: vertex = _aleat_diff(N_POL, _nplaces_away_from_vertex(vertex, N_PLACES, N_POL));
                break;
        default:break;
    }
    punt.x = punt.x + (POLIGON[vertex].x - punt.x) / DIV;
    punt.y = punt.y + (POLIGON[vertex].y - punt.y) / DIV;
 }
}

void    _init_aleat(){srand(time(NULL));}
int    _aleat(int n){return rand() % n;}
void    _wait_for(int n){int i; for ( i = 0; i < n; i++ );}

int    _aleat_diff(int n_pol, int vertex){
        int v;
        v = _aleat(n_pol);
        while ( v == vertex ) v = _aleat(N_POL);
        return v;
 }

int _nplaces_away_from_vertex(int vertex, int n_places, int n_pol){return ( (vertex + n_places) % n_pol );}
int _genera_poligon(t_punt POLIGON[], int n, int r){
int i;
for (i = 0; i < n; i++) {
    POLIGON[i].x = (int)(r - r * sinf(2 * M_PI * i / n));
    POLIGON[i].y = (int)(r - r * cosf(2 * M_PI * i / n));
}
}