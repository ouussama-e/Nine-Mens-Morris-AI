
#include "Node.h"

int Node::positionsDeleted = 0;
int Node::positionsGenerated = 0;
//constructor : init on point (Node)
Node::Node(int location)
:up(NULL), down(NULL), left(NULL), right(NULL),player(NEUTRAL)
{
	positionsGenerated++; //add one to the counter
	this->location = location; //the check is outside
}
//sets this Node with Player(Black\White)
void Node::setPlayer(Player x) {
	this->player = x;
}
//gets who "own" that specific point at player var format
Node::Player Node::getPlayerRaw(){
	return player;
}
//gets who "own" that specific point
std::string Node::getPlayer() {
	if (player == NEUTRAL)
		return "o";
	else if (player == BLACK)
		return "B";
	else
		return "W";
}
//returns the location of the Node
int Node::getLocation(){
	return this->location;
}
