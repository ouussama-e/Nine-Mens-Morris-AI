

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_
#include "nine.h"
#include <cstring>
#include <stdlib.h>

class GameController {
private:
		int White_pos; //the current position of white
		int Black_pos; //the current position of black
		std::string White_name; //stores the name of the player
		std::string Black_name; //stores the name of the player
		Node::Player currentTurn; //who is currenty playing
		Node::Player winner; //who won the game!
public:
	enum GameStatus {
			WHITE_WINS,
			BLACK_WINS,
			GAME_OVER,
			PLAYING
			};
	Board *myGame; //my Board for the game
	//SDL_Rect userInput;  //il faut la transformer vers event.button.x
	GameController(); //calling the Board Constructor
	GameStatus status;
	void changePlayer();//change player
	void writecurrentPos(int pos,Node::Player player);//writes the current player position on board
	void movePlayer();//move player(phase2)
	void eatPlayer(SDL_Surface *ecran, Node::Player player);//eats the opponent player
	void endGame();//ends the game from anypoint using "quit" syntax
	void declareAndQuit(SDL_Surface *ecran); //declare the winner and stop the program
	void Game(SDL_Surface *ecran); //gets info from users and start the 2 phases of game
	void GameAI(SDL_Surface *ecran, int niveau);
	void GamePhase1(SDL_Surface *ecran); //the first phase of the game (position phase)
	void GamePhase1_AI(SDL_Surface *ecran, int niveau); //the first phase of the game (position phase)
	void GamePhase2(SDL_Surface *ecran);//the second phase of game(play's phase)
	void GamePhase2_AI(SDL_Surface *ecran, int niveau);

	bool all_is_trio(Node::Player);
	//void GamePhase3(SDL_Surface *ecran);
	void sixMovesonly(); //for testing method only!
};

#endif /* GAMECONTROLLER_H_ */
