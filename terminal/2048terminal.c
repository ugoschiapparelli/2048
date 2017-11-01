#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../header/grid.h"

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
  grid g = new_grid();
  char c; 
  add_tile(g);
  add_tile(g);
  afficherGrid(g);
  printf("Jouez avec les touches Z, Q, S, D\n\n");
  while (!game_over(g)){
    scanf("%c",&c);
    if(c =='Z'){
      printf("Haut\n");
      play(g,UP);
      afficherGrid(g);
    }
    else if (c =='S'){
      printf("Bas\n");
      play(g,DOWN);
      afficherGrid(g);
    }
    else if (c =='D'){
      printf("Droite\n");
      play(g,RIGHT);
      afficherGrid(g);
    }
    else if (c == 'Q'){
      printf("Gauche\n");
      play(g, LEFT);
      afficherGrid(g);
    }
    else if (c == 'q'){
      break;
    } 
  }
  
  return EXIT_SUCCESS;
}
