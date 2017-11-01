void LoadAnimCat(Context *C){
  char *cat[] = {"./images/animation/catIdle.png", "./images/animation/catRight.png", "./images/animation/catIdle.png", "./images/animation/catLeft.png"};
  C->nbAnimCat = sizeof(cat)/sizeof(char*);
  C->animCat = malloc(C->nbAnimCat * sizeof(SDL_Surface*));
  for (int i = 0; i < C->nbAnimCat; i++){
    C->animCat[i] = IMG_Load(cat[i]);
  }
}

void LoadMenu(Context *C){
  char *menu[] = {"./images/menu/menuStart.png", "./images/menu/catMenu.png", "./images/menu/catMenu2.jpg", "./images/menu/menuNoir.png", "./images/menu/bordure.png", "./images/menu/menuOption.png", "./images/menu/optionNoir.png", "./images/menu/menuNoir2.png"};
  C->nbMenu = sizeof(menu)/sizeof(char*);
  C->menu = malloc(C->nbMenu * sizeof(SDL_Surface*));
  for (int i = 0; i < C->nbMenu; i++)
    C->menu[i] = IMG_Load(menu[i]);
}

void LoadText(Context *C){
  C->text = malloc(C->nbText*sizeof(SDL_Surface*));
  for (int i =0; i < C->nbText; i++)
    C->text[i]=NULL;
}

void LoadMusic(Context *C){
  C->musique = malloc(3*sizeof(Mix_Music*));
  C->musique[0] = Mix_LoadMUS("./musique/musique.mp3");
  C->musique[1] = Mix_LoadMUS("./musique/musique2.mp3");
  C->musique[2] = Mix_LoadMUS("./musique/musique3.mp3");
}
 
void LoadImgSpace(Context *C){
  char *spaceCat[] = { "./images/spaceCat/Bouton.bmp","./images/spaceCat/fond.png", "./images/spaceCat/gameOver.png", "./images/spaceCat/grille.bmp", "./images/spaceCat/casePleine.png", "./images/spaceCat/caseVide.png", "./images/spaceCat/menu.png"};
  C->nbImg = sizeof(spaceCat)/sizeof(char*);
  C->images = malloc(C->nbImg*sizeof(SDL_Surface*));
  for (int i = 0; i < C->nbImg; i++){
    C->images[i] = IMG_Load(spaceCat[i]);
  }
}

void LoadImgNorm(Context *C){
  char *norm[] = { "./images/normal/Bouton.bmp","./images/normal/fond.png", "./images/normal/gameOver.png", "./images/normal/grille.bmp", "./images/normal/casePleine.png", "./images/normal/caseVide.png", "./images/normal/menu.png"};
  C->nbImg = sizeof(norm)/sizeof(char*);
  C->images = malloc(C->nbImg*sizeof(SDL_Surface*));
  for (int i = 0; i < C->nbImg; i++){
    C->images[i] = IMG_Load(norm[i]);
  }
}

void LoadAll(Context *C){
  if(C->choice == 0)
    LoadImgNorm(C);
  else
    LoadImgSpace(C);
  LoadAnimCat(C);
}

void Blit(SDL_Surface* s, SDL_Surface *d, int x, int y){
  SDL_Rect R;
  R.x = x;
  R.y = y;
  SDL_BlitSurface(s, NULL, d, &R);
}

void Write(Context *C,TTF_Font *police, SDL_Surface *text, char *val, int x, int y){
  text = TTF_RenderText_Blended(police, val, C->color);
  Blit(text, C->ecran, x, y);
  SDL_FreeSurface(text);
}

void Init(Context *C, int x, int y){ 
    SDL_Init(SDL_INIT_VIDEO); // Initialise SDL et sa sortie video
    TTF_Init(); //Initialise TTF pour pouvoir écrire
    C->resX = x; //Définis la résolution de la surface principale
    C->resY = y;
    C->ecran = SDL_SetVideoMode(C->resX, C->resY, 32, SDL_HWSURFACE); //Initilise la surface principale
    C->police = TTF_OpenFont("./fonts/Doctor-Who.ttf", 30); //Ouvre les différentes police utilisés
    C->policeGo = TTF_OpenFont("./fonts/Doctor-Who.ttf", 100);
    C->policeMenu = TTF_OpenFont("./fonts/Star_Trek_future.ttf", 50);
    C->policeMenu2 = TTF_OpenFont("./fonts/Fipps.ttf", 70);
    C->nbText = 9; //Définis les différents int comme le nombre de text et les menus de base
    C->onMenu = 1; 
    C->menuType = 0;
    C->musicType = 0;
    C->choice = 1;
    C->colorChoice = 0;
    C->color.r = 0, C->color.g = 0, C->color.b = 0; //L'écriture de base est blacnhe
    SDL_WM_SetCaption("SDL_Mixer", NULL);  //Initialise la sortie audio pour la musique 
    SDL_WM_SetCaption("2048", NULL); // titre fenetre 
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);//Paramètre de la sortie audio
    LoadMenu(C); //Charge les différentes fonctions
    LoadText(C);
    LoadMusic(C);
}

void InitGrid(Context *C){
  LoadAll(C); // Charge les images
  if (C->choice == 1)
    C->color.r = 255, C->color.g = 255, C->color.b = 255;
  if (C->choice == 0)
    C->color.r = 0, C->color.g = 0, C->color.b = 0;
}

/**
 *\fn void Liberer(Context *C, grid g)
 *\return void
 *\brief On libère tous ce que l'on as allouer en mémoire
 */ 

void Liberer(Context *C, grid g){
  if (C->onMenu == 0){
    for (int i=0; i < C->nbImg; i++)
      SDL_FreeSurface(C->images[i]);
    free(C->images);
    for(int i=0; i < C->nbAnimCat; i++)
      SDL_FreeSurface(C->animCat[i]);
    free(C->animCat);
  }
  for(int i=0; i < C->nbText; i++)
    SDL_FreeSurface(C->text[i]);
  free(C->text);
  for (int i=0; i < C->nbMenu; i++)
    SDL_FreeSurface(C->menu[i]);
  free(C->menu);
  for(int i=0; i < 3; i++)
    Mix_FreeMusic(C->musique[i]);
  free(C->musique);
  SDL_FreeSurface(C->ecran);
  TTF_CloseFont(C->police);
  TTF_CloseFont(C->policeGo);
  TTF_CloseFont(C->policeMenu);
  TTF_CloseFont(C->policeMenu2);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
  delete_grid(g);
}
