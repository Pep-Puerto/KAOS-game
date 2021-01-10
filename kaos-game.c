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


void    _wait_for(int n);
void    _init_aleat();
int    _aleat(int N);
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
        case KeyPress:    break;
        default:    break;
    }
   }
   XCloseDisplay(foli);
   return 0;
}

int kaos( Display *foli, Window finestra, GC gc, int x_0, int y_0, unsigned int width, unsigned int height){
int x, y;
int i;
int punt;
t_punt POLIGON[3];
int N;

 x = x_0;
 y = y_0;
 N = 2;

 POLIGON[0].x = width / 2;
 POLIGON[0].y = 0;
 XFillRectangle(foli, finestra, gc, POLIGON[0].x, POLIGON[0].y, 4, 4);

 POLIGON[1].x = 0;
 POLIGON[1].y = height;
 XFillRectangle(foli, finestra, gc, POLIGON[1].x, POLIGON[1].y, 4, 4);

 POLIGON[2].x = width;
 POLIGON[2].y = height;
 XFillRectangle(foli, finestra, gc, POLIGON[2].x, POLIGON[2].y, 4, 4);

 for ( i = 0; i < 10000000; i++ ) {
    _wait_for(50000);
    XFillRectangle(foli, finestra, gc, x, y, 1, 1);
    punt = _aleat(3);
        x = x + (POLIGON[punt].x - x) / N;
        y = y + (POLIGON[punt].y - y) / N;
 }
}

void    _init_aleat(){srand(time(NULL));}
int    _aleat(int N){return rand()%N;}
void    _wait_for(int n){for ( int i = 0; i < n; i++ );}
