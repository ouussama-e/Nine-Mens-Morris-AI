
#include "GameController.h"
#include "Board.h"
#include "TTF.h"
#include <SDL/SDL_ttf.h>
#include <ctime>
#include "heuristike.h"
#include "pravila.h"  // règles.h
#include "alphabeta.h"

//creating empty board and init the vars
GameController::GameController() {
	this->myGame =  new Board();
	White_pos = 0; //the current position of white
	Black_pos = 0; //the current position of black
	White_name = "White";
	Black_name = "Black";
	currentTurn = Node::BLACK; //who is currently playing
	status = PLAYING;
	winner = Node::NEUTRAL;
}
//eats the rival player
void GameController::eatPlayer( SDL_Surface *ecran, Node::Player player)
{
    Ecriture(ecran, "VOUS AVEZ UN MOULIN", 1000); SDL_Delay(1000);
    Ecriture(ecran, "ELIMINEZ UN PION", 1000); SDL_Delay(1000);
    myGame->remplir_plateau(ecran);

	int eatPos = myGame->ChoixToPosition();
	Node::Player p = myGame->getPlayerR(eatPos);
      Node::Player Other_player;
      if(player == Node::BLACK) Other_player = Node::WHITE;
      else Other_player = Node::BLACK;

  if(all_is_trio(Other_player) == false)
  {  // le cas où on a au moins une case qui n'appartient pas à un moulin
	while(eatPos == -1 || ( p == player) || (p == Node::NEUTRAL) || ( myGame->isTrio(eatPos, p) == true ) )
	{   if( myGame->isTrio(eatPos, myGame->getPlayerR(eatPos)) == true)
	       {Ecriture(ecran, "C'EST DEJA UN MOULIN", 1000); SDL_Delay(1000);}
	    else if( p == Node::NEUTRAL )
		   {Ecriture(ecran, "LA CASE EST DEJA VIDE", 1000); SDL_Delay(1000);}
		else
		   {Ecriture(ecran, "CE PION EST LE TIEN", 1000); SDL_Delay(1000);}
		myGame->remplir_plateau(ecran);
		eatPos = myGame->ChoixToPosition();
		p =myGame->getPlayerR(eatPos);
	}
  }

  else {
    while(eatPos == -1 || ( p == player) || (p == Node::NEUTRAL) )
	{
	    if( p == Node::NEUTRAL )
		   {Ecriture(ecran, "LA CASE EST DEJA VIDE", 1000); SDL_Delay(1000);}
		else
		   {Ecriture(ecran, "CE PION EST LE TIEN", 1000); SDL_Delay(1000);}
		myGame->remplir_plateau(ecran);
		eatPos = myGame->ChoixToPosition();
		p =myGame->getPlayerR(eatPos);
	}
  }

	myGame->setPlayer(eatPos,Node::NEUTRAL);
	myGame->decreaseLeftDots(player);

}
//checks if the dots is legal and convert it to pos(int),if it is illegal return -1;
void GameController::endGame()
{
	if(currentTurn == Node::WHITE)winner = Node::BLACK;
	else winner = Node::WHITE;
	delete(myGame);
	status=GAME_OVER;
}
void GameController::declareAndQuit(SDL_Surface *ecran){

	/*END OF GAME declaring the winner*/
	if(winner == Node::WHITE) {Ecriture(ecran,"white won !", 5000); SDL_Delay(5000);}
	else if(winner == Node::BLACK) {Ecriture(ecran, "black won!", 5000); SDL_Delay(5000);}


	/*prints the winner*/
	exit (EXIT_FAILURE);
}

//writes the current player position on board
void GameController::writecurrentPos(int pos,Node::Player player)
{
	if(player == Node::WHITE)White_pos = pos;
	else
		Black_pos=pos;
}
//changes the player after every move
void GameController::changePlayer(){
	if(this->currentTurn == Node::WHITE)this->currentTurn = Node::BLACK;
	else currentTurn = Node::WHITE;
	return;
}

// une fonction return true si tous le jeu est des moulin et false si on a une pierre sans trio
bool GameController::all_is_trio(Node::Player player)
{ for(int i=0; i<24; i++)
     if( myGame->isTrio(i, player) == false )
         return false;
  return true;
}
//the "main func"
void GameController::Game(SDL_Surface *ecran)
{
	status = PLAYING;
	/*************************************************/

	/*************************************************/
	//as long as there is a dots to put and the input is different than "quit"
	//continue with phase1
	while(myGame->getUnusedDotsWhite() || myGame->getUnusedDotsBlack())
	{
		GamePhase1(ecran);
		if(status==GAME_OVER)
		{
			declareAndQuit(ecran); //if the player enter QUIT
		}
	}
	/*Phase 1 of the game completed*/
	//lets sets the Black to be first
	currentTurn = (Node::BLACK);
	status = PLAYING;
    Ecriture(ecran, "PHASE 1 EST TERMINEE", 1000);SDL_Delay(1000);
    myGame->remplir_plateau(ecran);


	while((myGame->getLeftDotsBlack()>=3) && (myGame->getLeftDotsWhite()>=3) && (myGame->hasMove(Node::WHITE)) && (myGame->hasMove(Node::BLACK)))
	{
		GamePhase2(ecran);
		if(status==GAME_OVER)
		declareAndQuit(ecran); //if the player enter QUIT
	}
// cela ne fonctionne pas
	if(myGame->hasMove(Node::WHITE)==false || myGame->getLeftDotsWhite()<3)
	{
		status = BLACK_WINS;
    }
	else
	{
		status = WHITE_WINS;
	}
	/*sets who won the game*/

	if(status == WHITE_WINS)winner = Node::WHITE;
	else winner = Node::BLACK;
	declareAndQuit(ecran);
}

//the Position phase
void GameController::GamePhase1(SDL_Surface *ecran){

	int pos = 1;
    pos = myGame->ChoixToPosition();
    while( pos < 0 || pos > 23)
        {Ecriture(ecran, "Votre choix est incompatible", 1000); SDL_Delay(1000);
         myGame->remplir_plateau(ecran);
         pos = myGame->ChoixToPosition();
        }
    //if the input is outOfRange or the dot is occupied, try again
	while(pos == -1 || ((myGame->getPlayerR(pos))  != Node::NEUTRAL))
	{   Ecriture(ecran, "Cette case est pleine", 1000);SDL_Delay(1000);
	    myGame->remplir_plateau(ecran);
		pos = myGame->ChoixToPosition(); }
	/*************************************************/
	//put the dot
	myGame->setPlayer(pos,currentTurn);
	//write the current pos of player white\black
	writecurrentPos(pos,currentTurn);
	//decrease the unused dots counter per player
	myGame->decreaseunUsedDots(currentTurn);
	myGame->increaseLeftDots(currentTurn);
	//change turn
	myGame->remplir_plateau(ecran);
	//check if there is a mill

	if(myGame->isTrio(pos,currentTurn))
	{   eatPlayer(ecran, currentTurn);
		myGame->remplir_plateau(ecran); }

	changePlayer();
}


void GameController::GamePhase2(SDL_Surface *ecran)
{

	int src_pos = 0;
	int dst_pos = 0;
	//string src_dot = "aO";//2 chars length //sample
	//string dst_dot = "a7";//2 chars length //sample
	myGame->remplir_plateau(ecran);

	/*prints the player names turn by turn*/
	/***************************************************************/
	//if quit has been entered quit the game!
	/*checks the user input*/

	do{
		//as long the position is out of boundries \ illegal move
		//get into while
		src_pos = myGame->ChoixToPosition();
		dst_pos = myGame->ChoixToPosition();

		//quit
			if((src_pos == -1) || (dst_pos == -1))
			{
				Ecriture(ecran, "please try again", 500); SDL_Delay(500);
				myGame->remplir_plateau(ecran);
			}

	}while((src_pos == -1) || (dst_pos == -1) );

	/****************************************************************/
	/****************************************************************/
	/****************************************************************/
	//lets check if the move is legal(the dot is not occupied)
	/*if not, return to phase2 again*/
	if((myGame->getPlayerR(src_pos) == Node::NEUTRAL))
	{
		Ecriture(ecran, "The Dot is not occupied by any player!", 500); SDL_Delay(500);
		myGame->remplir_plateau(ecran);
		return;
	}
	/*the point doesnt belong to you*/
	if((myGame->getPlayerR(src_pos) != currentTurn) && (myGame->getPlayerR(src_pos) != Node::NEUTRAL))
	{
		{
			Ecriture(ecran, "The Dot is doesn't belong to you!", 500);SDL_Delay(500);
			myGame->remplir_plateau(ecran);
			return;
		}
	}
	/*the DST point isn't empty*/
	if((myGame->getPlayerR(dst_pos) == Node::WHITE) ||(myGame->getPlayerR(dst_pos) == Node::BLACK))
	{
		{
			Ecriture(ecran, "The destination Dot is occupied by player!", 500); SDL_Delay(500);
			myGame->remplir_plateau(ecran);
			return;
		}
	}

	/*Enter check to see if the point is neigbore*/
	/*if not, return to phase2 again*/
	if((myGame->isNeighbor(src_pos,dst_pos) == false))
	{
		Ecriture(ecran, "The request dot is not adjacent", 500); SDL_Delay(500);
		myGame->remplir_plateau(ecran);
		return;
	}



	myGame->setPlayer(src_pos,Node::NEUTRAL);//Move the dot
	myGame->setPlayer(dst_pos,currentTurn);//Move the dot
	/*check if there is mill*/
	if(myGame->isTrio(dst_pos,currentTurn))
	{
		eatPlayer(ecran, currentTurn);
		myGame->remplir_plateau(ecran);
	}
	//change turn
	changePlayer();
}

// voici les fonctions du AI
//the "main func"
void GameController::GameAI(SDL_Surface *ecran, int niveau)
{
	status = PLAYING;
	//as long as there is a dots to put and the input is different than "quit"
	//continue with phase1
	while(myGame->getUnusedDotsWhite() || myGame->getUnusedDotsBlack())
	{
		GamePhase1_AI(ecran, niveau);
		if(status==GAME_OVER)
		{
			declareAndQuit(ecran); //if the player enter QUIT
		}
	}
	/*Phase 1 of the game completed*/
	//lets sets the Black to be first
	currentTurn = (Node::BLACK);
	status = PLAYING;
    Ecriture(ecran, "PHASE 1 EST TERMINEE", 1000);SDL_Delay(1000);
    myGame->remplir_plateau(ecran);


	while((myGame->getLeftDotsBlack()>=3) && (myGame->getLeftDotsWhite()>=3) && (myGame->hasMove(Node::WHITE)) && (myGame->hasMove(Node::BLACK)))
	{
		GamePhase2_AI(ecran, niveau);
		if(status==GAME_OVER)
		declareAndQuit(ecran); //if the player enter QUIT
	}
// cela ne fonctionne pas
	if(myGame->hasMove(Node::WHITE)==false || myGame->getLeftDotsWhite()<3)
	{
		status = BLACK_WINS;
    }
	else
	{
		status = WHITE_WINS;
	}
	/*sets who won the game*/


	if(status == WHITE_WINS)winner = Node::WHITE;
	else winner = Node::BLACK;
	declareAndQuit(ecran);
}

//the Position phase
void GameController::GamePhase1_AI(SDL_Surface *ecran, int niveau){

int pos = 1;
int deplacer[3] = {-1, -1, -1};
  // le jeu de la machine
  if( currentTurn == Node::BLACK){
    int Table[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int joueurActuel = -1; // 1 est la machine, -1 est le joueur
    int profondeurStable = 3;
    int profondeur = profondeurStable;
    int coef[19] = {11, 11, 2, 11, 10, 16, 3, 16, 21, 10, 31, 13, 42, 1, 1086, 10, 3, 19, 1200};

    int i;

    int placementLegal = 101;

    int resultat[4] = {0, 0, 0, 0};
    int pierre_sur_table = 10;

    myGame->board_to_table(Table);
    nbrBlockee(Table, resultat);
    if ((pierre_sur_table >= 18) && ((resultat[2] + resultat[3]) > 14))
        profondeur = profondeurStable + 1;
    else if (pierre_sur_table == 2 || pierre_sur_table == 3 || pierre_sur_table == 4 || pierre_sur_table == 5 || resultat[2] == 3 || resultat[3] == 3)
        profondeur = profondeurStable - 1;
    else
        profondeur = profondeurStable;

    if( niveau == 1 ){ max(Table, -3000000, 3000000, deplacer, -1, -1, profondeur, pierre_sur_table, coef); }

    else if( niveau == 2){   alphabeta(Table, deplacer, profondeur, pierre_sur_table, coef); }

    else if( niveau == 3 ){  alphabeta(Table, deplacer, profondeur + 2, pierre_sur_table, coef); }

    pos = deplacer[0];
    if(deplacer[2] <= 23 && deplacer[2] >= 0)
       {Ecriture(ecran, "la machine mange", 500);
        SDL_Delay(500);
        myGame->remplir_plateau(ecran);
        Table[deplacer[2]] = 0;}
        myGame->table_to_board(Table);
}

	else{
    pos = myGame->ChoixToPosition();
    while( pos < 0 || pos > 23)
        {Ecriture(ecran, " Votre choix est incompatible ", 1000); SDL_Delay(1000);
         myGame->remplir_plateau(ecran);
         pos = myGame->ChoixToPosition();
        }
    //if the input is outOfRange or the dot is occupied, try again
	while(pos == -1 || ((myGame->getPlayerR(pos))  != Node::NEUTRAL))
	{   Ecriture(ecran, "Cette case est pleine", 1000);SDL_Delay(1000);
	    myGame->remplir_plateau(ecran);
		pos = myGame->ChoixToPosition(); }

	}
	/*************************************************/
	//put the dot
	myGame->setPlayer(pos,currentTurn);
	//write the current pos of player white\black
	writecurrentPos(pos,currentTurn);
	//decrease the unused dots counter per player
	myGame->decreaseunUsedDots(currentTurn);
	myGame->increaseLeftDots(currentTurn);
	 //change turn
	myGame->remplir_plateau(ecran);
	//check if there is a mill
	if(myGame->isTrio(pos,currentTurn))
	{  if(currentTurn == Node::WHITE)
	      { eatPlayer(ecran, currentTurn); myGame->remplir_plateau(ecran); }
	}
	changePlayer();

}


void GameController::GamePhase2_AI(SDL_Surface *ecran, int niveau)
{

	int src_pos = 0;
	int dst_pos = 0;
	int eat_pos = 0;
	//string src_dot = "aO";//2 chars length //sample
	//string dst_dot = "a7";//2 chars length //sample
	myGame->remplir_plateau(ecran);

	 int deplacer[3] = {-1, -1, -1};
  // le jeu de la machine
  if( currentTurn == Node::BLACK){

    int Table[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int joueurActuel = -1; // 1 est la machine, -1 est le joueur
    int profondeurStable = 3 ;
    int profondeur = profondeurStable;
    int coef[19] = {11, 11, 2, 11, 10, 16, 3, 16, 21, 10, 31, 13, 42, 1, 1086, 10, 3, 19, 1200};

    int i;

    int placementLegal = 101;
    int pierre_sur_table = 20;
    int resultat[4] = {0, 0, 0, 0};

    myGame->board_to_table(Table);

    nbrBlockee(Table, resultat);
    if ((pierre_sur_table >= 18) && ((resultat[2] + resultat[3]) > 14))
         profondeur = profondeurStable + 1;

    if( niveau == 1 ){  max(Table, -3000000, 3000000, deplacer, -1, -1, profondeur, pierre_sur_table, coef); }

    else if( niveau == 2){ alphabeta(Table, deplacer, profondeur, pierre_sur_table, coef); }

    else if( niveau == 3 ){  alphabeta(Table, deplacer, profondeur + 1, pierre_sur_table, coef);  }

    src_pos = deplacer[0];
    dst_pos = deplacer[1];
   // if( dst_pos <= 0 || dst_pos >= 24) { Ecriture(ecran, "la dst n'a pas changé ", 2000); SDL_Delay(2000); }

    if(deplacer[2] >= 0 && deplacer[2] <= 23)
      { Ecriture(ecran, "la machine mange", 500);
        SDL_Delay(1000);
        Table[deplacer[2]] = 0;
        myGame->remplir_plateau(ecran);
      }
    myGame->table_to_board(Table);


  }

else{
	do{
		//as long the position is out of boundries \ illegal move
		//get into while
		src_pos = myGame->ChoixToPosition();
		dst_pos = myGame->ChoixToPosition();

		//quit
			if((src_pos == -1) || (dst_pos == -1))
			{
				Ecriture(ecran, "please try again", 500); SDL_Delay(500);
				myGame->remplir_plateau(ecran);
			}

	}while((src_pos == -1) || (dst_pos == -1) );

	/****************************************************************/
	/****************************************************************/
	/****************************************************************/
	//lets check if the move is legal(the dot is not occupied)
	/*if not, return to phase2 again*/
	if((myGame->getPlayerR(src_pos) == Node::NEUTRAL))
	{
		Ecriture(ecran, "The Dot is not occupied by any player!", 500); SDL_Delay(500);
		myGame->remplir_plateau(ecran);
		return;
	}
	/*the point doesnt belong to you*/
	if((myGame->getPlayerR(src_pos) != currentTurn) && (myGame->getPlayerR(src_pos) != Node::NEUTRAL))
	{
		{
			Ecriture(ecran, "The Dot is doesn't belong to you!", 500);SDL_Delay(500);
			myGame->remplir_plateau(ecran);
			return;
		}
	}
	/*the DST point isn't empty*/
	if((myGame->getPlayerR(dst_pos) == Node::WHITE) ||(myGame->getPlayerR(dst_pos) == Node::BLACK))
	{
		{
			Ecriture(ecran, "The destination Dot is occupied by player!", 500); SDL_Delay(500);
			myGame->remplir_plateau(ecran);
			return;
		}
	}

	/*Enter check to see if the point is neigbore*/
	/*if not, return to phase2 again*/
	if((myGame->isNeighbor(src_pos, dst_pos) == false))
	{
		Ecriture(ecran, "The request dot is not adjacent", 500); SDL_Delay(500);
		myGame->remplir_plateau(ecran);
		return;
	}

}

	myGame->setPlayer(src_pos,Node::NEUTRAL);//Move the dot
	myGame->setPlayer(dst_pos,currentTurn);//Move the dot
	/*check if there is mill*/
	if(myGame->isTrio(dst_pos,currentTurn))
	{  if( currentTurn == Node::WHITE )
		   {eatPlayer(ecran, currentTurn);
		    myGame->remplir_plateau(ecran);}
	}
	//change turn
	changePlayer();
 }

