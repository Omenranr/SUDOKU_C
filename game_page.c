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
#include "score_page.h"
#define WIDTH 800
#define HEIGHT 600
#define DIST 100
#define BWIDTH 342
#define BHEIGHT 95
int load_win_page(SDL_Surface *ecran, SDL_Event event, int *notescp);
int load_game_page(SDL_Surface *ecran, int int_grille[4][4], int solution_grille[4][4], int numplayer, char *nom) {
    srand(time(NULL));
    char nom_g[100] = "";
    int rep = 0;
    sprintf(nom_g, "%s", nom);
    int notescp = 1;
    FILE *initial_gfile;
    char pathIG[40];
    int initial_grille[4][4];
    char infosGrille[4][20];
    int gamenumpl = numplayer;
    int obj_posx = 55;
    int obj_posy = 110;
    int nbrimage;
    int tic = 0;
    int restart = 0;
    //SDL_EnableKeyRepeat(10, 10);
    SDL_Surface *background = NULL;
    SDL_Surface *game_table = NULL;
    SDL_Surface *grille[4][4];
    SDL_Surface *res_button = NULL;
    SDL_Surface *save_button = NULL;
    SDL_Surface *score_button = NULL;
    SDL_Surface *quit = NULL;

    SDL_Rect pos_background;
    SDL_Rect pos_game_table;
    SDL_Rect pos_grille[4][4];
    SDL_Rect pos_res_button;
    SDL_Rect pos_save_button;
    SDL_Rect pos_score_button;
    SDL_Rect pos_quit;
    int can_change[4][4] = {0};
    pos_background.x = 0;
    pos_background.y = 0;

    pos_game_table.x = 21;
    pos_game_table.y = 99;
    int positionsx[4] = {0, 180, 372, 560};
    int positionsy[4] = {0, 115, 232, 348};

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            pos_grille[i][j].x = obj_posx + positionsx[j];
            pos_grille[i][j].y = obj_posy + positionsy[i];
        }
    }

    pos_res_button.x = 317;
    pos_res_button.y = 17;

    pos_save_button.x = 59;
    pos_save_button.y = 17;

    pos_score_button.x = 3 * 166 + 77;
    pos_score_button.y = 17;

    pos_quit.x = 0;
    pos_quit.y = 0;

    background = IMG_Load("img/game_back.png");
    game_table = IMG_Load("img/game_table.png");
    res_button = IMG_Load("img/restart_button.png");
    save_button = IMG_Load("img/save_button.png");
    score_button = IMG_Load("img/score_button.png");
    quit = IMG_Load("img/quit.png");
restart:
    if(numplayer == -1) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                int_grille[i][j] = 0;
                solution_grille[i][j] = 0;
                can_change[i][j] = 1;
            }
        }
        init_grille(int_grille, solution_grille);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                initial_grille[i][j] = int_grille[i][j];
            }
        }
    } else if(numplayer != -1 && restart == 0) {
        sprintf(pathIG, "players/init_grilles/%d.txt", numplayer);

        initial_gfile = fopen(pathIG, "r");
        for(int i = 0; i < 4; i++) {
            fgets(infosGrille[i], 20, initial_gfile);
            for(int j = 0; j < 4; j++) {
                initial_grille[i][j] = infosGrille[i][j] - 48;
            }
        }
        fclose(initial_gfile);
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(initial_grille[i][j] != 0) {
                can_change[i][j] = 0;
            } else {
                can_change[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            nbrimage = int_grille[i][j];
            char *path = malloc(35 * sizeof(char));
            sprintf(path, "img/%d.png", nbrimage);
            grille[i][j] = IMG_Load(path);
        }
    }

    int continuer = 1;
    int gagne = 0;
    int i = 1;
    int toc = 0;
    SDL_Event event;
    int score = 1000;
    char *pathC = malloc(35 * sizeof(char));
    notescp = 1;
    while(continuer) {
        toc = SDL_GetTicks();
        if(toc - tic > 1000 && gagne == 0 && score > 0) {
            score -= 10;
            tic = toc;
        }
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                SDL_FreeSurface(background);
                SDL_FreeSurface(game_table);
                SDL_FreeSurface(res_button);
                SDL_FreeSurface(save_button);
                SDL_FreeSurface(score_button);
                SDL_FreeSurface(grille);
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    if(event.button.x > pos_res_button.x && event.button.x < pos_res_button.x + 166 && event.button.y > pos_res_button.y && event.button.y < pos_res_button.y + 60) {
                        restart = 1;
                        score = 1000;
                        for(int i = 0; i < 4; i++) {
                            for(int j = 0; j < 4; j++) {
                                int_grille[i][j] = 0;
                                initial_grille[i][j] = 0;
                                solution_grille[i][j] = 0;
                                can_change[i][j] = 1;
                            }
                        }
                        init_grille(int_grille, solution_grille);
                        for(int i = 0; i < 4; i++) {
                            for(int j = 0; j < 4; j++) {
                                initial_grille[i][j] = int_grille[i][j];
                            }
                        }
                        goto restart;
                    }
                    else if(event.button.x > pos_save_button.x && event.button.x < pos_save_button.x + 166 && event.button.y > pos_res_button.y && event.button.y < pos_save_button.y + 60) {
                        if(gamenumpl == -1) {
                                save_page(ecran, event, initial_grille, int_grille, solution_grille, &gamenumpl, score, nom_g);
                        } else {
                            save_game(initial_grille, int_grille, solution_grille, &gamenumpl, score, nom_g);
                        }
                    }
                    else if(event.button.x > pos_score_button.x && event.button.x < pos_score_button.x + 166 && event.button.y > pos_score_button.y && event.button.y < pos_score_button.y + 60) {
                        load_score_page(ecran, event);
                    }
                    else if(event.button.x < 40 && event.button.y < 40) {
                        load_start_page(ecran);
                    }
                    for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 4; j++) {
                            if(can_change[i][j] == 1 && event.button.x > pos_grille[i][j].x - 20  && event.button.x < pos_grille[i][j].x + 155 && event.button.y > pos_grille[i][j].y - 5 && event.button.y < pos_grille[i][j].y + 100) {
                                int_grille[i][j]++;
                                if(int_grille[i][j] > 4) {int_grille[i][j] = 0;}
                                sprintf(pathC, "img/%d.png", int_grille[i][j]);
                                grille[i][j] = IMG_Load(pathC);
                            }
                        }
                    }
                }
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        goto end;
                    }
                    break;

        }

        SDL_BlitSurface(background, NULL, ecran, &pos_background);
        SDL_BlitSurface(game_table, NULL, ecran, &pos_game_table);
        SDL_BlitSurface(res_button, NULL, ecran, &pos_res_button);
        SDL_BlitSurface(save_button, NULL, ecran, &pos_save_button);
        SDL_BlitSurface(score_button, NULL, ecran, &pos_score_button);
        SDL_BlitSurface(quit, NULL, ecran, &pos_quit);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                SDL_BlitSurface(grille[i][j], NULL, ecran, &pos_grille[i][j]);
            }
        }

        SDL_Flip(ecran);
        gagne = 1;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(int_grille[i][j] != solution_grille[i][j]) {
                    gagne = 0;
                }
            }
        }


        if(gagne == 1 && notescp == 1) {
            load_win_page(ecran, event, &notescp);
        }
    }
    SDL_FreeSurface(background);
    SDL_FreeSurface(game_table);
    SDL_FreeSurface(res_button);
    SDL_FreeSurface(save_button);
    SDL_FreeSurface(score_button);
    SDL_FreeSurface(grille);
end: printf("\n");
    return 0;
}

void init_grille(int grille[4][4], int solution_grille[4][4]) {

	FILE *file = fopen("grilles.txt", "r");
	char str_grilles[20][4];
	char vide[4];
	int pos_grilles[5] = {0, 4, 8, 12, 16};
	int r = rand() % 5;
	printf("%d \n", r);
	for(int i = 0; i < 20; i++) {
		fgets(str_grilles[i], 5, file);
		fgets(vide, 5, file);
	}
	for(int i = pos_grilles[r]; i < pos_grilles[r] + 4; i++) {
		for(int j = 0; j < 4; j++) {
			grille[i % 4][j] = (int) str_grilles[i][j] - 48;
			solution_grille[i % 4][j] = (int) str_grilles[i][j] - 48;
		}
	}
	fclose(file);
	int nbr_enlv = 0;
	while(nbr_enlv < 8) {
		int ni = rand() % 4;
		int nj = rand() % 4;
		if(grille[ni][nj] != 0) {
			grille[ni][nj] = 0;
			nbr_enlv++;
		}
	}
}

int load_nbrj(FILE *var_ext) {
    char number[20];
    int nbrj = 0;
    int N = 0;
    int i = 0;
    fgets(number, 21, var_ext);

    while(number[N] != '\0') {
    	printf("%c", number[N]);
        N++;
    }
    printf("\n%d\n", N);
 	while(i < N) {
 		nbrj += ((int) number[i] - 48) * pow(10, N-i-1);
 		i++;
 	}
 	printf("%d\n", i);
 	printf("%d\n", nbrj);
	return nbrj;
}

int load_win_page(SDL_Surface *ecran, SDL_Event event, int *notescp) {
    SDL_Surface *background;
    SDL_Surface *text;
    TTF_Font *police = NULL;
    SDL_Color txt_color = {0, 0, 0};
    police = TTF_OpenFont("medusa.otf", 30);

    background = IMG_Load("img/back_gagne.png");
    text = TTF_RenderText_Blended(police, "VOUS AVEZ GAGNER", txt_color);
    SDL_Rect position;
    int continuer = 1;
    while(continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        continuer = 0;
                        *notescp = 0;
                    }
                    break;
        }
        position.x = 100;
        position.y = 100;
        SDL_BlitSurface(background, NULL, ecran, &position);
        position.x = 220;
        position.y = 220;
        SDL_BlitSurface(text, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    return 0;
}
