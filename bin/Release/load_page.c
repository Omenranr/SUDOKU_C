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


int verify_page(SDL_Surface *ecran, SDL_Event event, int *canenter, char *nom, char *pass);

int load_load_page(SDL_Surface *ecran) {
    int nbrj = 0;
    int c = 0;
    int canenter = 0;
    int int_grille[4][4] = {0};
    int solution_grille[4][4] = {0};
    FILE *var = fopen("var_ext.txt", "r");
    FILE *players = NULL;
    FILE *player_pass = NULL;
    TTF_Font *police = NULL;
    SDL_Color txt_color = {0, 0, 0};
    police = TTF_OpenFont("kids.ttf", 20);
    SDL_Surface *background;
    SDL_Surface *info_backs[30];
    SDL_Surface *infos_txt[30][2];
    SDL_Surface *quit_butt;

    SDL_Rect position;
debut:
    nbrj = load_nbrj(var);
    fclose(var);
    char infos[nbrj][11][20];
	char *path = malloc(20 * sizeof(char));
    for(int i = 1; i < nbrj + 1; i++) {
        sprintf(path, "players/%d.txt", i);
        players = fopen(path, "r");
        for(int j = 0; j < 10; j++) {
            fgets(infos[i-1][j], 20, players);
        }
    }
	fclose(players);

    int len = 0;
    char toshow[40];
    background = IMG_Load("img/game_back.png");
    quit_butt = IMG_Load("img/quit.png");
    for(int i = 0; i < nbrj; i++) {
        info_backs[i] = IMG_Load("img/infos_back.png");
        sprintf(toshow, "PSEUDO: %s", infos[i][9]);
        len = strlen(toshow);
        toshow[len - 2] = '\0';
        infos_txt[i][0] = TTF_RenderText_Blended(police, toshow, txt_color);
        sprintf(toshow, "SCORE: %s", infos[i][8]);
        len = strlen(toshow);
        toshow[len - 2] = '\0';
        infos_txt[i][1] = TTF_RenderText_Blended(police, toshow, txt_color);
    }

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
                    SDL_FreeSurface(quit_butt);
                    load_start_page(ecran);
                    goto end;
                }
                for(int i = 0; i < nbrj; i++) {
                    if(event.button.x > 100 && event.button.x < 100 + 600 && event.button.y > i * 50 && event.button.y < i * 50 + 50) {
                        for(int j = 0; j < 4; j++) {
                            for(int k =0; k < 4; k++) {
                                int_grille[j][k] = infos[i][j][k] - 48;
                                solution_grille[j][k] = infos[i][j+4][k] - 48;
                            }
                        }
                        load_game_page(ecran, int_grille, solution_grille, i+1, infos[i][9]);
                        goto debut;
                    }
                }
        }

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(background, NULL, ecran, &position);
        SDL_BlitSurface(quit_butt, NULL, ecran, &position);
        for(int i = 0; i < nbrj; i++) {
            position.x = 100;
            position.y = i * 50;
            SDL_BlitSurface(info_backs[i], NULL, ecran, &position);

            position.x = 150;
            position.y = i * 50 + 10;
            SDL_BlitSurface(infos_txt[i][0], NULL, ecran, &position);

            position.x = 450;
            position.y = i * 50 + 10;
            SDL_BlitSurface(infos_txt[i][1], NULL, ecran, &position);
        }
        SDL_Flip(ecran);
    }
end: printf("");
    return 0;
}

int verify_page(SDL_Surface *ecran, SDL_Event event, int *canenter, char *nom, char *pass) {

    return 0;
}

