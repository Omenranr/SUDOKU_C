#ifndef GAME_PAGE
#define GAME_PAGE
int load_game_page(SDL_Surface *ecran, int int_grille[4][4], int solution_grille[4][4], int numplayer, char *nom);
void init_grille(int grille[4][4], int solution_grille[4][4]);
int verifier_sol(int grille[4][4], int solution_grille[4][4]);
int load_nbrj(FILE *var_ext);
#endif // GAME_PAGE
