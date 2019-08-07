#ifndef GAME_H
#define GAME_H
#include "SDL/SDL.h"

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
	SDL_Rect position_choix;
	GameController(); //calling the Board Constructor
	GameStatus status;
	void changePlayer();//change player
	void poser_pierre(SDL_Surface *ecran);
	void movePlayer();//move player(phase2)
	void eatPlayer(Node::Player player);//eats the opponent player
	void endGame();//ends the game from anypoint using "quit" syntax
	void declareAndQuit(SDL_Surface *ecran); //declare the winner and stop the program
	void Game(SDL_Surface *ecran); //gets info from users and start the 2 phases of game
	void GamePhase1(SDL_Surface *ecran); //the first phase of the game (position phase)
	void GamePhase2(SDL_Surface *ecran); //the second phase of game(play's phase)
	void GamePhase3(SDL_Surface *ecran);
	void sixMovesonly(); //for testing method only!
};
#endif // GAME_H
