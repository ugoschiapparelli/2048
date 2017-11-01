/**
 *\file init.h
 *\brief Initialise le jeu 
 */

/**
 *\fn void LoadAnimCat(Context *C)
 *\brief Charge dans un tableau pédéfinis dans contexte toute les images pour l'animation du chat qui danse 
 *\param Context contexte du jeu
 */

void LoadAnimCat(Context *C);

/**
 *\fn void LoadMenu(Context *C)
 *\brief On charge toutes les images nécessaire au menu
 *\param Context contexte du jeu
 */

void LoadMenu(Context *C);

/**
 *\fn void LoadText(Context *C)
 *\brief On charge les surfaces nécessaire pour écrire
 *\param Context contexte du jeu
 */

void LoadText(Context *C);

/**
 *\fn void LoadMusic(Context *C)
 *\brief On charge les différentes musique
 *\param Context contexte du jeu
 */

void LoadMusic(Context *C);

/**
 *\fn void LoadImgSpace(Context *C)
 *\brief On charge toutes les images nécessaire au mode space cat
 *\param Context contexte du jeu
 */
  
void LoadImgSpace(Context *C);

/**
 *\fn void LoadImgNormal(Context *C)
 *\brief On charge toutes les images nécessaire au mode classique
 *\param Context contexte du jeu 
 */

void LoadImgNorm(Context *C);

/**
 *\fn void LoadAll(Context *C)
 *\brief On appelle toutes les fonctions pour charger tous ce que l'on as besoin 
 *\param Context contexte du jeu 
 */

void LoadAll(Context *C);

/**
 *\fn void Blit(SDL_Surface* s, SDL_Surface *d, int x, int y) 
 *\brief Dessine une image s sur un fond d à une position x et y
 *\param SDL_Surface la surface à "blitter"
 *\param SDL_Surface la surface où l'on va "blitter"
 *\param int position x de s par rapport à d
 *\param int position y de s par rapport à d
 */

void Blit(SDL_Surface* s, SDL_Surface *d, int x, int y);

/**
 *\fn void Write(Context *C, TTF_Font *police, SDL_Surface *text, char *val, int x, int y)
 *\brief Ecrit val avec une police définis dans les paramètre à une position x et y sur la surface principal ecran
 *\param Context contexte du jeu
 *\param TTF_Font police à utiliser
 *\param SDL_Surface surface texte à utiliser pour ecrire son texte
 *\param char texte à écrire
 *\param int position x du texte à écrire 
 *\param int position y du texte à écrire 
 */

void Write(Context *C,TTF_Font *police, SDL_Surface *text, char *val, int x, int y);

/**
 *\fn void Init(Context *C, int x, int y)
 *\brief Initilise le jeu avec une résolution x et y
 *\param Context contexte du jeu
 *\param int resolution x de l'écran
 *\param int resolution y de l'écran
 */

void Init(Context *C, int x, int y);

/**
 *\fn void InitGrid(Context *C)
 *\brief On initialise la grille avec les images et les couleurs de la police
 *\param Context contexte du jeu
 */

void InitGrid(Context *C);

/**
 *\fn void Liberer(Context *C, grid g)
 *\brief On libère tous ce que l'on as allouer en mémoire
 *\param Context contexte du jeu
 *\param grid grille g à libérer
 */ 

void Liberer(Context *C, grid g);
