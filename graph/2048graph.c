void anime(Context *C, int i){
  Blit(C->animCat[i], C->ecran, 0, 0);
  Blit(C->animCat[i], C->ecran, 405, 0);
  Blit(C->animCat[i], C->ecran, 0, 560);
  Blit(C->animCat[i], C->ecran, 405, 560);
}

void DrawGrid(Context *C, grid g, int i){
  int x = 0 , y = 0; 
  int Xpos = 0, Ypos = 0;
  int valScore, val;
  char tile[30];
  char score[30];
  Blit(C->images[1], C->ecran, 0, 0); //Colle le fond de la surface principal 
  Blit(C->images[3], C->ecran, 130, 240); //et le fond de la grille 
  for(int i = 0; i < 16; i++){ //Pour chaque tile de la grille on fait 
    int j = 1;
    if(get_tile(g, x, y)==0) //Si la tile est vide on met l'image d'une case vide
      Blit(C->images[5], C->ecran, 140 + Xpos, 250 + Ypos);
    if(get_tile(g, x, y)!=0){ //Si la tile n'est pas vide on met l'image d'une case pleine et on écrit la valeur de cette tile 
      if (C->choice == 0){ //Si on est en mode normal on colore les cases
	Uint32 color = SDL_MapRGB(C->images[4]->format, 255, 255, 255); //De base la couleur est blanc
	if(C->colorChoice == 0) //Selon les trois choix proposé on change en bleu, en rouge ou en vert
	  color = SDL_MapRGB(C->images[4]->format, 255 - get_tile(g, x, y)*12, 255, 255  - get_tile(g, x, y)*12);
	if(C->colorChoice == 1)
	  color = SDL_MapRGB(C->images[4]->format, 255, 255 - get_tile(g, x, y)*12, 255 - get_tile(g, x, y)*12);
	if(C->colorChoice == 2)
	  color = SDL_MapRGB(C->images[4]->format, 255 - get_tile(g, x, y)*12, 255, 255);
	SDL_FillRect(C->images[4], NULL, color); // On colorie la case
      }
      Blit(C->images[4], C->ecran, 140 + Xpos, 250 + Ypos); //l'image d'une case pleine est collé
      val = pow(2, get_tile(g,x,y)); // Valeur de la tile en puissance de 2
      sprintf(tile, "%u", val); // Convertit la tile val en char

      while(val/10!=0){ //On calcule le nombre de chiffres de la valeur d'une tile
	j++;
	val %= 10;
      }

      if (j==1) //écrit à une position différente selon le nombre de chiffre qu'il y a écrire 
	Write(C, C->police, C->text[0], tile, 140 + 19 + Xpos, 250 + 17 + Ypos);
      else if (j==2)
	Write(C, C->police, C->text[0], tile, 140 + 15 + Xpos, 250 + 15 + Ypos);
      else if (j==3)
	Write(C, C->police, C->text[0], tile, 140 + 0 + Xpos, 250 + 0 + Ypos);
      else
	Write(C, C->police, C->text[0], tile, 140 + 0 + Xpos, 250 + 0 + Ypos);
      
      valScore = grid_score(g); //Récupère le score
      sprintf(score, "Score: %u", valScore); //modifie le score en char
      Write(C, C->police, C->text[1], score, 220, 530);//Ecrit le nouveau score
    }
    y+=1; 
    Ypos+=60; //Permet d'avancer la position à la prochaine tile sur l'interfcae graphique puisque les cases font 60 pixels
    if (y == 4){ //Si ça fait 4 tile par ligne on change de colonne
      y=0;
      Ypos=0;
      x+=1;
      Xpos+=60;
    } 
  }
  Blit(C->images[0], C->ecran, 225, 120); //Dessine les deux boutons new game et menu 
  Blit(C->images[6], C->ecran, 225, 620);
  if (C->choice == 0){ //Si on est en mode normal On dessine les trois boutons R, G et B
    SDL_FillRect(C->menu[5], NULL, SDL_MapRGB(C->menu[5]->format, 122, 88, 53)); 
    Blit(C->menu[5], C->ecran, 410, 265);
    Write(C, C->policeMenu, C->text[7], "R", 433, 265);
    Blit(C->menu[5], C->ecran, 410, 340);
    Write(C, C->policeMenu, C->text[7], "G", 433, 340);
    Blit(C->menu[5], C->ecran, 410, 415);
    Write(C, C->policeMenu, C->text[7], "B", 433, 415);
  }
  if (game_over(g)){ //Si on as perdu on affiche l'image du game over et on écrit GAME OVER
    if (C->choice == 0)//Si on est en mode normal, on met l'image en transparence 
      SDL_SetAlpha(C->images[2], SDL_SRCALPHA, 128);
    Blit(C->images[2], C->ecran, 70, 180);
    Write(C, C->policeGo, C->text[2], "GAME OVER", 70, 450);
  }
  if (C->choice == 1) //Si on est en mode space cat, on dessine les images de l'animation du chat qui danse
  anime(C, i);
}

void PlayGrid(Context *C, Input *in, grid g){
  if (in->key[SDLK_UP] || in->key[SDLK_z]){ //Si la touche HAUT ou z est pressé on joue un mouvement vers le haut
    play(g, UP);
    in->key[SDLK_UP] = 0;
    in->key[SDLK_z] = 0;
  }
  if (in->key[SDLK_DOWN] || in->key[SDLK_s]){ //Même chose avec BAS et s
    play(g, DOWN);
    in->key[SDLK_DOWN] = 0;
    in->key[SDLK_s] = 0;
  }
  if (in->key[SDLK_LEFT] || in->key[SDLK_q]){ //Même chose avec LEFT et q
    play(g, LEFT);
    in->key[SDLK_LEFT] = 0;
    in->key[SDLK_q] = 0;
  }
  if (in->key[SDLK_RIGHT] || in->key[SDLK_d]){ //Même chose avec DROIT et d
    play(g, RIGHT);
    in->key[SDLK_RIGHT] = 0;
    in->key[SDLK_d] = 0;
  }
  if (in->mouseY > 120 && in->mouseX > 225 && in->mouseY <= 120+20 && in->mouseX <= 225+60 && in->mouseButtons[SDL_BUTTON_LEFT]){ //Si on appuye à la position du bouton new game on crée une nouvelle grille et on lui ajoute deux tile aléatoire
    delete_grid(g);
    g = new_grid(g);
    add_tile(g);
    add_tile(g);
  }
  if (in->mouseY > 620 && in->mouseX > 225 && in->mouseY <= 620+20 && in->mouseX <= 225+60 && in->mouseButtons[SDL_BUTTON_LEFT]){ //Si on appuye à la position du bouton menu on étein la musique et on revient au menu 
    Mix_HaltMusic();
    C->onMenu = 1;
    C->color.r = 0, C->color.g = 0, C->color.b = 0;
  }
  if (in->mouseY > 265 && in->mouseX > 410 && in->mouseY <= 265+60 && in->mouseX <= 410+60 && in->mouseButtons[SDL_BUTTON_LEFT]) //Si on appuye à la postion R on change de couleur 
    C->colorChoice = 1;
  if (in->mouseY > 340 && in->mouseX > 410 && in->mouseY <= 340+60 && in->mouseX <= 410+60 && in->mouseButtons[SDL_BUTTON_LEFT])//Même chose avec G
    C->colorChoice = 0;
  if (in->mouseY > 415 && in->mouseX > 410 && in->mouseY <= 415+60 && in->mouseX <= 410+60 && in->mouseButtons[SDL_BUTTON_LEFT])// Même chose avec B
    C->colorChoice = 2;
  if (in->key[SDLK_p]){//Si on appuye sur p on met la musique en pause
    if(Mix_PausedMusic() == 1)
      Mix_ResumeMusic(); 
    else
      Mix_PauseMusic();
  }
}
