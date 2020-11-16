#ifndef SRC_BOT_H_
#define SRC_BOT_H_
#include "Move.h"



class Bot
{
	private:
		int ownMap[10][10];
		int mapCopy[10][10];
		vector<Move> possibleMoves;
	public:
		Bot();
		int* getNextMove(int map[], int nextMove[]);
		bool isLegalMove(int x1, int y1, int x2, int y2);
		bool isLegalH(int x1, int y1, int x2, int y2);
		bool isLegalV(int x1, int y1, int x2, int y2);
		void fillMap(int map[]);
		void findPossibleMoves(int bestMove[]);
		int calculateScore(int x1, int y1, int x2, int y2);
		int findSets();
		void findBestMove(int bestMove[]);
		void printMap();
		void printMapCopy();
};

Bot::Bot() //initialise Bot class - constructor
{

}

void Bot::fillMap(int map[]){
	for(int i=0; i<100; i++){
		ownMap[i/10][i%10] = map[i];
	}
}

void Bot::findPossibleMoves(int bestMove[]){
	possibleMoves.clear();
	for(int x =0; x<10; x++){
		for(int y=0; y<10; y++){
			if(x!=9 && isLegalMove(x,y,x+1,y)){
				int score = calculateScore(x,y,x+1,y);
				Move m(x,y,x+1,y,score);
				possibleMoves.push_back(m);
			}
			if(y!=9 && isLegalMove(x,y,x,y+1)){
				int score = calculateScore(x,y,x,y+1);
				Move m(x,y,x,y+1,score);
				possibleMoves.push_back(m);
			}
		}
	}

	findBestMove(bestMove);
}

void Bot::findBestMove(int bestMove[]){
	int max = 0;
	for(int i=0; i<possibleMoves.size(); i++){
		if(possibleMoves[i].getScore()>max){
			possibleMoves[i].getCoordinates(bestMove);
			max = possibleMoves[i].getScore();
		}
	}
	cout<<"best move is: "<<bestMove[0]<<bestMove[1]<<bestMove[2]<<bestMove[3]<<" with a score of "<<max<<endl;
}

int Bot::calculateScore(int x1, int y1, int x2, int y2){
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			mapCopy[x][y] = ownMap[x][y];
		}
	}
	swap(mapCopy[x1][y1], mapCopy[x2][y2]);
	int score = findSets();
	return score;
}


int Bot::findSets(){
	int totalScore = 0;
	for(int x=0; x<10; x++){
		int tempScore = 1;
		for(int y=0; y<10; y++){
			if(y>0 && mapCopy[x][y] == mapCopy[x][y-1] && mapCopy[x][y]!=0){
				tempScore++;

			} else if(y>0 && mapCopy[x][y] != mapCopy[x][y-1] && tempScore>2){
				totalScore += tempScore;
				tempScore = 1;
			} else {
				tempScore = 1;
			}
		}
		if(tempScore>2){
			totalScore += tempScore;
		}
	}

	for(int y=0; y<10; y++){
			int tempScore = 1;
			for(int x=0; x<10; x++){
				if(x>0 && mapCopy[x][y] == mapCopy[x-1][y] && mapCopy[x][y]!=0){
					tempScore++;
				} else if(y>0 && mapCopy[x][y] != mapCopy[x-1][y] && tempScore>2){
					totalScore += tempScore;
					tempScore = 1;
				} else {
					tempScore = 1;
				}
			}
			if(tempScore>2){
				totalScore += tempScore;
			}
		}

	return totalScore;
}

bool Bot::isLegalMove(int x1, int y1, int x2, int y2){
	if((isLegalH(x1,y1,x2,y2) || isLegalV(x1,y1,x2,y2)) && ownMap[x1][y1]!=0 && ownMap[x2][y2]!=0){
		return true;
	}
	return false;
}

bool Bot::isLegalH(int x1, int y1, int x2, int y2){
	if((y2>=y1 && y1>1 && ownMap[x2][y2]==ownMap[x1][y1-1] && ownMap[x2][y2]==ownMap[x1][y1-2])
				|| (y1>=y2 && y2>1 && ownMap[x1][y1]==ownMap[x2][y2-1] && ownMap[x1][y1]==ownMap[x2][y2-2])
				|| (y2>=y1 && y2<8 && ownMap[x1][y1]==ownMap[x2][y2+1] && ownMap[x1][y1]==ownMap[x2][y2+2])
				|| (y1>=y2 && y1<8 && ownMap[x2][y2]==ownMap[x1][y1+1] && ownMap[x2][y2]==ownMap[x1][y1+2])
				|| (x1!=x2 && y1>0 && y1<9 && ownMap[x2][y2]==ownMap[x1][y1+1] && ownMap[x2][y2]==ownMap[x1][y1-1])
				|| (x1!=x2 && y2>0 && y2<9 && ownMap[x1][y1]==ownMap[x2][y2+1] && ownMap[x1][y1]==ownMap[x2][y2-1])){
			return true;
		} else {
			return false;
		}
}

bool Bot::isLegalV(int x1, int y1, int x2, int y2){
	if((x1>=x2 && x1>1 && ownMap[x2][y2]==ownMap[x1-2][y1] && ownMap[x2][y2]==ownMap[x1-1][y1])
			|| (x2>=x1 && x2>1 && ownMap[x1][y1]==ownMap[x2-2][y2] && ownMap[x1][y1]==ownMap[x2-1][y2])
			|| (x1>=x2 && x1<8 && ownMap[x2][y2]==ownMap[x1+2][y1] && ownMap[x2][y2]==ownMap[x1+1][y1])
			|| (x2>=x1 && x2<8 && ownMap[x1][y1]==ownMap[x2+2][y2] && ownMap[x1][y1]==ownMap[x2+1][y2])
			|| (y1!=y2 && x1>0 && x1<9 && ownMap[x2][y2]==ownMap[x1-1][y1] && ownMap[x2][y2]==ownMap[x1+1][y1])
			|| (y1!=y2 && x2>0 && x2<9 && ownMap[x1][y1]==ownMap[x2-1][y2] && ownMap[x1][y1]==ownMap[x2+1][y2])){
		return true;
	} else {
		return false;
	}
}

int* Bot::getNextMove(int map[], int nextMove[]) //decide and return next move, given the current state of the map.
{
	int bestMove[4];
	fillMap(map);
	findPossibleMoves(bestMove);

	int tempx1 = bestMove[0];
	int tempy1 = bestMove[1];
	int tempx2 = bestMove[2];
	int tempy2 = bestMove[3];
	nextMove[0] = tempx1;
	nextMove[1] = tempy1;
	nextMove[2] = tempx2;
	nextMove[3] = tempy2;
	return nextMove;
}
void Bot::printMap(){

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(j != 9){
                cout << ownMap[i][j] << " ";
            } else {
                cout << ownMap[i][j];
            }
        }
        cout << endl;
    }
    cout<<endl;
}

void Bot::printMapCopy(){

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(j != 9){
                cout << mapCopy[i][j] << " ";
            } else {
                cout << mapCopy[i][j];
            }
        }
        cout << endl;
    }
    cout<<endl;
}



#endif /* SRC_BOT_H_ */
