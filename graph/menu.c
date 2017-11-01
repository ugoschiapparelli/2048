void DrawMenu(Context *C, int i){
  int j = 0;
  Uint32 white = SDL_MapRGB(C->ecran->format, 255, 255, 255); //La surface principale de fond est blanc 
  SDL_FillRect(C->ecran, NULL, white);
  Write(C, C->policeMenu2, C->text[7], "2048", 120, 0); //On écrit le titre 
  Blit(C->menu[4], C->ecran, 147, 145); //On dessine les différents boutons 
  Blit(C->menu[0], C->ecran, 152, 150); //Avec la bordure
  if (i > 10){ //Si i est supérieur à 10 (Soit si on as eu un clic souris)
    SDL_SetAlpha(C->menu[3], SDL_SRCALPHA, 60); //Le filtre noir s'assombrit sur toute la taille du bouton
     SDL_SetAlpha(C->menu[7], SDL_SRCALPHA, 60);
     i = i%10; //On change la valeur de i pour savoir quelle bouton est pressé
     j = 1; //j vaut 1 pour car on as clique
  }
  else{
    SDL_SetAlpha(C->menu[3], SDL_SRCALPHA, 30); //Sinon le filtre noir est assez clair
    SDL_SetAlpha(C->menu[7], SDL_SRCALPHA, 30);
  }
  if ( i == 2){ //si la souris passe sur le premier bouton 
    if (j == 1)  //et quelle l'on as clique 
      Blit(C->menu[3], C->ecran, 147, 145); //On assombris avec la bordure
    else
      Blit(C->menu[7], C->ecran, 152, 150); //Sinon on passe le filtre noir mois sombre sur le bouton sans la bordure
  }
  Write(C, C->policeMenu, C->text[3], "Play", 215, 157); //On écrit le texte du bouton 
  Blit(C->menu[4], C->ecran, 147, 245); 
  if (i == 1) //On fait la même chose avec tous les boutons du menu 
    Blit(C->menu[2], C->ecran, 152, 250);
  else
    Blit(C->menu[1], C->ecran, 152, 250);
  Write(C, C->policeMenu, C->text[4], "Space cat", 175, 240);
  Write(C, C->policeMenu, C->text[4], "Mode", 215, 275);
  Blit(C->menu[4], C->ecran, 147, 345);
  Blit(C->menu[0], C->ecran, 152, 350);
  if ( i == 3){
    if (j == 1)
      Blit(C->menu[3], C->ecran, 147, 345);
    else
      Blit(C->menu[7], C->ecran, 152, 350);
  }
  Write(C, C->policeMenu, C->text[5], "Options", 200, 357);
  Blit(C->menu[4], C->ecran, 147, 445);
  Blit(C->menu[0], C->ecran, 152, 450);
  if (i == 4){
    if(j==1)
      Blit(C->menu[3], C->ecran, 147, 445);
    else
      Blit(C->menu[7], C->ecran, 152, 450);
  }
  Write(C, C->policeMenu, C->text[6], "Quit", 220, 457);
}

int PlayMenu(Context *C, Input *in, grid g){
  int i = 0;
  if (in->mouseY > 150 && in->mouseX > 152 && in->mouseY <= 150 + 75 && in->mouseX <= 152+200)// Si la souris passe sur le premier bouton
    i = 2;
  if (in->mouseY > 150 && in->mouseX > 152 && in->mouseY <= 150 + 75 && in->mouseX <= 152+200 && in->mouseButtons[SDL_BUTTON_LEFT]){ //Si on clique sur ce bouton, on lance le jeu en mode classique 
    delete_grid(g);
    g = new_grid(g);
    add_tile(g);
    add_tile(g);
    C->onMenu = 0;
    C->choice = 0;
    InitGrid(C);
    i = 12;
  }
  if (in->mouseY > 250 && in->mouseX > 152 && in->mouseY <= 250 + 75 && in->mouseX <= 152+200)
    i = 1;
  if (in->mouseY > 250 && in->mouseX > 152 && in->mouseY <= 250 + 75 && in->mouseX <= 152+200 && in->mouseButtons[SDL_BUTTON_LEFT]){//Si on clique sur ce bouton, on lance en mode space cat et on lance la musique 
    delete_grid(g);
    g = new_grid(g);
    add_tile(g);
    add_tile(g);
    C->onMenu = 0;
    C->choice = 1;
    InitGrid(C);
    Mix_PlayMusic(C->musique[C->musicType], -1);
  }
  if (in->mouseY > 350 && in->mouseX > 152 && in->mouseY <= 350 + 75 && in->mouseX <= 152+200)
    i = 3;
  if (in->mouseY > 350 && in->mouseX > 152 && in->mouseY <= 350 + 75 && in->mouseX <= 152+200 && in->mouseButtons[SDL_BUTTON_LEFT]){//Si on clique sur ce bouton, on lance les options
    in->mouseButtons[SDL_BUTTON_LEFT] = 0;
    C->menuType = 1;
    i = 13;
  }
  if (in->mouseY > 450 && in->mouseX > 152 && in->mouseY <= 450 + 75 && in->mouseX <= 152+200)
    i = 4;
  if (in->mouseY > 450 && in->mouseX > 152 && in->mouseY <= 450 + 75 && in->mouseX <= 152+200 && in->mouseButtons[SDL_BUTTON_LEFT]){//Si on clique sur ce bouton, on quitte 
    i = 14;
    in->quit=1;
  }
  return i;
}
