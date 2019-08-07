#include "TTF.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>


void Ecriture(SDL_Surface *ecran, char msg[40], int temp)
{
    SDL_Surface *texte = NULL, *fond = NULL, *background = NULL;
    SDL_Rect position, position_texte;

    position.x = 100; position.y = 140;
    position_texte.x = 110; position_texte.y = 180;

    TTF_Font *police = NULL;
    SDL_Color couleur_texte = {255, 255, 255};
    int continuer = 1;
    TTF_Init();
    fond = IMG_Load("assets/fond-msg.png");
    /* Chargement de la police */
    police = TTF_OpenFont("fonts/arial.ttf", 40);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, msg, couleur_texte);

    int tempactuel = 0, tempinitial = 0;

         SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */
         SDL_BlitSurface(texte, NULL, ecran, &position_texte); /* Blit du texte */
         SDL_Flip(ecran);
    while(continuer)
    {
    tempactuel = SDL_GetTicks();
    if(tempactuel - tempinitial > temp)
        break;
    }
TTF_CloseFont(police);
TTF_Quit();
SDL_FreeSurface(texte);
}
