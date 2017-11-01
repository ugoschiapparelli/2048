void DrawOptions(Context *C, int i){
  int j = 0;
  Uint32 white = SDL_MapRGB(C->ecran->format, 255, 255, 255); //On définis deux couleur différente 
  Uint32 brown = SDL_MapRGB(C->menu[5]->format, 187, 170, 154);
  SDL_FillRect(C->ecran, NULL, white); //Et on dessine les différente images avec ces couleurs
  SDL_FillRect(C->menu[5], NULL, brown);
  Write(C, C->policeMenu2, C->text[7], "Options", 40, 0); //On écrit le titre
  Blit(C->menu[0], C->ecran, 152, 150); //On fait le même chose que pour les boutons de DrawMenu 
  if (i > 10){
    SDL_SetAlpha(C->menu[6], SDL_SRCALPHA, 60);
    SDL_SetAlpha(C->menu[3], SDL_SRCALPHA, 60);
    SDL_SetAlpha(C->menu[7], SDL_SRCALPHA, 60);
    i = i%10;
    j = 1;
  }
  else{
    SDL_SetAlpha(C->menu[6], SDL_SRCALPHA, 30);
    SDL_SetAlpha(C->menu[3], SDL_SRCALPHA, 30);
    SDL_SetAlpha(C->menu[7], SDL_SRCALPHA, 30);
  }
  Write(C, C->policeMenu, C->text[8], "Musique", 195, 157);
  Blit(C->menu[5], C->ecran, 152, 235);
  if (i == 1){
    Blit(C->menu[6], C->ecran, 152, 235);
    Write(C, C->policeMenu, C->text[7], "Space cat - Day breaks", 80, 500); //Si on passe sur la première musique on affiche son titre
  }
  Write(C, C->policeMenu, C->text[8], "1", 175, 235);
  Blit(C->menu[5], C->ecran, 222, 235);
  if (i == 2){
    Blit(C->menu[6], C->ecran, 222, 235);
    Write(C, C->policeMenu, C->text[7], "Sugar rush - pixl", 100, 500);//Même chose ici
  }
  Write(C, C->policeMenu, C->text[8], "2", 243, 235);
  Blit(C->menu[5], C->ecran, 292, 235);
  if (i == 3)
    Blit(C->menu[6], C->ecran, 292, 235);
  Write(C, C->policeMenu, C->text[8], "3", 315, 235);
  Blit(C->menu[4], C->ecran, 147, 305);
  Blit(C->menu[0], C->ecran, 152, 310);
  if (i == 4){
    if (j == 1)
      Blit(C->menu[3], C->ecran, 147, 305);
    else
      Blit(C->menu[7], C->ecran, 152, 310);
  }
  Write(C, C->policeMenu, C->text[8], "Stop Music", 165, 322);
  Blit(C->menu[4], C->ecran, 147, 395);
  Blit(C->menu[0], C->ecran, 152, 400);
  if (i == 5){
    if (j == 1)
      Blit(C->menu[3], C->ecran, 147, 395);
    else
      Blit(C->menu[7], C->ecran, 152, 400);
  }
  Write(C, C->policeMenu, C->text[8], "Menu", 215, 407);
}

int PlayOptions(Context *C, Input *in){
  int i = 0;
  if (in->mouseX > 152 && in->mouseY > 235 && in->mouseX <= 152 + 60 && in->mouseY <= 235 + 60){
    i = 1;
  }
  if (in->mouseX > 152 && in->mouseY > 235 && in->mouseX <= 152 + 60 && in->mouseY <= 235 + 60 && in->mouseButtons[SDL_BUTTON_LEFT]){ //Si on appuye sur le premier bouton on lance la première musique et on choisit celle-là pour le space cat mode
    Mix_PlayMusic(C->musique[0], 1);
    C->musicType = 0;
    i = 11;
  }
  if (in->mouseX > 222 && in->mouseY > 235 && in->mouseX <= 222 + 60 && in->mouseY <= 235 + 60){
    i = 2;
  }
  if (in->mouseX > 222 && in->mouseY > 235 && in->mouseX <= 222 + 60 && in->mouseY <= 235 + 60 && in->mouseButtons[SDL_BUTTON_LEFT]){//Même chose pour la seconde musique
    Mix_PlayMusic(C->musique[1], 1);
    C->musicType = 1;
    i = 12;
  }
  if (in->mouseX > 292 && in->mouseY > 235 && in->mouseX <= 292 + 60 && in->mouseY <= 235 + 60){
    i = 3;
  }
  if (in->mouseX > 292 && in->mouseY > 235 && in->mouseX <= 292 + 60 && in->mouseY <= 235 + 60 && in->mouseButtons[SDL_BUTTON_LEFT]){//Même chose ici pour la toisième musique 
    Mix_PlayMusic(C->musique[2], 1);
    C->musicType = 2;
    i = 13;
  }
  if (in->mouseX > 152 && in->mouseY > 305 && in->mouseX <= 152 + 200 && in->mouseY <= 305 + 75)
    i = 4;
  if (in->mouseX > 152 && in->mouseY > 305 && in->mouseX <= 152 + 200 && in->mouseY <= 305 + 75 && in->mouseButtons[SDL_BUTTON_LEFT]){//Si on appuye sur ce bouton, on stop la musique
    Mix_HaltMusic();
    i = 14;
  }
  if (in->mouseX > 152 && in->mouseY > 390 && in->mouseX <= 152 + 200 && in->mouseY <= 390 + 75)
    i = 5;
  if (in->mouseX > 152 && in->mouseY > 390 && in->mouseX <= 152 + 200 && in->mouseY <= 390 + 75 && in->mouseButtons[SDL_BUTTON_LEFT]){ //Si on appuye sur celui-ci, on revient au menu de base
    Mix_HaltMusic();
    in->mouseButtons[SDL_BUTTON_LEFT] = 0;
    C->menuType = 0;
    i = 15;
  }
  return i;
}
