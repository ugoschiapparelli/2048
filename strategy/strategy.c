#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "strategy.h"
#include "stdlib.h"

//Déclarations
int evaluation_recursive(grid g, int prof, bool premier, dir d, strategy s);
int min(int t[], grid g);
void tableauEval(grid g, int *t);
int min_premier(int t[], grid g, strategy s);
int calcul_evaluation(grid g);

void free_memless_strat (strategy strat){
  free (strat);
}

dir play_move_fast(strategy s, grid g){
  bool premier = true;
  dir d = UP;
  evaluation_recursive(g, 2, premier, d, s);
  return (dir)s->mem;
}

dir play_move_efficient(strategy s, grid g){
  bool premier = true;
  dir d = UP;
  evaluation_recursive(g, 5, premier, d, s);
  return (dir)s->mem;
}

strategy A1_bedin_etcheverry_schiapparelli_fast(){
  strategy s = malloc(sizeof(struct strategy_s));
  s->name = "A1_bedin_etcheverry_schiapparelli_fast";
  s->play_move = play_move_fast;
  s->free_strategy = free_memless_strat;
  return s;
}

strategy A1_bedin_etcheverry_schiapparelli_efficient(){
  strategy s = malloc(sizeof(struct strategy_s));
  s->name = "A1_bedin_etcheverry_schiapparelli_efficient";
  s->play_move = play_move_efficient;
  s->free_strategy = free_memless_strat;
  return s;
}

//Retourne l'évaluation minimum parmi les 4 grilles possibles et affecte la direction à s->mem
int evaluation_recursive(grid g, int prof, bool premier, dir d, strategy s){ 
  if (prof==0)
    return calcul_evaluation(g);

  int eval = 0;

  //Créer les 4 grilles correspondant aux 4 directions possibles
  grid gUp = new_grid(), gLeft = new_grid(), gDown = new_grid(), gRight = new_grid(); 
  copy_grid(g, gUp);
  if (can_move(gUp, UP))
    do_move(gUp, UP);
  copy_grid(g, gLeft);
  if(can_move(gLeft, LEFT))
    do_move(gLeft, LEFT);
  copy_grid(g, gDown);
  if(can_move(gDown, DOWN))
    do_move(gDown, DOWN);
  copy_grid(g, gRight);
  if(can_move(gRight, RIGHT))
    do_move(gRight, RIGHT);
  
  //On calcule les 4 évaluations dans chaque direction
  int eMinUp = calcul_evaluation(gUp), eMinLeft = calcul_evaluation(gLeft), eMinDown = calcul_evaluation(gDown), eMinRight = calcul_evaluation(gRight); 

  int* tUp = malloc(4*sizeof(int));
  tableauEval(gUp, tUp);
  int* tDown = malloc(4*sizeof(int));
  tableauEval(gDown, tDown);
  int* tLeft = malloc(4*sizeof(int));
  tableauEval(gLeft, tLeft);
  int* tRight = malloc(4*sizeof(int));
  tableauEval(gRight, tRight);
 
  //On utilise la récursivité pour calculer l'addition de tous les minimums de chaque cas possible
  int eUp = evaluation_recursive(gUp, prof - 1, false, d, s); 
  int eDown = evaluation_recursive(gUp, prof - 1, false, d, s);
  int eLeft = evaluation_recursive(gLeft, prof - 1, false, d, s);
  int eRight = evaluation_recursive(gRight, prof - 1, false, d, s);

  eUp += min(tUp, gUp);
  eDown += min(tDown, gDown);
  eLeft += min(tLeft, gLeft);
  eRight += min(tRight, gRight);

  //On ajoute à chaque cas possible l'additon des minimums déjà calculés
  eUp += eMinUp; 
  eDown += eMinDown;
  eLeft += eMinLeft;
  eRight += eMinRight;
  
  //On crée un tableau contenant l'addition de tous les minimums selon la profondeur
  int t[4] = {eUp, eDown, eLeft, eRight}; 

  //Si on est à la première profondeur on choisit le minimum à affecter à s->mem  
  if (premier==true) 
    eval = min_premier(t, g, s);
  else
  //Sinon on calcule juste le minimum 
    eval = min(t, g); 

  //On libère la mémoire
  free(tUp);
  free(tDown);
  free(tLeft);
  free(tRight);
  delete_grid(gUp); 
  delete_grid(gDown);
  delete_grid(gLeft);
  delete_grid(gRight);
  return eval;
}

//Retourne le minimum d'un tableau t d'evaluations
int min(int t[], grid g){ 
  int eval = 0;
  int first_move = 0;
  //On créer un tableau des directions possibles pour pouvoir tester si elles sont valides
  dir *d = malloc(4 * sizeof(dir)); 
  d[0]=UP;
  d[1]=DOWN;
  d[2]=LEFT;
  d[3]=RIGHT;
  for (int i =0; i < 4; i++){
    if (can_move(g, d[i])){ //On regarde si les directions sont valides
      if (first_move==0) //Si c'est la première direction valide, pas besoin de comparer
	eval = t[i];
      else if (t[i] < eval) //Sinon on compare avec eval
	eval = t[i];
      first_move++; 
    }
  }
  free(d);
  return eval;
}

//Retourne le minimum d'un tableau d'evaluation et affecte la direction correspondant à ce minimum à s->mem
int min_premier(int t[], grid g, strategy s ){ 
  int eval = 0;
  int first_move = 0;
  dir *tDir = malloc(4 * sizeof(dir));
  tDir[0]=UP;
  tDir[1]=DOWN;
  tDir[2]=LEFT;
  tDir[3]=RIGHT;
  for(int i = 0; i < 4; i++){
    if(can_move(g, tDir[i])){
      if(first_move==0){
	s->mem = (dir *)tDir[i];
	eval = t[i];
      }
      else if (t[i] < eval){
	s->mem = (dir *)tDir[i];
	eval = t[i];
      }
      first_move++;
    }
  }
  free(tDir);
  return eval;
}

//On créé 4 grilles, on met leur evaluation dans un tableau
void tableauEval(grid g, int* t){
  grid gUp = new_grid(), gLeft = new_grid(), gDown = new_grid(), gRight = new_grid(); //Créer 4 grilles des 4 directions possible  
  copy_grid(g, gUp);
  if (can_move(gUp, UP))
    do_move(gUp, UP);
  copy_grid(g, gLeft);
  if(can_move(gLeft, LEFT))
    do_move(gLeft, LEFT);
  copy_grid(g, gDown);
  if(can_move(gDown, DOWN))
    do_move(gDown, DOWN);
  copy_grid(g, gRight);
  if(can_move(gRight, RIGHT))
    do_move(gRight, RIGHT);
  int eMinUp = calcul_evaluation(gUp), eMinLeft = calcul_evaluation(gLeft), eMinDown = calcul_evaluation(gDown), eMinRight = calcul_evaluation(gRight); //On calcule les evaluations que l'on met dans des tableaux
  t[0] = eMinUp;
  t[1] = eMinDown;
  t[2] = eMinLeft;
  t[3] = eMinRight;
  delete_grid(gUp); 
  delete_grid(gDown);
  delete_grid(gLeft);
  delete_grid(gRight);
}

//Calcul de l'évaluation
int calcul_evaluation(grid g){
  int L = 0, US = 0, M;
  int SUP_i = 0, INF_i = 0, SUP_j = 0, INF_j = 0;

  //Calcul de M
  for(int i = 1; i < GRID_SIDE; i++){
    for(int j = 0; j < GRID_SIDE; j++){
      if(get_tile(g, i, j) < get_tile(g, i - 1, j))
	SUP_i++;
      else if(get_tile(g, i, j) > get_tile(g, i - 1, j))
	INF_i++;
    }
  }
  for(int j = 1; j < GRID_SIDE; j++){
    for(int i = 0; i < GRID_SIDE; i++){
      if(get_tile(g, i, j) < get_tile(g, i, j - 1))
	SUP_j++;
      else if(get_tile(g, i, j) > get_tile(g, i, j - 1))
	INF_j++;
    }
  }
  M = fmin(SUP_i, INF_i) + fmin(SUP_j, INF_j);

  //Calcul de US
  for(int i = 0; i < GRID_SIDE; i++)
    for(int j = 0; j < GRID_SIDE; j++)
      if(get_tile(g, i, j) != 0)
	US++;

  //Calcul de L
  for(int i = 0; i < GRID_SIDE; i++)
    for(int j = 0; j < GRID_SIDE; j++){
      if (i==0 && j >= 1)
	L += fabs(get_tile(g, i, j) - 0) + fabs(get_tile(g, i, j) - get_tile(g, i, j - 1));
      if (i >= 1 && j==0)
	L += fabs(get_tile(g, i, j) - get_tile(g, i - 1, j)) + fabs(get_tile(g, i, j) - 0);
      if (i==0 && j==0)
      L += fabs(get_tile(g, i, j) - 0) + fabs(get_tile(g, i, j) - 0);
      if (i > 1 && j >= 1)
	L += fabs(get_tile(g, i, j) - get_tile(g, i - 1, j)) + fabs(get_tile(g, i, j) - get_tile(g, i, j - 1));
    }
      return 2 * L + 2 * US + 6 * M;
}
