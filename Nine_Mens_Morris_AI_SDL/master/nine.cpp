
//the main class that runs and manage the game

#include "nine.h"
#include "constantes.h"
#include "TTF.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Music.h"
void JoueurVcJoueur(SDL_Surface *ecran);

int main(int argc, char *argv[])
{
    SDL_Surface *ecran;
    // Chargement de la vidéo et de l'audio
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_RESIZABLE | SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("MOULIN", NULL);
    music("son1.mp3");
    menuPrincipal(ecran);

    SDL_Flip( ecran);
    SDL_FreeSurface(ecran);
    SDL_Quit();
	return 0;
}

void JoueurVcJoueur(SDL_Surface *ecran){

    GameController *t1 = new GameController();
    Board::PrintBoard(ecran);
	t1->Game(ecran);
	delete(t1);

}

void JoueurvcMachine(SDL_Surface *ecran, int niveau){
   GameController *t1 = new GameController();
   Board::PrintBoard(ecran);
   t1->GameAI(ecran, niveau);
   delete (t1);
}
