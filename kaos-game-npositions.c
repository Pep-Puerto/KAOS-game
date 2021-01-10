#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W_W 1000
#define H_W 1000

typedef struct punt{
    int x;
    int y;
} t_punt;


void _wait_for(int n);
void _init_aleat();
int _aleat(int N);
int _aleat_diff(int N, int vertex);
int _nplaces_away_from_vertex(int vertex, int n_places, int N);
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
int vertex, next_vertex;
t_punt POLIGON[4], punt;
int N;

 punt.x = x_0;
 punt.y = y_0;
 N = 2;


 //Vertex 0
 POLIGON[0].x = 0;
 POLIGON[0].y = 0;
 XFillRectangle(foli, finestra, gc, POLIGON[0].x, POLIGON[0].y, 4, 4);

 //Vertex 1
 POLIGON[1].x = 0;
 POLIGON[1].y = height;
 XFillRectangle(foli, finestra, gc, POLIGON[1].x, POLIGON[1].y, 4, 4);

 //Vertex 2
 POLIGON[2].x = width;
 POLIGON[2].y = 0;
 XFillRectangle(foli, finestra, gc, POLIGON[2].x, POLIGON[2].y, 4, 4);

 //Vertex 3
 POLIGON[3].x = width;
 POLIGON[3].y = height;
 XFillRectangle(foli, finestra, gc, POLIGON[3].x, POLIGON[3].y, 4, 4);
  
 vertex = _aleat(4);
 for ( i = 0; i < 10000000; i++ ) {
    _wait_for(100);
    XFillRectangle(foli, finestra, gc, punt.x, punt.y, 1, 1);
    vertex = _aleat_diff(4, _nplaces_away_from_vertex(vertex, 2, 4));
    punt.x = punt.x + (POLIGON[vertex].x - punt.x) / N;
    punt.y = punt.y + (POLIGON[vertex].y - punt.y) / N;
 }
}

void    _init_aleat(){srand(time(NULL));}
int    _aleat(int N){return rand()%N;}
void    _wait_for(int n){int i; for ( i = 0; i < n; i++ );}
int    _aleat_diff(int N, int vertex){
        int v;
        v = _aleat(N);
        while ( v == vertex ) v = _aleat(N);
        return v;
 }
int _nplaces_away_from_vertex(int vertex, int n_places, int N){return ( (vertex + n_places) % N );}