#include "lib_std_facilities.h"
#include <fstream>
#include "GameEngine.h"
#include "Bot.h"


int main()
{
	GameEngine engine("C:\\Users\\itsupport\\eclipse-workspace\\hi\\src\\map10.txt", "C:\\Users\\itsupport\\eclipse-workspace\\hi\\src\\future10.txt"); //init game engine with map & future map.
	Bot myBot; //init Bot

	bool smart = false; //false = human, true = bot
	int x1, y1, x2, y2; //coordinates for next move. x1 y1 = tile 1 , x2 y2 = tile 2


	while(engine.hasLegalMoves()){ //while the game isn't over

		int *nextMove; // this is where the next move will be stored: [x1,y1,x2,y2]

		if(smart){ //bot player

			nextMove = myBot.getNextMove(engine.getMap(), nextMove); //get next move from bot.

			//assign coordinates of next move
			x1 = nextMove[0];
			y1 = nextMove[1];
			x2 = nextMove[2];
			y2 = nextMove[3];

		} else { //human player

			//ask human for input
			cout<<"Give the x-coordinate of the first tile"<<endl;
			cin>>x1;
			cout<<"Give the y-coordinate of the first tile"<<endl;
			cin>>y1;

			cout<<"Give the x-coordinate of the second tile"<<endl;
			cin>>x2;
			cout<<"Give the y-coordinate of the second tile"<<endl;
			cin>>y2;

			nextMove[0] = x1;
			nextMove[1] = y1;
			nextMove[2] = x2;
			nextMove[3] = y2;

		}


		//check if the move is legal
		if(engine.isLegalMove(x1, y1, x2, y2)){

			int points=1; //first move always gets 1 point per tile
			engine.makeMove(nextMove); //make the move
			cout<<endl;
			while(engine.needsUpdate()){ //while there is still tiles to break
				engine.updateMap(points); //update the map
				engine.restoreMap(); //copy map clone to original map
				engine.printMap(); //print map on terminal
				engine.printScore(); // print score on terminal

				points+=1; //next cycle of tile breaking gets +1 point
			}
		}
		else{ //move is invalid
			cout<<"Invalid move, try again"<<endl;
		}

	}

	//the end
	cout<<"The game has ended"<<endl;
	cout<<engine.getScore()<<endl;




	return 0;
}


