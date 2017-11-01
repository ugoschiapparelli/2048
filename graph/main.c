#include "struct.h"
#include "init.c"
#include "2048graph.c"
#include "menu.c"
#include "option.c"

void UpdateEvents(Input* in){
  SDL_Event event;
  in->mouseButtons[SDL_BUTTON_WHEELUP] = 0;
  in->mouseButtons[SDL_BUTTON_WHEELDOWN] = 0;
  while(SDL_PollEvent(&event)){
    switch (event.type){
    case SDL_KEYDOWN: // On gère les pression sur les touches
      in->key[event.key.keysym.sym]=1;
      break;
    case SDL_KEYUP: // Relachement des touches
      in->key[event.key.keysym.sym]=0;
      break;
    case SDL_MOUSEMOTION: // Souris qui se deplace
      in->mouseX=event.motion.x;
      in->mouseY=event.motion.y;
      break;
    case SDL_MOUSEBUTTONDOWN: //Bouton souris
      in->mouseButtons[event.button.button]=1;
      break;
    case SDL_MOUSEBUTTONUP://Position de la souris
      if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
	in->mouseButtons[event.button.button]=0;
      break;
    case SDL_QUIT://Bouton echap
      in->quit = 1;
      break;
    default:
      break;
    }
  }
}

int main(void) {
  Context C; //Définis les différente structures et int à utilisés 
  Input in;
  grid g = new_grid();
  int i = 0, j = 0, k = 0;
  add_tile(g); //Ajoute les deux tile aléatoire de base
  add_tile(g);
  memset(&in, 0, sizeof(in)); // On alloue la mémoire à in et on met toute les valeurs à 0
  Init(&C, 505, 670); //Initalise le jeu avec une sérolution de 505 par 670
  while(!in.key[SDLK_ESCAPE] && !in.quit){ //Tant que l'on appuye pas sur la touche echap ou que l'on appuye pas sur la croix
    unsigned int elapsed; 
    unsigned int lasttime = SDL_GetTicks(); //Permet de compter les secondes
    UpdateEvents(&in); //Initialise les tableaux d'inputs
    if (C.onMenu == 0){ //Si on n'est pas dans le menu
      PlayGrid(&C, &in, g); //on joue et on dessine sur la surface principale
      DrawGrid(&C, g, i); //Le i permet de changer les images des animations
    }
    else{
      if (C.menuType == 0){//Si on est dans le menu principal 
	j = PlayMenu(&C, &in, g); //On recupère les inputs et on dessine le menu
	DrawMenu(&C, j);
      }
      else{
	k = PlayOptions(&C, &in); //Si on est dans les options on fait la même chose que menu
	DrawOptions(&C, k);
      }
    }
    SDL_Flip(C.ecran); //Mise à jour de la surface principale
    while(SDL_Flip(C.ecran)!=0)  // Permet d'augmenter le temps de latence pour que les animations soit fluides
      SDL_Delay(1); 			  
    elapsed = SDL_GetTicks()-lasttime;  
    if (elapsed<90){						
      SDL_Delay(90-elapsed);
    }
    i++; //Augmante toutes les 90 sec
    if (i==4) 
      i=0;
    
  }
  Liberer(&C, g); //Libère la mémoire allouer 
  return 0;
}
