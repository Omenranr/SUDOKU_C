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
#define DIST 100
#define BWIDTH 342
#define BHEIGHT 95

int load_rules_page(SDL_Surface *ecran);

int load_start_page(SDL_Surface *ecran) {

    int tic = 0, toc = 0;
    int debut_grille[4][4] = {0};
    int debutsol_grille[4][4] = {0};

    SDL_Surface *background = NULL;
    SDL_Surface *logo = NULL;
    SDL_Surface *play_button = NULL;
    SDL_Surface *load_button = NULL;
    SDL_Surface *inst_button = NULL;

    SDL_Rect pos_background;
    SDL_Rect pos_logo;
    SDL_Rect pos_play_button;
    SDL_Rect pos_load_button;
    SDL_Rect pos_inst_button;
debut:
    tic = 0;
    toc = 0;
    pos_background.x = 0;
    pos_background.y = 0;

    pos_logo.x = WIDTH/4 + 22;
    pos_logo.y = DIST/2;

    pos_play_button.x = WIDTH/4 + 22;
    pos_play_button.y = DIST * 2;

    pos_load_button.x = WIDTH/4 + 22;
    pos_load_button.y = DIST * 3;

    pos_inst_button.x = WIDTH/4 + 22;
    pos_inst_button.y = DIST * 4;


    int i = 0;

    int continuer = 1;
    SDL_Event event;
    while(continuer) {
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                    continuer = 0;
                    break;
            case SDL_MOUSEBUTTONDOWN:
                 if (event.button.button == SDL_BUTTON_LEFT) {
                        if(event.button.x > WIDTH/4 + 37 && event.button.x < WIDTH/4 + BWIDTH && event.button.y > DIST * 2 && event.button.y < DIST * 2 + BHEIGHT - 15) {
                            load_game_page(ecran, debut_grille, debutsol_grille, -1, "");
                        }
                        else if(event.button.x > WIDTH/4 + 37 && event.button.x < WIDTH/4 + BWIDTH && event.button.y > DIST * 3 && event.button.y < DIST * 3 + BHEIGHT - 15) {
                            load_load_page(ecran);
                        }
                        else if(event.button.x > WIDTH/4 + 37 && event.button.x < WIDTH/4 + BWIDTH && event.button. y > DIST* 4 && event.button.y < DIST * 4 + BHEIGHT - 15) {
                            load_rules_page(ecran);
                        }
                 }
        }
        char *buffer = malloc(35 * sizeof(char));
        sprintf(buffer, "img/background_grames2/%d.gif", i);

        background = IMG_Load(buffer);
        logo = IMG_Load("img/logo.png");
        play_button = IMG_Load("img/play_button.png");
        load_button = IMG_Load("img/load_button.png");
        inst_button = IMG_Load("img/inst_button.png");

        SDL_BlitSurface(background, NULL, ecran, &pos_background);
        SDL_BlitSurface(logo, NULL, ecran, &pos_logo);
        SDL_BlitSurface(play_button, NULL, ecran, &pos_play_button);
        SDL_BlitSurface(load_button, NULL, ecran, &pos_load_button);
        SDL_BlitSurface(inst_button, NULL, ecran, &pos_inst_button);

        toc = SDL_GetTicks();
        if(toc - tic > 41) {
            i++;
            tic = toc;
        }
        if(i > 179) {
            i = 0;
        }
        SDL_Flip(ecran);
        free(buffer);
        SDL_FreeSurface(background);
        SDL_FreeSurface(logo);
        SDL_FreeSurface(play_button);
        SDL_FreeSurface(load_button);
        SDL_FreeSurface(inst_button);

    }
    SDL_Quit();
    return 0;
}

int load_rules_page(SDL_Surface *ecran) {

    SDL_Surface *background;
    SDL_Surface *quit;

    SDL_Rect position;

    background = IMG_Load("img/rules_back.png");
    quit = IMG_Load("img/quit.png");
    int continuer = 1;
    SDL_Event event;
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x < 40 && event.button.y < 40) {
                    SDL_FreeSurface(background);
                    SDL_FreeSurface(quit);
                    load_start_page(ecran);
                }
            break;
        }
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(background, NULL, ecran, &position);
        SDL_BlitSurface(quit, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    return 0;
}

