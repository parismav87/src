#ifndef SRC_BOT_H_
#define SRC_BOT_H_


class Bot
{
	private:
		int ownMap[10][10];
	public:
		Bot();
		int* getNextMove(int map[], int nextMove[]);
		bool isLegalMove(int x1, int y1, int x2, int y2);
		bool isLegalH(int x1, int y1, int x2, int y2);
		bool isLegalV(int x1, int y1, int x2, int y2);
		void fillMap(int map[]);
};

Bot::Bot() //initialise Bot class - constructor
{

}

void Bot::fillMap(int map[]){
	for(int i=0; i<100; i++){
		ownMap[i/10][i%10] = map[i];
	}
}

bool Bot::isLegalMove(int x1, int y1, int x2, int y2){
	if(isLegalH(x1,y1,x2,y2) || isLegalV(x1,y1,x2,y2)){
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
	fillMap(map);
	for(int x =0; x<10; x++){
		for(int y=0; y<10; y++){
			if(y!=9 && isLegalMove(x,y,x,y+1)){
				nextMove[0] = x;
				nextMove[1] = y;
				nextMove[2] = x;
				nextMove[3] = y+1;
				return nextMove;
			}
			if(x!=9 && isLegalMove(x,y,x+1,y)){
				nextMove[0] = x;
				nextMove[1] = y;
				nextMove[2] = x+1;
				nextMove[3] = y;
				return nextMove;
			}
		}
	}
	nextMove[0] = 1;
	nextMove[1] = 2;
	nextMove[2] = 3;
	nextMove[3] = 4;
	return nextMove;
}





#endif /* SRC_BOT_H_ */
