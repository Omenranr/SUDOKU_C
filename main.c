#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "game_page.h"
#include "start_page.h"
#include "save_page.h"
#include "load_page.h"
#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    TTF_Init();
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("SuDoKu", NULL);

    SDL_WM_SetIcon(IMG_Load("img/1.png"), NULL);

    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(ecran == NULL) {
        fprintf(stderr, "error: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    load_start_page(ecran);
    SDL_Quit();
    TTF_Quit();
    return 0;
}



