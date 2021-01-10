//https://wiki.libsdl.org/APIByCategory
//gcc kaos.c -lm -lSDL2 -lSDL2main -o kaos

#include <SDL2/SDL.h>
#include <math.h>

#define true     1
#define false    0

//Screen dimension in pixels
#define _W 800
#define _H 800

//Polygon type and radius dimension
#define N_POL 4
#define RADI ( _H / 2 )

//Predefined operation, divide by 2
#define DIV 2
//N_PLACES 0, Next vertex selected not the same vertex, 1: Not the next vertex in order, and so on ...
#define N_PLACES 2
//Cancel N_PLACES. ALL 1, all vertex possible selected
#define ALL 0

typedef struct punt{
    int x;
    int y;
} t_punt;

//Global pixel map
Uint32 pixels[_W * _H * sizeof(Uint32)];

void   _init_aleat();
int    _aleat(int n);
int    _aleat_diff(int n_pol, int vertex);
int    _nplaces_away_from_vertex(int vertex, int n_places, int n_pol);
int    _genera_poligon(t_punt POLIGON[], int n, int r);
int    _kaos( t_punt POLIGON[], t_punt *punt, int *vertex);


int main(int argc, char ** argv)
{
    int quit = false;
    SDL_Event event;
 
    t_punt POLIGON[N_POL], punt;
    int vertex;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2 Chaos Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _W, _H, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, _W, _H);
    memset(pixels, 255, _W * _H * sizeof(Uint32));

    _init_aleat();
    punt.x = _aleat(_W);
    punt.y = _aleat(_H);
    _genera_poligon(POLIGON, N_POL, RADI);
    vertex = _aleat(N_POL);
    while (!quit)
    {
        SDL_UpdateTexture(texture, NULL, pixels, _W * sizeof(Uint32));
          if (( SDL_PollEvent(&event) ) && (event.type == SDL_QUIT )) quit = true;
          _kaos(POLIGON, &punt, &vertex);
          pixels[punt.y * _W + punt.x] = 1;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int _kaos( t_punt POLIGON[], t_punt *punt, int *vertex){
   switch ( ALL ){
        case 1:     *vertex = _aleat( N_POL );
                    break;
        case 0:    *vertex = _aleat_diff(N_POL, _nplaces_away_from_vertex(*vertex, N_PLACES, N_POL));
                    break;
        default:    break;
    }
    punt->x = punt->x + (POLIGON[*vertex].x - punt->x) / DIV;
    punt->y = punt->y + (POLIGON[*vertex].y - punt->y) / DIV;
}

void   _init_aleat(){srand(time(NULL));}
int    _aleat(int n){return rand() % n;}
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
