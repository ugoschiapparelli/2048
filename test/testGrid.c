#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "../header/grid.h"

static void waitFor (unsigned int t){
  int retTime = time(0) + t;
  while (time(0) < retTime);
}

static void afficherGrid(grid g){
  int val;
  for (int y=0; y < GRID_SIDE; y++){
    for (int x=0; x < GRID_SIDE; x++){
      if(get_tile(g, x, y) != 0){
	val = pow(2, get_tile(g, x, y));
	printf(" %8d ",val);
      }
      else
	printf(" %8d ", 0);
    }
    
    printf("\n");
  }
  printf("\n");
}

static bool equalsTo(grid g1, grid g2){
  for(int x = 0; x < GRID_SIDE; x++)
    for(int y = 0; y < GRID_SIDE; y++)
      if(get_tile(g1, x, y) != get_tile(g2, x, y))
	return false;
  return true;
}


static void initGrid(grid g){
  for(int x = 0; x < GRID_SIDE; x++)
    for(int y = 0; y < GRID_SIDE; y++)
      set_tile(g, x, y, 0);
}

static bool test_get_set_tile(grid g){
  tile i = 0;
  for(int x = 0; x < GRID_SIDE; x++){
    for(int y = 0; y < GRID_SIDE; y++){
      set_tile(g, x, y, i);
      if(get_tile(g, x, y) != i)
        return false;
      i++;
    }
  }
  return true;
}

static bool test_add_tile(grid g){
  initGrid(g);
  afficherGrid(g);
  for(int i = 0; i < GRID_SIDE*GRID_SIDE; i++){
    add_tile(g);
    afficherGrid(g);
    waitFor(1);
    //Il faut attendre entre chaque test parce que la partie aléatoire de add_tile dépend de l'horloge de l'ordinateur, ce qui rend tous les résultats identiques en cas d'executions consécutives trop rapides
  }
  for(int x = 0; x < GRID_SIDE; x++)
    for(int y = 0; y < GRID_SIDE; y++)
      if(pow(2, get_tile(g, x, y)) != 2 && pow(2, get_tile(g, x, y)) != 4)
        return false;
  return true;
  
}

static bool test_copy_grid(grid g, grid g2){
  copy_grid(g, g2);
  for(int x = 0; x < GRID_SIDE; x++)
    for(int y = 0; y < GRID_SIDE; y++)
      if(get_tile(g, x, y) != get_tile(g2, x, y))
        return false;
  return true;

}

static bool test_can_move(grid g){
  initGrid(g);
  int y1 = 0;
  int y2 = 0;
  int y3 = 0;

  initGrid(g);

  dir tabDir[4] = {UP, DOWN, LEFT, RIGHT};

  for(int i = 0; i < 4; i++){

    dir d = tabDir[i];

   

    //Tous les cas forcément juste
  
    for(int x = 0 ; x < GRID_SIDE; x++){
      
      //Premier for: tout les cas avec une seule valeur (différente de 0) par colonne ou par ligne

      /*
      //UP ou DOWN      //LEFT OU RIGHT
      0000     0000     0100     0010
      1000     0000     0000     0000
      0000     1000     0000     0000
      0000     0000     0000     0000

      */
      for(y1 = 1; y1 < GRID_SIDE - 1; y1++){
	if (d == UP || d == DOWN)
	  set_tile(g, x, y1, 1);
	else
	  set_tile(g, y1, x, 1);
	if (!can_move(g, d))
	  return false;
	if (d == UP || d == DOWN)
	  set_tile(g, x, y1, 0);
	else
	  set_tile(g, y1, x, 0);
      }

      /*
      //U     //D/R    //L
      0000     1000     0001
      0000     0000     0000
      0000     0000     0000
      1000     0000     0000

      */

      if(d == UP)
	set_tile(g, 0, GRID_SIDE - 1, 1);
      else
	if(d == DOWN || d == RIGHT)
	  set_tile(g, 0, 0, 1);
	else // d == LEFT
	  set_tile(g, GRID_SIDE - 1, 0, 1);

      if(!can_move(g, d))
	return false;
      
      if(d == UP)
	set_tile(g, 0, GRID_SIDE - 1, 0);
      else
	if(d == DOWN || d == RIGHT)
	  set_tile(g, 0, 0, 0);
	else // d == LEFT
	  set_tile(g, GRID_SIDE - 1, 0, 0);

      // Deuxième for: tous les cas avec deux mêmes valeurs (différentes de 0) par colonne ou ligne
  
      for (y1=0; y1 < GRID_SIDE - 1; y1++){
	for (y2=2; y2 < GRID_SIDE; y2++){
	  if (d == UP || d == DOWN){
	    set_tile(g, x, y1, 1);
	    set_tile(g, x, y2, 1);
	  }
	  else{
	    set_tile(g, y1, x, 1);
	    set_tile(g, y2, x, 1);
	  }
	  if (!can_move(g, d))
	    return false;
	  if (d==UP){
	    set_tile(g, x, y1, 0);
	    set_tile(g, x, y2, 0);
	  }
	  else{
	    set_tile(g, y1, x, 0);
	    set_tile(g, y2, x, 0);
	  }     
	}
      }

      // Troisième for: tous les cas avec trois variable différente de 0 par colonne ou ligne

      for(y1=0; y1 < GRID_SIDE - 2; y1++){
	for(y2=y1+1; y2 < GRID_SIDE - 1; y2++){
	  y3=3;
	  if (d == UP || d == DOWN){
	    set_tile(g, x, y1, 1);
	    set_tile(g, x, y2, 1);
	    set_tile(g, x, y3, 1);
	  }
	  else{
	    set_tile(g, y1, x, 1);
	    set_tile(g, y2, x, 1);
	    set_tile(g, y3, x, 1);
	  }
	  if (can_move(g, d) == false)
	    return false;
	  if (d==UP){
	    set_tile(g, x, y1, 0);
	    set_tile(g, x, y2, 0);
	    set_tile(g, x, y3, 0);
	  }
	  else{
	    set_tile(g, y1, x, 0);
	    set_tile(g, y2, x, 0);
	    set_tile(g, y3, x, 0);
	  }
	}
      }
    }
  }
  /*
    U/L/R/D:X000     
    0000
    0000
    000X
  */

  
  set_tile(g, 0, 0, 1);
  set_tile(g, 3, 3, 1);
  if(!can_move(g, UP) || !can_move(g, LEFT) || !can_move(g, RIGHT) || !can_move(g, LEFT))
    return false;     

  initGrid(g);
  /*
    XX00     XXX0     XXXX
    X000     X00X     X00X
    000X     X00X     X00X
    00XX     0XXX     XXXX
  */
  
  // U/L/R/D
  set_tile(g, 0, 0, 1);
  set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, 1);
  for(int i = 1; i < 4; i++){
    set_tile(g, 0, i, 1);
    set_tile(g, i, 0, 1);
    set_tile(g, GRID_SIDE - 1 - i, GRID_SIDE - 1, 1);
    set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1 - i, 1);
    if(!can_move(g, UP) || !can_move(g, LEFT) || !can_move(g, RIGHT) || !can_move(g, DOWN))
      return false;
  }
  initGrid(g);
  
  /*
    UP       DOWN     LEFT     RIGHT
    Y000     0000     YX00     0000
    X000     0000     0000     0000
    0000     X000     0000     0000
    0000     Y000     0000     00XY
  */

  //UP

  set_tile(g, 0, 0, 2);
  set_tile(g, 0, 1, 1);
  if(can_move(g, UP))
    return false;
  set_tile(g, 0, 0, 0);
  set_tile(g, 0, 1, 0);

  
  //DOWN

  set_tile(g, 0, GRID_SIDE - 1, 2);
  set_tile(g, 0, GRID_SIDE - 2, 1);
  if(can_move(g, DOWN))
    return false;
  set_tile(g, 0, GRID_SIDE - 1, 0);
  set_tile(g, 0, GRID_SIDE - 2, 0);


  //LEFT

  set_tile(g, 0, 0, 2);
  set_tile(g, 0, 1, 1);
  if(can_move(g, LEFT))
    return false;
  set_tile(g, 0, 0, 0);
  set_tile(g, 0, 1, 0);


  //RIGHT

  set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, 2);
  set_tile(g, GRID_SIDE - 2, GRID_SIDE - 1, 1);
  if(can_move(g, RIGHT))
    return false;
  set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, 0);
  set_tile(g, GRID_SIDE - 2, GRID_SIDE - 1, 0);
  
  initGrid(g);
  
  /*
    UP       UP       LEFT     LEFT     RIGHT    RIGHT    DOWN     DOWN
    Y000     X000     YXX0     XXY0     0XXY     0YXX     0000     0000
    X000     X000     0000     0000     0000     0000     X000     Y000
    X000     Y000     0000     0000     0000     0000     X000     X000
    0000     0000     0000     0000     0000     0000     Y000     X000
  */
  //UP

  set_tile(g, 0, 0, 2);
  for(int y = 1; y < 3; y++)
    set_tile(g, 0, y, 1);
  if(!can_move(g, UP))
    return false;
  set_tile(g, 0, 2, 2);
  set_tile(g, 0, 0, 1);
  if(!can_move(g, UP))
    return false;

  initGrid(g);


  //LEFT

  set_tile(g, 0, 0, 2);
  for(int x = 1; x < 3; x++)
    set_tile(g, x, 0, 1);
  if(!can_move(g, LEFT))
    return false;
  set_tile(g, 0, 0, 1);
  set_tile(g, 2, 0, 2);
  if(!can_move(g, LEFT))
    return false;

  initGrid(g);
  
  
  //RIGHT

  set_tile(g, 0, GRID_SIDE - 1, 2);
  for(int x = 2; x < GRID_SIDE; x++)
    set_tile(g, x, 0, 1);
  if(!can_move(g, RIGHT))
    return false;
  set_tile(g, GRID_SIDE - 1, 0, 1);
  set_tile(g, GRID_SIDE - 3, 0, 2);
  if(!can_move(g, RIGHT))
    return false;

  initGrid(g);

  
  //DOWN

  set_tile(g, 0, GRID_SIDE - 1, 2);
  for(int y = 1; y < GRID_SIDE; y++)
    set_tile(g, 0, y, 1);
  if(!can_move(g, DOWN))
    return false;
  set_tile(g, 0, GRID_SIDE - 1, 1);
  set_tile(g, 0, GRID_SIDE - 3, 2);
  if(!can_move(g, DOWN))
    return false;

  initGrid(g);

    
  /*
    U        D        L        R
    X000     0000     XYX0     0XYX
    Y000     X000     0000     0000
    X000     Y000     0000     0000
    0000     X000     0000     0000
  */

  
  //UP
  
  set_tile(g, 0, 0, 1);
  set_tile(g, 0, 1, 2);
  set_tile(g, 0, 2, 1);
  if(can_move(g, UP))
    return false;

  set_tile(g, 0, 1, 0);
  set_tile(g, 0, 2, 0);

  
  //LEFT

  set_tile(g, 0, 1, 2);
  set_tile(g, 0, 2, 1);
  if(can_move(g, LEFT))
    return false;

  initGrid(g);


  //DOWN

  set_tile(g, 0, GRID_SIDE - 1, 1);
  set_tile(g, 0, GRID_SIDE - 2, 2);
  set_tile(g, 0, GRID_SIDE - 3, 1);
  if(can_move(g, DOWN))
    return false;

  initGrid(g);

  //RIGHT

  set_tile(g, GRID_SIDE - 1, 0, 1);
  set_tile(g, GRID_SIDE - 2, 0, 2);
  set_tile(g, GRID_SIDE - 3, 0, 1);
  if(can_move(g, RIGHT))
    return false;

  initGrid(g);

  
  /*
    UP/DOWN

    X000     Y000     X000     X000     X000
    X000     X000     Y000     X000     X000
    X000     X000     X000     Y000     X000
    X000     X000     X000     X000     Y000
  */
  for(int y = 0; y < GRID_SIDE; y++)
    set_tile(g, 0, y, 1);
  if(!can_move(g, UP) || !can_move(g, DOWN))
    return false;
  
  for(int y = 0; y < GRID_SIDE; y++){
    set_tile(g, 0, y, 2);
    if(!can_move(g, UP) || !can_move(g, DOWN))
      return false;
    set_tile(g, 0, y, 1);
  }

  initGrid(g);

  /*
    LEFT/RIGHT
  
    XXXX     YXXX     XYXX     XXYX     XXXY
    0000     0000     0000     0000     0000
    0000     0000     0000     0000     0000
    0000     0000     0000     0000     0000
  */
  
  for(int x = 0; x < GRID_SIDE; x++)
    set_tile(g, x, 0, 1);
  if(!can_move(g, LEFT) || !can_move(g, RIGHT))
    return false;
  for(int x = 0; x < GRID_SIDE; x++){
    set_tile(g, x, 0, 2);
    if(!can_move(g, LEFT) || !can_move(g, RIGHT))
      return false;
    set_tile(g, x, 0, 1);
  }   
  return true;
}

static bool test_game_over(grid g){
  int n = 1;
  for(int i = 0; i < GRID_SIDE; i++){
    for(int j = 0; j < GRID_SIDE; j++){
      set_tile(g, i, j, n);
      n++;
    }
  }
  if (!can_move(g, UP) && !can_move(g, DOWN) && !can_move(g, RIGHT) && !can_move(g, LEFT) && game_over(g));
  return true;
  return false;
}

static bool test_score(grid g){
  initGrid(g);
  int score = 0;
  int valeur = 1;
  set_tile(g, 0, 0, valeur);
  set_tile(g, 0, 1, valeur);
  do_move(g, UP);
  score += pow(2, ++valeur);
  set_tile(g, 1, 0, valeur);
  do_move(g, LEFT);
  score += pow(2, ++valeur);
  set_tile(g, 0, GRID_SIDE - 1, valeur);
  do_move(g, DOWN);
  afficherGrid(g);
  score += pow(2, ++valeur);
  set_tile(g, GRID_SIDE - 1, GRID_SIDE - 1, valeur);
  do_move(g, RIGHT);
  score += pow(2, ++valeur);
  return score == grid_score(g);
}

static bool test_do_move(grid g){
  initGrid(g);

  grid gUp = new_grid();
  grid gDown = new_grid();
  grid gLeft = new_grid();
  grid gRight = new_grid();
  
  /*
  //       UP        DOWN       LEFT        RIGHT
  2000 ->  2222  OU  0000  OU   2000   OU   0002
  0200     0000      0000       2000        0002
  0020     0000      0000       2000        0002
  0002     0000      2222       2000        0002

  */
    
  //Grilles à obtenir après do_move

  for(int x = 0; x < GRID_SIDE; x++)
    set_tile(gUp, x, 0, 1);
  
  for(int x = 0; x < GRID_SIDE; x++)
    set_tile(gDown, x, GRID_SIDE - 1, 1);

  for(int y = 0; y < GRID_SIDE; y++)
    set_tile(gLeft, 0, y, 1);

  for(int y = 0; y < GRID_SIDE; y++)
    set_tile(gRight, GRID_SIDE - 1, y, 1);

  //UP
  for(int y = 0, x = 0; y < GRID_SIDE && x < GRID_SIDE; y++, x++)
    set_tile(g, x, y, 1);

  do_move(g, UP);

  if(!equalsTo(g, gUp))
    return false;
  initGrid(g);

  //DOWN
  for(int y = 0, x = 0; y < GRID_SIDE && x < GRID_SIDE; y++, x++)
    set_tile(g, x, y, 1);
  
  do_move(g, DOWN);

  if(!equalsTo(g, gDown))
    return false;
  initGrid(g);

  //LEFT
  for(int y = 0, x = 0; y < GRID_SIDE && x < GRID_SIDE; y++, x++)
    set_tile(g, x, y, 1);
  
  do_move(g, LEFT);

  if(!equalsTo(g, gLeft))
    return false;
  initGrid(g);

  //RIGHT
  for(int y = 0, x = 0; y < GRID_SIDE && x < GRID_SIDE; y++, x++)
    set_tile(g, x, y, 1);
 
  do_move(g, RIGHT);

  if(!equalsTo(g, gRight))
    return false;

  initGrid(g);
  initGrid(gUp);
  initGrid(gLeft);
  initGrid(gDown);
  initGrid(gRight);

  /*
           UP          LEFT       DOWN      RIGHT
  2200     4400   OU   4000  OU   0000  OU  0004 
  2200     0000        4000       0000      0004
  0000     0000        0000       0000      0000
  0000     0000        0000       4400      0000
  */
  for(int i = 0; i < 2; i++){
    set_tile(gUp, i, 0, 2);
    set_tile(gLeft, 0, i, 2);
    set_tile(gDown, i, GRID_SIDE - 1, 2);
    set_tile(gRight, GRID_SIDE - 1, i, 2);
  }

  for(int x = 0; x < 2; x++)
    for(int y = 0; y < 2; y++)
      set_tile(g, x, y, 1);
  do_move(g, UP);
  if(!equalsTo(g, gUp))
    return false;
  
  initGrid(g);

  for(int x = 0; x < 2; x++)
    for(int y = 0; y < 2; y++)
      set_tile(g, x, y, 1);
  do_move(g, LEFT);
  if(!equalsTo(g, gLeft))
    return false;

  initGrid(g);
  
  for(int x = 0; x < 2; x++)
    for(int y = 0; y < 2; y++)
      set_tile(g, x, y, 1);
  do_move(g, DOWN);
  if(!equalsTo(g, gDown))
    return false;

  initGrid(g);

  for(int x = 0; x < 2; x++)
    for(int y = 0; y < 2; y++)
      set_tile(g, x, y, 1);
  do_move(g, RIGHT);
  if(!equalsTo(g, gRight))
    return false;


  initGrid(g);
  initGrid(gUp);
  initGrid(gLeft);
  initGrid(gDown);
  initGrid(gRight);

  
  //Mouvements à la suite sans réinitialisation de la grille avec 2 valeurs différentes dans la direction à tester

/*            DOWN        RIGHT       UP          LEFT
  1000   =>   0000   =>   0000   =>   0021   =>   2100
  2300        0000        0000        0003        3000
  0000        1000        0001        0000        0000
  0000        2300        0023        0000        0000
  */
  
  
  set_tile(g, 0, 0, 1);
  set_tile(g, 0, 1, 2);
  set_tile(g, 1, 1, 3);

  set_tile(gDown, 0, GRID_SIDE - 2, 1);
  set_tile(gDown, 0, GRID_SIDE - 1, 2);
  set_tile(gDown, 1, GRID_SIDE - 1, 3);

  set_tile(gRight, GRID_SIDE - 1, GRID_SIDE - 2, 1);
  set_tile(gRight, GRID_SIDE - 2, GRID_SIDE - 1, 2);
  set_tile(gRight, GRID_SIDE - 1, GRID_SIDE - 1, 3);

  set_tile(gUp, GRID_SIDE - 1, 0, 1);
  set_tile(gUp, GRID_SIDE - 2, 0, 2);
  set_tile(gUp, GRID_SIDE - 1, 1, 3);
  
  set_tile(gLeft, 1, 0, 1);
  set_tile(gLeft, 0, 0, 2);
  set_tile(gLeft, 0, 1, 3);
  

  do_move(g, DOWN);

  if(!equalsTo(g, gDown))
    return false;

  do_move(g, RIGHT);
  if(!equalsTo(g, gRight))
    return false;

  do_move(g, UP);
  if(!equalsTo(g, gUp))
    return false;

  do_move(g, LEFT);
  if(!equalsTo(g, gLeft))
    return false;
    
  initGrid(g);
  initGrid(gUp);
  initGrid(gLeft);
  initGrid(gDown);
  initGrid(gRight);


  /*On teste que les valeurs ne se "chevauchent" pas suite aux fusions successives
    Si GRID_SIDE est impair, les grilles gUp, gDown, gLeft et gRight ne se comporteraient pas de la même façon, cependant le "chevauchement" possible est déjà testé
   */
  if(GRID_SIDE % 2 == 0){
  /* Initialisation de la grille, UP puis LEFT
     Réinitialisation de la grille, DOWN puis RIGHT

            //UP      //LEFT      //DOWN     //RIGHT
    1111    2222  ->  3300   OU   0000  ->   0000
    1111    2222      3300        0000       0000
    1111    0000      0000        2222       0033
    1111    0000      0000        2222       0033

   */

    for(int x = 0; x < GRID_SIDE; x++){
      for(int y = 0; y < GRID_SIDE / 2; y++){
	set_tile(gUp, x, y, 2);
	set_tile(gDown, x, GRID_SIDE - 1 - y, 2);
      }
    }

    for(int x = 0; x < (GRID_SIDE / 2); x++){
      for(int y = 0; y < (GRID_SIDE / 2); y++){
	set_tile(gLeft, x, y, 3);
	set_tile(gRight, GRID_SIDE - 1 - x, GRID_SIDE - 1 - y, 3);
      }
    }
  
    //Initialisation de g
    for(int x = 0; x < GRID_SIDE; x++)
      for(int y = 0; y < GRID_SIDE; y++)
	set_tile(g, x, y, 1);

    do_move(g, UP);

    if(!equalsTo(g, gUp))
      return false;

    do_move(g, LEFT);

    if(!equalsTo(g, gLeft))
      return false;

    //Initialisation de g
    for(int x = 0; x < GRID_SIDE; x++)
      for(int y = 0; y < GRID_SIDE; y++)
	set_tile(g, x, y, 1);

    do_move(g, DOWN);

    if(!equalsTo(g, gDown))
      return false;

    do_move(g, RIGHT);

    if(!equalsTo(g, gRight))
      return false;

    initGrid(g);
    initGrid(gUp);
    initGrid(gLeft);
    initGrid(gDown);
    initGrid(gRight);
  
  /*
    INIT       //UP       //LEFT       //DOWN      //RIGHT
    2110       2110  ->   2200    OU   0000   ->   0000
    1000       2000       2000         0000        0000
    1000       0000       0000         2000        0002
    0000       0000       0000         2110        0022
   */

    set_tile(gUp, 0, 0, 2);
    set_tile(gUp, 1, 0, 1);
    set_tile(gUp, 2, 0, 1);
    set_tile(gUp, 0, 1, 2);
  
    set_tile(gLeft, 0, 0, 2);
    set_tile(gLeft, 1, 0, 2);
    set_tile(gLeft, 0, 1, 2);

    set_tile(gDown, 0, GRID_SIDE - 1, 2);
    set_tile(gDown, 0, GRID_SIDE - 2, 2);
    set_tile(gDown, 1, GRID_SIDE - 1, 1);
    set_tile(gDown, 2, GRID_SIDE - 1, 1);
  
    set_tile(gRight, GRID_SIDE - 1, GRID_SIDE - 1, 2);
    set_tile(gRight, GRID_SIDE - 2, GRID_SIDE - 1, 2);
    set_tile(gRight, GRID_SIDE - 1, GRID_SIDE - 2, 2);

  
    //Init
    set_tile(g, 0, 0, 2);
    set_tile(g, 1, 0, 1);
    set_tile(g, 2, 0, 1);
    set_tile(g, 0, 1, 1);
    set_tile(g, 0, 2, 1);

    do_move(g, UP);
    if(!equalsTo(g, gUp))
      return false;

    do_move(g, LEFT);
    if(!equalsTo(g, gLeft))
      return false;
  
    //Init
    set_tile(g, 0, 0, 2);
    set_tile(g, 1, 0, 1);
    set_tile(g, 2, 0, 1);
    set_tile(g, 0, 1, 1);
    set_tile(g, 0, 2, 1);

    do_move(g, DOWN);
    if(!equalsTo(g, gDown))
      return false;

    do_move(g, RIGHT);
    if(!equalsTo(g, gRight))
      return false;
  }
  
  return true;
}

int main(void){
  grid g = new_grid();
  bool testGetSet = test_get_set_tile(g);
  bool testAdd = test_add_tile(g);
  grid g2 = new_grid();
  bool testCopy = test_copy_grid(g, g2);
  bool testCanMove = test_can_move(g);
  bool testGameOver = test_game_over(g);
  bool testGridScore = test_score(g);
  bool testDoMove = test_do_move(g);
  delete_grid(g2);
  test_do_move(g);
  printf("Test des fonctions get_tile et set_tile: ");
  printf(testGetSet ? "OK\n" : "ERROR\n");
  printf("Test de la fonction add_tile: ");
  printf(testAdd ? "OK\n" : "ERROR\n");
  printf("Test de la fonction copy_grid: ");
  printf(testCopy ? "OK\n" : "ERROR\n");
  printf("Test de la fonction can_move: ");
  printf(testCanMove ? "OK\n" : "ERROR\n");
  printf("Test de la fonction game_over: ");
  printf(testGameOver ? "OK\n" : "ERROR\n");
  printf("Test de la fonction grid_score: ");
  printf(testGridScore ? "OK\n" : "ERROR\n");
  printf("Test de la fonction test_do_move: ");
  printf(testDoMove ? "OK\n" : "ERROR\n");
  delete_grid(g);
  return 0;
}
