#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../header/grid.h"
#include "strategy.h"

static void afficherGrid(grid g){
  int val;
  int valScore;
  for (int y = 0; y < GRID_SIDE; y++){
    for (int x=0; x < GRID_SIDE; x++){
      if(get_tile(g, x, y) != 0)
	val = pow(2, get_tile(g, x, y));
      else
	val = 0;
      printf(" %8d ",val);      
    }
    printf("\n");
  }
  printf("\n");
  valScore = grid_score(g);
  printf("Score: %8d", valScore);
  printf("\n\n");
}

int main(int argc, char** argv){
  grid g;
  int reussi;
  int tilemax = 0;
  int scoremax = 0;
  for(int i = 0; i < 1; i++){
    g = new_grid();
    add_tile(g);
    add_tile(g);
    strategy s = A1_bedin_etcheverry_schiapparelli_efficient();
    printf("%s\n", s->name);
    while(!game_over(g)){
      play(g, s->play_move(s, g));
      afficherGrid(g);
    }
    for(int i = 0; i < GRID_SIDE ; i++)
      for(int j = 0 ; j < GRID_SIDE ; j++){
	if(get_tile(g,i,j) > tilemax){
	  tilemax = get_tile(g,i,j);
	}
	if(get_tile(g, i, j) == 11)
	  reussi++;
      }
    if (grid_score(g) > scoremax)
      scoremax = grid_score(g);
    s->free_strategy(s);
    delete_grid(g);
  }
  printf("Tile Maximum = %d\n", (int)pow(2,tilemax));
  printf("Score Maximum = %d\n", scoremax);
  printf("Reussite: %d\n", reussi);
  
  return EXIT_SUCCESS;
}
