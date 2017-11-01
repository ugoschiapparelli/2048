#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "../header/grid.h"

/**
 *\struct grid_s grid.c Cette structure est une grille où on définis le score et un tableau de tile
 */ 

struct grid_s{
  tile **tab;
  unsigned int score;
};

/**
 *\fn grid new_grid (void)
 *\return nouvelle grille alloué dans la fonction de taille GRID_SIDE*GRID_SIDE
 */

grid new_grid(void){
  grid g = malloc(sizeof(*g));
  assert(g != NULL);
  g->tab = malloc(GRID_SIDE * sizeof(tile*));
  assert(g->tab);
  for(int i = 0; i < GRID_SIDE; i++){
    g->tab[i] = malloc(GRID_SIDE * sizeof(tile));
    assert(g->tab[i]!= NULL);
    for (int j = 0; j < GRID_SIDE; j++)
      g->tab[i][j]=0;
  }
  g->score = 0;
  return g;
}

/**
 *\fn void delete_grid(grid g)
 *\return void 
 *\brief permet de supprimer une grille g et de libérer la mémoire alloué à celle-ci
 */  

void delete_grid(grid g){
  for(int i = 0; i < GRID_SIDE; i++)
    free(g->tab[i]);
  free(g->tab);
  free(g);
}

/**
 *\fn void copy_grid(grid src, grid dst)
 *\return void 
 *\brief permet de copier une grille source dans une autre grille
 */

void copy_grid(grid src, grid dst){
  for(int i = 0; i < GRID_SIDE; i++)
    for(int j = 0; j < GRID_SIDE; j++)
      dst->tab[i][j] = src->tab[i][j];
}


/**
 *\fn unsigned long int grid_score(grid g)
 *\return unsigned long int 
 *\brief permet de retourner le score d'une grille
 */  

unsigned long int grid_score(grid g){
  return g->score;
}

/**
 *\fn tile get_tile(grid g, int x, int y)
 *\return retourne une tile à la position x et y 
 */  

tile get_tile(grid g, int x, int y){
  assert(x >= 0 && x < GRID_SIDE && y >= 0 && y < GRID_SIDE);
  return g->tab[x][y];
}

/**
 *\fn void set_tile(grid g, int x, int y, tile t)
 *\return void
 *\brief change la valeur d'une tile à la position x et y 
 */ 

void set_tile(grid g, int x, int y, tile t){
  assert(x >= 0 && x < GRID_SIDE && y >= 0 && y < GRID_SIDE);
  g->tab[x][y] = t;
}

/**
 *\fn void add_tile(grid g)
 *\return void 
 *\brief ajoute de façon aléatoire une valeur de 2 ou 4 (1 chance sur 10 pour 4) dans les tile vide d'une grille en particulier 
 */  

void add_tile (grid g)
{
  int n=0;
  for (int x=0; x<GRID_SIDE; x++)       //On compte le nombre de cases vides
    for (int y=0; y<GRID_SIDE; y++)
      if (get_tile(g, x, y)==0)
	n+=1;
  srand(time(NULL));    //Initialise la variable temps de random à 0
  int alea=(rand() % n) + 1;
  for (int x=0; x<GRID_SIDE; x++)
    for (int y=0; y<GRID_SIDE; y++)
      {
	if (get_tile(g, x, y)==0)
	  alea-=1;
	if (alea==0)
	  {
	    int val=(rand() % 10) + 1;
	    if (val==10)                 //La case a 1 chance sur 10 de prendre la valeur 4, sinon elle prend la valeur 2
	      set_tile(g, x, y, 2);
	    else
	      set_tile(g, x, y, 1);
	    return;
	  }
      }
}

/**
 *\fn bool game_over(grid g)
 *\return renvoie true sur il n'y a plus aucun mouvement possible dans une grille quelque soit les directions et false sinon  
 */  

bool game_over (grid g)
{
  return !(can_move(g, UP) || can_move(g, DOWN) || can_move(g, LEFT) || can_move(g, RIGHT));
}

/**
 *\fn bool can_move(grid g, dir d)
 *\return retourne true si il existe un mouvement possible selon une direction définis dans les paramètres et false sinon
 */  

bool can_move(grid g, dir d){
  int incX = 0;
  int incY = 0;
  switch (d){                     //incX et incY permettent de savoir où se trouve la case suivante dans la grille, dans le sens du déplacement d
  case UP    :  incY = 1; break;
  case DOWN  :  incY = -1; break;
  case LEFT  :  incX = 1; break; 
  case RIGHT :  incX = -1; break;
  }
  for (int x = 0 ; x < GRID_SIDE ; ++x){
    for (int y = 0 ; y < GRID_SIDE ; ++y){
      if ((x + incX) < GRID_SIDE && (y + incY) < GRID_SIDE  && (x + incX >= 0) && (y + incY >= 0)){
	if (get_tile(g, x, y)==0){
	    if (get_tile(g, x + incX, y + incY) != 0)                 //Si une case qui suit un 0 est occupee, le deplacement est possible
	      return true;
	  }
	else
	  if (get_tile(g, x + incX, y + incY) == get_tile(g, x, y))   //Si 2 cases successives sont identiques, elles peuvent fusionner
	    return true;
      }
    }
  }
  return false;
}

/**
 *\fn static void decalageHaut(grid g, int x, int y)
 *\return void
 *\brief La valeur contenue dans g->tab[x][y] se retrouve en bas du tableau dans la même colonne à g->tab[x][GRID_SIDE - 1]
 * Toutes les valeurs g->tab[x][y2] (avec y < y2 < GRID_SIDE) se retrouvent à la position les précédant sur la même colonne, soit g->tab[x][y2 - 1].
 */
static void decalageHaut(grid g, int x, int y){
  tile tmp = get_tile(g, x, y);
  for(int y2 = y + 1; y2 < GRID_SIDE; y2++)
    set_tile(g, x, y2 - 1, get_tile(g, x, y2));
  set_tile(g, x, GRID_SIDE - 1, tmp);
}


/**
 *\fn static void decalageBas(grid g, int x, int y)
 *\return void
 *\brief La valeur contenue dans g->tab[x][y] se retrouve en haut du tableau dans la même colonne à g->tab[x][0]
 * Toutes les valeurs g->tab[x][y2] (avec 0 <= y2 < y) se retrouvent à la position les suivant sur la même colonne, soit g->tab[x][y2 + 1].
 */

static void decalageBas(grid g, int x, int y){
  tile tmp = get_tile(g, x, y);
  for(int y2 = y - 1; y2 >= 0; y2--)
    set_tile(g, x, y2 + 1, get_tile(g, x, y2));
  set_tile(g, x, 0, tmp);
}


/**
 *\fn static void decalageGauche(grid g, int x, int y)
 *\return void
 *\brief La valeur contenue dans g->tab[x][y] se retrouve à droite du tableau sur la même ligne à g->tab[GRID_SIDE - 1][y]
 * Toutes les valeurs g->tab[x2][y] (avec x < x2 < GRID_SIDE) se retrouvent à la position les précédant sur la même ligne, soit g->tab[x2 - 1][y].
 */

static void decalageGauche(grid g, int x, int y){
  tile tmp = get_tile(g, x, y);
  for(int x2 = x + 1; x2 < GRID_SIDE; x2++)
    set_tile(g, x2 - 1, y, get_tile(g, x2, y));
  set_tile(g, GRID_SIDE - 1, y, tmp);
}


/**
 *\fn static void decalageDroite(grid g, int x, int y)
 *\brief La valeur contenue dans g->tab[x][y] se retrouve à gauche du tableau sur la même ligne à g->tab[0][y]
 * Toutes les valeurs g->tab[x2][y] (avec 0 <= x2 < x) se retrouvent à la position les suivant sur la même ligne, soit g->tab[x2 + 1][y].
 */

static void decalageDroite(grid g, int x, int y){
  tile tmp = get_tile(g, x, y);
  for(int x2 = x - 1; x2 >= 0; x2--)
    set_tile(g, x2 + 1, y, get_tile(g, x2, y));
  set_tile(g, 0, y, tmp);
}



/**
 *\fn static void decalage(grid g, int x, int y, dir d)
 *\return void
 *\brief La fonction decalage fait appel à la fonction decalage précédente correspondant à la direction entrée en paramètre.
 */

static void decalage(grid g, int x, int y, dir d){
  switch(d){
  case UP:
    decalageHaut(g, x, y);
    break;
  case LEFT:
    decalageGauche(g, x, y);
    break;
  case DOWN:
    decalageBas(g, x, y);
    break;
  case RIGHT:
    decalageDroite(g, x, y);
    break;
  }
}

/**
 *\fn static void fusion(grid g, int x, int y, int incX, int incY)
 *\return void 
 *\brief Fusionne la case g[x][y] avec la case suivante définis par les incrément lorsque l'on appelle cette fonction dans do_move
 */

static void fusion(grid g, int x, int y, int incX, int incY){
  tile t = get_tile(g, x, y);
  set_tile(g, x + incX, y + incY, t+1);     //Cette case reçoit la somme des 2
  g->score+=pow(2, get_tile(g, x + incX, y + incY));
  set_tile(g, x, y, 0);
}
  
  
/**
 *\fn void do_move(grid g, dir d)
 *\return void
 *\brief Effectue un mouvement dans la direction dans une grille g
 */

void do_move(grid g, dir d){
  int incX = 0, incY = 0;
  int tmp;
  switch(d){                     // g[x + incX][y + incY] désignera toujours la case suivant g[x][y] dans la direction d
  case UP : incY = 1; break;
  case LEFT: incX = 1; break;
  case DOWN: incY = -1; break;
  case RIGHT: incX = -1; break;
  }
  //Les parcours de UP et de LEFT sont similaires
  if (d == UP || d == LEFT){
    //Decalage des 0 vers la direction opposée à d
    for(int x = 0; x < GRID_SIDE; x++)
      for(int y = 0; y < GRID_SIDE; y++){ 
	tmp = 0;
	while(get_tile(g, x, y) == 0 && tmp < GRID_SIDE){
	  decalage(g, x, y, d);
	  tmp += 1;
	}
      }
    //Fusion des cases
    for(int x = 0; x < GRID_SIDE - incX; x++){
      for(int y = 0; y < GRID_SIDE - incY; y++){
	if (get_tile(g, x, y) != 0)
	  if(get_tile(g, x, y) == get_tile(g, x + incX, y + incY)){
	    fusion(g, x, y, incX, incY);
	    decalage(g, x, y, d);
	}
      }
    }
  }

  //Les parcours de RIGHT et de DOWN sont similaires
  else{
    //Decalage des 0
    for(int x = GRID_SIDE - 1 ; x >= 0 ; x--)
      for(int y = GRID_SIDE - 1 ; y >= 0 ; y--){
	tmp = 0;
	while(get_tile(g, x, y) == 0 && tmp < GRID_SIDE){
	  decalage(g, x, y, d);
	  tmp += 1;
	}
      }
    //Fusion
    for(int x = GRID_SIDE - 1 ; x >= 0 - incX ; x--){
      for(int y = GRID_SIDE - 1 ; y >= 0 - incY ; y--){
	if (get_tile(g, x, y) != 0)
	  if(get_tile(g, x, y) == get_tile(g, x + incX, y + incY)){
	    fusion(g, x, y, incX, incY);
	    decalage(g, x, y, d);
	  }
      }
    }
  }
}

/**
 *\fn void play(grid g, dir d)
 *\return void
 *\brief Joue dans une direction si celle-ci est possible et ajoute une tile alétoire à la grille
 */

void play(grid g, dir d)
{
  if (can_move(g, d))
    {
      do_move(g, d);
      add_tile(g);
    }
}
