
#include <iostream>
#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "GameController.h"
#include "constantes.h"
#include "Node.h"
#include <SDL/SDl_image.h>
#include <SDL/SDL.h>
#include "TTF.h"
#include "Music.h"

#define taille_image 80

class Node;
using namespace std;
/*That Function initialize the game board
 * creates empty dots and link them to each other*/
void Board::initialize() {
	Board::unusedDots[Node::WHITE] = 9; //reset the number of turns at the position stage
	Board::unusedDots[Node::BLACK] = 9; //reset the number of turns at the position stage
	Board::leftDots[Node::WHITE] = 0; //reset each player with 9 turns
	Board::leftDots[Node::BLACK] = 0; //reset each player with 9 turns
	/*Now sets dot by dot and link them*/

	for(int p=0;p<24;p++){
		Board::myBoard[p] = new Node(p); //Calling the constructor of each point.(no default constructor is exist)
	}
	//Linkin all the points(it is massy)
	myBoard[0]->down = myBoard[9];myBoard[0]->right = myBoard[1];
	myBoard[1]->left = myBoard[0];myBoard[1]->right = myBoard[2]; myBoard[1]->down = myBoard[4];
	myBoard[2]->left = myBoard[1];myBoard[2]->down = myBoard[14];
	myBoard[3]->right = myBoard[4];myBoard[3]->down = myBoard[10];
	myBoard[4]->up = myBoard[1];myBoard[4]->left = myBoard[3];myBoard[4]->right=myBoard[5];myBoard[4]->down = myBoard[7];
	myBoard[5]->left = myBoard[4];myBoard[5]->down=myBoard[13];
	myBoard[6]->right=myBoard[7];myBoard[6]->down=myBoard[11];
	myBoard[7]->up=myBoard[4];myBoard[7]->left=myBoard[6];myBoard[7]->right=myBoard[8];
	myBoard[8]->left=myBoard[7];myBoard[8]->down=myBoard[12];
	myBoard[9]->up=myBoard[0];myBoard[9]->down=myBoard[21];myBoard[9]->right=myBoard[10];
	myBoard[10]->left = myBoard[9]; myBoard[10]->right = myBoard[11]; myBoard[10]->up = myBoard[3]; myBoard[10]->down = myBoard[18];
	myBoard[11]->left = myBoard[10]; myBoard[11]->up = myBoard[6]; myBoard[11]->down = myBoard[15];
	myBoard[12]->right = myBoard[13]; myBoard[12]->up = myBoard[8]; myBoard[12]->down = myBoard[17];
	myBoard[13]->left = myBoard[12]; myBoard[13]->right = myBoard[14]; myBoard[13]->up = myBoard[5]; myBoard[13]->down = myBoard[20];
	myBoard[14]->left = myBoard[13]; myBoard[14]->up = myBoard[2]; myBoard[14]->down = myBoard[23];
	myBoard[15]->right = myBoard[16]; myBoard[15]->up = myBoard[11];
	myBoard[16]->left = myBoard[15]; myBoard[16]->right = myBoard[17]; myBoard[16]->down = myBoard[19];
	myBoard[17]->left = myBoard[16]; myBoard[17]->up = myBoard[12];
	myBoard[18]->right = myBoard[19]; myBoard[18]->up = myBoard[10];
	myBoard[19]->left = myBoard[18]; myBoard[19]->right = myBoard[20]; myBoard[19]->up = myBoard[16]; myBoard[19]->down = myBoard[22];
	myBoard[20]->left = myBoard[19]; myBoard[20]->up = myBoard[13];
	myBoard[21]->right = myBoard[22]; myBoard[21]->up = myBoard[9];
	myBoard[22]->left = myBoard[21]; myBoard[22]->right = myBoard[23]; myBoard[22]->up = myBoard[19];
	myBoard[23]->left = myBoard[22]; myBoard[23]->up = myBoard[14];

}
/*constructor : calls initialize function*/
Board::Board()
{
	Board::initialize();
}
//destrcutor
Board::~Board()
{
	for(int p=0;p<24;p++)
			delete(Board::myBoard[p]); //delete each point from Heap!
}

//That function Prints the Game Board
void Board::PrintBoard(SDL_Surface *ecran)
{
SDL_Surface  *plateau = NULL;
SDL_Rect position_fond;
    plateau = IMG_Load("assets/plateau.png");
    position_fond.x = 0; position_fond.y = 0;  // initalisation du position
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
    SDL_BlitSurface(plateau, NULL, ecran, &position_fond);
    SDL_Flip(ecran);
}
//checks if the player has moves
bool Board::hasMove(Node::Player player)
{
	//we got the player color and now we will check his dots
	//if one of them has a neigbore dot empty
	//he can move
	//notice!that function has no position!
	//its checks all the player dots for available move
	int i=0;
	bool status = false;
	for(i=0;i<24;i++)
	{
		if(myBoard[i]->getPlayerRaw() == player)
		{
			//check 4 directions
			//if one of them is Neutral status will set to be true;
			if(myBoard[i]->up != NULL){
				if(myBoard[i]->up->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->down != NULL){
				if(myBoard[i]->down->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->right != NULL){
				if(myBoard[i]->right->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
			if(myBoard[i]->left != NULL){
				if(myBoard[i]->left->getPlayerRaw() == Node::NEUTRAL) status = true;
			}
		}
	}
	return status;
	}
//That function set player color at a specific spot(Node's array is private)
void Board::setPlayer(int n,Node::Player x)
{
		if(n<24 && n>=0)
		{
			myBoard[n]->setPlayer(x);
		}
}
// transform le choix du joueur a la position dans le board
int Board::ChoixToPosition()
{
 SDL_Rect userInput;
 SDL_Event event;

 //while( event.type != SDL_MOUSEBUTTONDOWN || event.type != SDL_KEYDOWN )
 int continuer = 1;
 while(continuer)
    {
 SDL_WaitEvent(&event);
 if( (event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) ) // si on voudrait sortir
 { continuer =0; exit(EXIT_SUCCESS); }

 else if( event.type == SDL_MOUSEBUTTONDOWN ) {
        continuer = 0;
        userInput.x = (int)(event.button.x / 85);
        userInput.y = (int)(event.button.y / 85);
       switch(userInput.y)
             {case 0:
                  switch(userInput.x)
                       {case 0: return 0;
                             break;
                        case 3: return 1;
                             break;
                        case 6: return 2;
                             break;
                        default: return -1; break;
                       }
                  break;
             case 1:
                 switch(userInput.x)
                     {case 1: return 3;
                           break;
                      case 3: return 4;
                           break;
                      case 5: return 5;
                           break;
                      default: return -1;  break;
                     }
                  break;
            case 2:
                switch(userInput.x)
                    {case 2: return 6;
                          break;
                     case 3: return 7;
                          break;
                     case 4: return 8;
                          break;
                     default: return -1; break;
                    }
                  break;
            case 3:
                switch(userInput.x)
                    {case 0: return 9;
                          break;
                     case 1: return 10;
                          break;
                     case 2: return 11;
                          break;
                     case 4: return 12;
                          break;
                     case 5: return 13;
                          break;
                     case 6: return 14;
                          break;
                     default: return -1; break;
                    }
                  break;
            case 4:
                switch(userInput.x)
                    {case 2: return 15;
                          break;
                     case 3: return 16;
                          break;
                     case 4: return 17;
                          break;
                     default: return -1; break;
                    }
                  break;
            case 5:
                switch(userInput.x)
                    {case 1: return 18;
                          break;
                     case 3: return 19;
                          break;
                     case 5: return 20;
                          break;
                     default: return -1; break;
                    }
                  break;
            case 6:
                switch(userInput.x)
                    {case 0: return 21;
                          break;
                     case 3: return 22;
                          break;
                     case 6: return 23;
                          break;
                     default: return -1; break;
                    }
                  break;
          } // switch(userInput.y)
        }
     }
}


//gets the player at the n Node
std::string Board::getPlayer(int n)
{
				return Board::myBoard[n]->getPlayer();
}

//gets the player at the n Node(return Player)
Node::Player Board::getPlayerR(int n)
{
	return myBoard[n]->getPlayerRaw();
}
//checks if the player has a HorizontalTrio
bool Board::isVerticalTrio(int pos, Node::Player player){
	bool status = false;
	//Three options
	if(myBoard[pos]->up == NULL)
	{
		status = (myBoard[pos]->down->player == myBoard[pos]->down->down->player) && (myBoard[pos]->down->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is up)
	}
	if(myBoard[pos]->down == NULL){
		status = (myBoard[pos]->up->player == myBoard[pos]->up->up->player) && (myBoard[pos]->up->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is down)
	}
	if((myBoard[pos]->up != NULL)&&(myBoard[pos]->down != NULL)){
		status = (myBoard[pos]->up->player == myBoard[pos]->down->player) && (myBoard[pos]->up->player == myBoard[pos]->player);
	}//if it is true status will get 1(the dot is in the middle)



	return status;
}
//checks if the player has a VerticalTrio
bool Board::isHorizontalTrio(int pos, Node::Player player){
	bool status = false;
	//Three options
	if(myBoard[pos]->left == NULL)
	{
		status = (myBoard[pos]->right->player == myBoard[pos]->right->right->player) && (myBoard[pos]->right->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is on the left)
	}
	if(myBoard[pos]->right == NULL){
		status = (myBoard[pos]->left->player == myBoard[pos]->left->left->player) && (myBoard[pos]->left->player == myBoard[pos]->player);
		//if it is true status will get 1(the dot is on the right)
	}
	if((myBoard[pos]->right != NULL)&&(myBoard[pos]->left != NULL)){
		status = (myBoard[pos]->right->player == myBoard[pos]->left->player) && (myBoard[pos]->right->player == myBoard[pos]->player);
	}//if it is true status will get 1(the dot is in the middle)
	return status;
}
//checks if the player had trio
bool Board::isTrio(int pos, Node::Player player){
	if(isVerticalTrio(pos,player)==true)
	{
		return true;
	}
	else if(isHorizontalTrio(pos,player)==true){
		return true;
	}
	return false;
}
//checks if the move is legal(the point has the appropriate neighbore
bool Board::isNeighbor(int src,int dst)
{
	bool status = false;
	for(int i=0;i<24;i++)
	{
		if(myBoard[i]->getLocation() == src)
				{
					//check 4 directions
					//if one of them is the neighbore status will set to be true;
			if(myBoard[i]->up!=NULL)
			{
				if(myBoard[i]->up->getLocation() == dst) status = true;
			}
			if(myBoard[i]->down!=NULL)
			{
				if(myBoard[i]->down->getLocation() == dst) status = true;
			}
			if(myBoard[i]->right!=NULL)
			{
				if(myBoard[i]->right->getLocation() == dst) status = true;
			}
			if(myBoard[i]->left!=NULL)
			{
				if(myBoard[i]->left->getLocation() == dst) status = true;
			}
				}
	}
	return status;
}



void menuPrincipal(SDL_Surface *ecran)
{
    int continuer = 1;
    SDL_Rect position_menu; // position de la surface et celle du choix du joueur
    SDL_Event event;
    SDL_Surface *image_menu;    // celle-la pour l'image de fond du menu
    image_menu = IMG_Load("assets/menu-entree.jpg"); // on a initialiser l'image de fond
    position_menu.x = 0; position_menu.y = 0;  // initalisation du position
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
    SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
    SDL_Flip(ecran);
     while(continuer)
     {
         SDL_WaitEvent(&event); /* Récupération de l'événement dans event*/
         switch(event.type) /* Test du type d'événement */
           {
             case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                  {continuer = 0;SDL_Flip(ecran);}
                  break;
             case SDL_KEYDOWN :
                  {continuer = 0;SDL_Flip(ecran);}
                  break;
             case SDL_MOUSEMOTION :
                  {   // zoom configuration button
                      if((event.motion.x > conf_min_x && event.motion.x < conf_max_x) &&(event.motion.y > conf_min_y && event.motion.y < conf_max_y))
                        {image_menu = IMG_Load("assets/menu-entree-options.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
                         SDL_Flip(ecran);}
                     // zoom play button
                     else if((event.motion.x > play_min_x && event.motion.x < play_max_x) &&(event.motion.y > play_min_y && event.motion.y < play_max_y))
                        {image_menu = IMG_Load("assets/menu-entree-play.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
                         SDL_Flip(ecran);}
                     else if((event.motion.x > acom_min_x && event.motion.x < acom_max_x) &&(event.motion.y > acom_min_y && event.motion.y < acom_max_y))
                        {image_menu = IMG_Load("assets/menu-entree-accomplishemet.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
                         SDL_Flip(ecran);}
                     else{
                        image_menu = IMG_Load("assets/menu-entree.jpg"); // on a initialiser l'image de fondposition_menu.x = 0; position_menu.y = 0;  // initalisation du position
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                        SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
                        SDL_Flip(ecran);
                     }
                     break;
                  }

             case SDL_MOUSEBUTTONDOWN :
                  { // press play
                      if((event.motion.x > play_min_x && event.motion.x < play_max_x) &&(event.motion.y > play_min_y && event.motion.y < play_max_y))
                          {jouer(ecran);
                           image_menu = IMG_Load("assets/menu-entree.jpg"); // on a initialiser l'image de fondposition_menu.x = 0; position_menu.y = 0;  // initalisation du position
                           SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                           SDL_BlitSurface(image_menu, NULL, ecran, &position_menu);
                           SDL_Flip(ecran);
                          }
                  }
                 break;
           }

     }
SDL_FreeSurface(image_menu);
}



void jouer(SDL_Surface *ecran){
    int continuer = 1;
    SDL_Rect position_fond; // position de la surface et celle du choix du joueur
    SDL_Event event;
    SDL_Surface *image_fond;    // celle-la pour l'image de fond du menu
    image_fond = IMG_Load("assets/players.jpg"); // on a initialiser l'image de fond
    position_fond.x = 0; position_fond.y = 0;  // initalisation du position
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
    SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
    SDL_Flip(ecran);
     while(continuer)
     {
         SDL_WaitEvent(&event); /* Récupération de l'événement dans event*/
         switch(event.type) /* Test du type d'événement */
           {
             case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                  {continuer = 0;}
                  break; //case SDL_QUIT:
             case SDL_KEYDOWN :
                  continuer = 0;
                  break; // case SDL_KEYDOWN :
             case SDL_MOUSEMOTION :
                  {// zoom two_players  button
                      if((event.motion.x > two_min_x && event.motion.x < two_max_x) &&(event.motion.y > two_min_y && event.motion.y < two_max_y))
                        {image_fond = IMG_Load("assets/players-1.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}
                     // zoom one_player button
                     else if((event.motion.x > one_min_x && event.motion.x < one_max_x) &&(event.motion.y > one_min_y && event.motion.y < one_max_y))
                        {image_fond = IMG_Load("assets/players-2.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}

                     else{
                        image_fond = IMG_Load("assets/players.jpg"); // on a initialiser l'image de fondposition_menu.x = 0; position_menu.y = 0;  // initalisation du position
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                        SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                        SDL_Flip(ecran);
                     }

                  }
                  break; // case SDL_MOUSEMOTION :
             case SDL_MOUSEBUTTONDOWN :
                 {   // press two_players button
                     if((event.button.x > two_min_x && event.button.x < two_max_x) &&(event.button.y > two_min_y && event.button.y < two_max_y))
                        { levels(ecran); }
                     // zoom one_player button
                     else if((event.motion.x > one_min_x && event.motion.x < one_max_x) &&(event.motion.y > one_min_y && event.motion.y < one_max_y))
                        { JoueurVcJoueur(ecran); }

                 }
                  break; //case SDL_MOUSEBUTTONDOWN :
           } // switch(event.type)
     }// while(continuer)
    SDL_FreeSurface(image_fond);
   }



void levels(SDL_Surface *ecran)
{int continuer = 1;
    SDL_Rect position_fond; // position de la surface et celle du choix du joueur
    SDL_Event event;
    SDL_Surface *image_fond;    // celle-la pour l'image de fond du menu
    image_fond = IMG_Load("assets/levels.jpg"); // on a initialiser l'image de fond
    position_fond.x = 0; position_fond.y = 0;  // initalisation du position
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
    SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
    SDL_Flip(ecran);
     while(continuer)
     {
         SDL_WaitEvent(&event); /* Récupération de l'événement dans event*/
         switch(event.type) /* Test du type d'événement */
           {
             case SDL_QUIT: /* Si c'est un événement de type "Quitter" */
                  {continuer = 0;}
                  break; //case SDL_QUIT:
             case SDL_KEYDOWN :
                  continuer = 0;
                  break; // case SDL_KEYDOWN :
             case SDL_MOUSEMOTION :
                  {   // zoom amateur  button
                      if((event.motion.x > l1_min_x && event.motion.x < l1_max_x) &&(event.motion.y > l1_min_y && event.motion.y < l1_max_y))
                        {image_fond = IMG_Load("assets/levels-1.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}
                      // zoom adventure button
                     else if((event.motion.x > l2_min_x && event.motion.x < l2_max_x) &&(event.motion.y > l2_min_y && event.motion.y < l2_max_y))
                        {image_fond = IMG_Load("assets/levels-2.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}
                      // zoom veteran button
                     else if((event.motion.x > l3_min_x && event.motion.x < l3_max_x) &&(event.motion.y > l3_min_y && event.motion.y < l3_max_y))
                        {image_fond = IMG_Load("assets/levels-3.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}

                     else{
                         image_fond = IMG_Load("assets/levels.jpg"); // on a initialiser l'image de fond
                         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255, 255));
                         SDL_BlitSurface(image_fond, NULL, ecran, &position_fond);
                         SDL_Flip(ecran);}

                  }
                  break; // case SDL_MOUSEMOTION :
                  // ceci conduirera vers un des algorithmes calculés

            case SDL_MOUSEBUTTONDOWN :
                 {   // Partie facile avec IA
                     if((event.button.x > l1_min_x && event.button.x < l1_max_x) &&(event.button.y > l1_min_y && event.button.y < l1_max_y))
                        { JoueurvcMachine(ecran, 1); }
                     // Partie intermediaire avec IA
                     else if((event.motion.x > l2_min_x && event.motion.x < l2_max_x) &&(event.motion.y > l2_min_y && event.motion.y < l2_max_y))
                        { JoueurvcMachine(ecran, 2); }
                     // Partie intermediaire avec IA
                     else if((event.motion.x > l3_min_x && event.motion.x < l3_max_x) &&(event.motion.y > l3_min_y && event.motion.y < l3_max_y))
                        { JoueurvcMachine(ecran, 3); }



                 }



           } // switch(event.type)
     }

}


void Board::remplir_plateau(SDL_Surface *ecran)
{
    SDL_Surface *black_dot, *white_dot;
    SDL_Rect position_dot; // position de la surface et celle du choix du joueur
    Board::PrintBoard(ecran);
    int i;
    // on a initialiser l'image de fond
    black_dot = IMG_Load("assets/noir.png");
    white_dot = IMG_Load("assets/blanc.png");
    for( i=0; i<24; i++)
    {
      switch(i)
      { case 0:   position_dot.x = 0*taille_image + 0;   position_dot.y = 0*taille_image + 0;   break;
        case 1:   position_dot.x = 3*taille_image + 10;   position_dot.y = 0*taille_image + 0;   break;
        case 2:   position_dot.x = 6*taille_image + 40;   position_dot.y = 0*taille_image + 0;   break;
        case 3:   position_dot.x = 1*taille_image + 0;   position_dot.y = 1*taille_image + 0;   break;
        case 4:   position_dot.x = 3*taille_image + 15;   position_dot.y = 1*taille_image + 0;   break;
        case 5:   position_dot.x = 5*taille_image + 35;   position_dot.y = 1*taille_image + 0;   break;
        case 6:   position_dot.x = 2*taille_image + 2;   position_dot.y = 2*taille_image + 7;   break;
        case 7:   position_dot.x = 3*taille_image + 14;   position_dot.y = 2*taille_image + 7;   break;
        case 8:   position_dot.x = 4*taille_image + 25;   position_dot.y = 2*taille_image + 5;   break;
        case 9:   position_dot.x = 0*taille_image + (- 5);   position_dot.y = 3*taille_image + 15;   break;
        case 10:  position_dot.x = 1*taille_image + 0;   position_dot.y = 3*taille_image + 15;   break;
        case 11:  position_dot.x = 2*taille_image + 10;   position_dot.y = 3*taille_image + 20;   break;
        case 12:  position_dot.x = 4*taille_image + 23;   position_dot.y = 3*taille_image + 20;   break;
        case 13:  position_dot.x = 5*taille_image + 35;   position_dot.y = 3*taille_image + 20;   break;
        case 14:  position_dot.x = 6*taille_image + 45;   position_dot.y = 3*taille_image + 20;   break;
        case 15:  position_dot.x = 2*taille_image + 7;   position_dot.y = 4*taille_image + 30;   break;
        case 16:  position_dot.x = 3*taille_image + 15;   position_dot.y = 4*taille_image + 27;   break;
        case 17:  position_dot.x = 4*taille_image + 23;   position_dot.y = 4*taille_image + 27;   break;
        case 18:  position_dot.x = 1*taille_image + (-3);   position_dot.y = 5*taille_image + 30;   break;
        case 19:  position_dot.x = 3*taille_image + 11;   position_dot.y = 5*taille_image + 35;   break;
        case 20:  position_dot.x = 5*taille_image + 33;   position_dot.y = 5*taille_image + 35;   break;
        case 21:  position_dot.x = 0*taille_image + (-3);   position_dot.y = 6*taille_image + 37;   break;
        case 22:  position_dot.x = 3*taille_image + 15;   position_dot.y = 6*taille_image + 37;   break;
        case 23:  position_dot.x = 6*taille_image + 39;   position_dot.y = 6*taille_image + 39;   break;
        }
      SDL_SetColorKey(black_dot, SDL_SRCCOLORKEY, SDL_MapRGB(black_dot->format, 255, 255, 255));
      SDL_SetColorKey(white_dot, SDL_SRCCOLORKEY, SDL_MapRGB(white_dot->format, 255, 255, 255));
      if( myBoard[i]->getPlayerRaw() ==  Node::BLACK)
         { SDL_BlitSurface(black_dot, NULL, ecran, &position_dot); }
      else if( myBoard[i]->getPlayerRaw() == Node::WHITE)
         { SDL_BlitSurface(white_dot, NULL, ecran, &position_dot); }
    }
  SDL_Flip(ecran);
  SDL_FreeSurface(black_dot);
  SDL_FreeSurface(white_dot);

}


int Board::nbr_pierre(){
    int nbr = 0;
    for(int i=0;i<24;i++)
       if(myBoard[i]->getPlayerRaw() != Node::NEUTRAL)
            nbr++;
    return nbr;
                   };

void Board::board_to_table(int table[24]){
for(int i=0;i<24;i++)
    {if(myBoard[i]->getPlayerRaw() == Node::BLACK)
        table[i] = 1;
     else if(myBoard[i]->getPlayerRaw() == Node::WHITE)
        table[i] = -1;
     else
        table[i] = 0;
    }
}

void Board::table_to_board(int table[24])
{ for(int i=0;i<24;i++)
    {if(table[i] == 1)
        myBoard[i]->setPlayer(Node::BLACK);
     else if(table[i] == -1)
        myBoard[i]->setPlayer(Node::WHITE);
     else
        myBoard[i]->setPlayer(Node::NEUTRAL);
    }

}
