/**
*\file menu.h
*\brief permet de dessiner le menu 
*/

/**
 *\fn void DrawMenu(Context *C, int i)
 *\brief Dessine les differents boutons du menu
 *\param Context contexte du jeu
 *\param int entier pour savoir quelle bouton as été cliquer ou passé par la souris
 */

void DrawMenu(Context *C, int i);

/**
 *\fn int PlayMenu(Context *C, Input *in, grid g)
 *\brief prends les différent input des souris
 *\param Context contexte du jeu
 *\param Input tableau des inputs
 *\param grid grille à utiliser 
 *\return un int qui dit si la souris passe sur un bouton et si on clique sur celui-ci
 */

int PlayMenu(Context *C, Input *in, grid g);
