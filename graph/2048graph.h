/**
 *\file 2048graph.h
 *\brief lance la partie graphique du jeu en lui même
 */

/**
 *\fn void anime(Context *C, int i)
 *\brief "colle" sur l'ecran principal les 4 mêmes images au quatre coins de l'ecran principal, on prend i en paramètre pour savoir quelle image utilisé
 *\param Context contexte du jeu
 *\param int entier pour savoir quelle image dessiner
 */

void anime(Context *C, int i);

/**
 *\fn void DrawGrid(Context *C, grid g, int i)
 *\brief "redessine" l'aspect graphique à chaque instant t selon une grille g
 *\param Context contexte du jeu
 *\param grid la grille g à utiliser
 *\param int entier qu'on utilise dans la fonction anime
 */

void DrawGrid(Context *C, grid g, int i);

/**
 *\fn void PlayGrid(Context *C, Input *in, grid g)
 *\brief permet de savoir quoi faire selon les inputs qui sont pressés
 *\param Context contexte du jeu
 *\param Input tableau des inputs
 *\param grid grille à utiliser 
 */

void PlayGrid(Context *C, Input *in, grid g);
