

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <string>
class Node {

private:
	int location; //location of one point on the board{0-24}

public:
    enum Player {
					WHITE,
					BLACK,
					NEUTRAL
				};
	static int positionsGenerated;  //points added(moves)
	static int positionsDeleted; //points removed(moves)
	Node *up; //across the point(up)
	Node *down; //across the point(down)
	Node *left; //across the point(left)
	Node *right; //across the point(right)
	Player player; //holds the player info(color)
	Node(int location); //constructor
	int getLocation(); //returns int(location)
	std::string getPlayer();//(who own this point?)
	Node::Player getPlayerRaw(); //return player as Player var
	void setPlayer(Player x);//set the right player(W\B) on the point
};


#endif /* NODE_H_ */
