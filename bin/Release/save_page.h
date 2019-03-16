#ifndef SAVE_PAGE
#define SAVE_PAGE
int save_page(SDL_Surface *ecran, SDL_Event event, int initial_grille[4][4], int grille[4][4], int sol_grille[4][4], int *gamenumpl, int score, char *nom);
int save_game(int initial_grille[4][4], int grille[4][4], int sol_grille[4][4], int *numplayer, int score, char *nom);
crypt(const char *passwd, const char *salt);
#endif // SAVE_PAGE
