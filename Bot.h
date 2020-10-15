#ifndef SRC_BOT_H_
#define SRC_BOT_H_

class Bot
{
	public:
		Bot();
		int* getNextMove(int map[], int nextMove[]);
};

Bot::Bot() //initialise Bot class - constructor
{

}

int* Bot::getNextMove(int map[], int nextMove[]) //decide and return next move, given the current state of the map.
{
	nextMove[0] = 1;
	nextMove[1] = 2;
	nextMove[2] = 3;
	nextMove[3] = 4;

	return nextMove;
}



#endif /* SRC_BOT_H_ */
