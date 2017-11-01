#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../header/grid.h"

/**
*\file struct.h
*\brief définition des structures
*/

/**
 *\struct Context strcut.h Cette structure permet de définir le jeu et tous ce que l'on appelle tout le long de celui-ci. 
 */

typedef struct Context{ //Definiton du jeu
  SDL_Surface *ecran; //Surface principal 
  SDL_Surface **images, **menu, **text, **animCat; //Tableaux des différentes images à utiliser
  int nbAnimCat, nbImg, nbMenu, nbPacks, nbText; //Indice des différents tableaux
  TTF_Font *police, *policeGo, *policeMenu, *policeMenu2; //Différentes polices utilisées
  int resX, resY; //Resolution fenetre
  int onMenu, menuType, choice, musicType, colorChoice; //Gestion des menus
  SDL_Color color; //Couleur de la police
  Mix_Music **musique; //Tableau de musique
} Context;

/**
 *\struct Input struct.h Cette structure contient un tableau de tous les inputs possible, ils sont deux valeurs possible, true pour si l'input est enfoncé et false pour le contraire.
 */ 

typedef struct{
  char key[SDLK_LAST]; // tableau des inputs
  int mouseX, mouseY; //position réelle souris
  char mouseButtons[8]; //tableau des inputs de la souris
  char quit;
} Input;

