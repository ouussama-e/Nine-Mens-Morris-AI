/*
 * Board.h
 *
 *  Created on: Nov 13, 2015
 *      Author: Eran
 */

#ifndef BOARD_H_
#define BOARD_H_
#include<iostream>
#include<string>
#include <SDL/SDL.h>
#include "Node.h"


int retour1(SDL_Surface *ecran);
int grandLogo();
void menuPrincipal(SDL_Surface *ecran);
void jouer(SDL_Surface *ecran);
void levels(SDL_Surface *ecran);
void JoueurVcJoueur(SDL_Surface *ecran);
void JoueurvcMachine(SDL_Surface *ecran, int niveau);
static std::string currentTurn = "";
class Node; //needs the class information about many things
// That class stores the info for a specific board
class Board{
	private:
	char unusedDots[2]; //the number of unplaced dots,the first cell is WHITE the second is black
	char leftDots[2]; //the number of placed dots,the first cell is WHITE the second is BLACK
	Node *myBoard[24]; //myGaming Board
	void initialize(); //init the board with dots
public:
	Board();
	~Board(); //same as ~Board(); //(default constructor)

	static void PrintBoard(SDL_Surface *ecran);
    void remplir_plateau(SDL_Surface *ecran);
    int ChoixToPosition();

	void setPlayer(int n,Node::Player x);
	std::string getPlayer(int n);
	bool isTrio(int pos, Node::Player player);
	bool isVerticalTrio(int pos, Node::Player player);
	bool isHorizontalTrio(int pos, Node::Player player);
	bool hasMove(Node::Player player);//checks if the player has moves
	bool isNeighbor(int src,int dst); //checks if the move is legal(the point has the appropriate neighbore
	int getUnusedDotsWhite(){return (unusedDots[0]);};
	int getUnusedDotsBlack(){return (unusedDots[1]);};
	int getLeftDotsWhite(){return leftDots[0];};
	int getLeftDotsBlack(){return leftDots[1];};
	Node::Player getPlayerR(int n);
	void decreaseunUsedDots(Node::Player player){this->unusedDots[player]-=1;};
	void increaseLeftDots(Node::Player player){this->leftDots[player]+=1;};
	void decreaseLeftDots(Node::Player player){this->leftDots[player]-=1;};
	int nbr_pierre();
    void board_to_table(int table[24]);
    void table_to_board(int tanble[24]);
};



#endif /* BOARD_H_ */
