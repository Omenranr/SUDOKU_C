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

int save_page(SDL_Surface *ecran, SDL_Event event, int initial_grille[4][4], int grille[4][4], int sol_grille[4][4], int *gamenumpl, int score, char *nom) {
    char buffer[100] = "";
    char buffer2[100] = "";
    char buffer3[100] = "";
    TTF_Font *police = NULL;
    SDL_Color txt_color = {0, 0, 0};
    police = TTF_OpenFont("medusa.otf", 30);

    SDL_Surface *background;
    SDL_Surface *user_text;
    SDL_Surface *pin_text;


    background = IMG_Load("img/save_page.png");

    SDL_Rect position;


    if(*gamenumpl == -1) {
        int continuer = 1;
        int len = 0;
        int tomod = 0;
        while(continuer) {
            SDL_WaitEvent(&event);
            switch(event.type) {
                case SDL_QUIT:
                    SDL_FreeSurface(background);
                    SDL_FreeSurface(user_text);
                    SDL_FreeSurface(pin_text);
                    SDL_Quit();
                case SDL_KEYDOWN:
                    if(tomod == 0) {
                        if(event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
                            sprintf(buffer, "%s%c", buffer, event.key.keysym.sym - 32);
                        }
                        else if(event.key.keysym.sym == SDLK_BACKSPACE) {
                            len = strlen(buffer);
                            buffer[len - 1] = '\0';
                        }
                    }
                    if(tomod == 1) {
                        if(event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
                            sprintf(buffer2, "%s%c", buffer2, event.key.keysym.sym - 32);
                            sprintf(buffer3, "%s%c", buffer3, 'O');

                        }
                        else if(event.key.keysym.sym == SDLK_BACKSPACE) {
                            len = strlen(buffer2);
                            buffer2[len - 1] = '\0';
                            buffer3[len - 1] = '\0';
                        }
                    }
                    if(event.key.keysym.sym == SDLK_UP) {
                        tomod = 0;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN) {
                        tomod = 1;
                    }
                    else if(event.key.keysym.sym == SDLK_KP_ENTER && strcmp(buffer2, "ABCD") == 0) {
                        save_game(initial_grille, grille, sol_grille, gamenumpl, score, buffer);
                        sprintf(nom, "%s", buffer);
                        continuer = 0;
                    }
                    else if(event.key.keysym.sym == SDLK_ESCAPE) {
                        continuer = 0;
                    }
            }
            position.x = 100;
            position.y = 100;
            SDL_BlitSurface(background, NULL, ecran, &position);
            user_text = TTF_RenderText_Blended(police, buffer, txt_color);
            position.x = 320;
            position.y = 198;
            SDL_BlitSurface(user_text, NULL, ecran, &position);
            pin_text = TTF_RenderText_Blended(police, buffer3, txt_color);
            position.x = 320;
            position.y = 320;
            SDL_BlitSurface(pin_text, NULL, ecran, &position);

            SDL_Flip(ecran);

        }
    }
    SDL_FreeSurface(background);
    SDL_FreeSurface(user_text);
    SDL_FreeSurface(pin_text);

    TTF_CloseFont(police);
    return 0;
}

int save_game(int initial_grille[4][4], int grille[4][4], int sol_grille[4][4], int *numplayer, int score, char *nom) {
    int nbrj = 0;
    int c = 0;
    FILE *var = fopen("var_ext.txt", "r");
    char path[30] = "";
    char path2[30] = "";
    nbrj = load_nbrj(var);
    FILE *file_player = NULL;
    FILE *initial_grilles = NULL;
    if(*numplayer == -1) {
        sprintf(path2, "players/init_grilles/%d.txt", nbrj + 1);
        sprintf(path, "players/%d.txt", nbrj + 1);
        *numplayer = nbrj + 1;
        var = freopen("var_ext.txt", "w", var);
        fprintf(var, "%d", *numplayer);

    } else {
        sprintf(path, "players/%d.txt", *numplayer);
        sprintf(path2, "players/init_grilles/%d.txt", *numplayer);
    }
    initial_grilles = fopen(path2, "w");
    for(int i = 0; i < 4; i++) {
        fprintf(initial_grilles, "%d%d%d%d\r\n", initial_grille[i][0], initial_grille[i][1], initial_grille[i][2], initial_grille[i][3]);
    }
    file_player = fopen(path, "w");
    for(int i = 0; i < 4; i++) {
        fprintf(file_player, "%d%d%d%d\r\n", grille[i][0], grille[i][1], grille[i][2], grille[i][3]);
    }
    for(int i = 0; i < 4; i++) {
        fprintf(file_player, "%d%d%d%d\r\n", sol_grille[i][0], sol_grille[i][1], sol_grille[i][2], sol_grille[i][3]);
    }
    fprintf(file_player, "%d\r\n", score);
    fprintf(file_player, "%s\r\n", nom);
    fclose(var);
    fclose(initial_grilles);
    fclose(file_player);
    return 0;
}



