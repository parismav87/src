
#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

class GameEngine{
private:
    int map[10][10];
    int fmap[10][10];
    string mapPath;
    string futurePath;
public:
    GameEngine(string mapPath, string futurePath);
    void readMap(string mapPath);
    void printMap();
    void readFuture(string futurePath);

    void makeMove(int x1, int y1, int x2, int y2);
    bool isLegalMove(int x1, int y1, int x2, int y2);
    bool isAdjecent(int x1, int y1, int x2, int y2);
    bool isVerticalLegal(int x1, int y1, int x2, int y2);
    bool isHorizontalLegal(int x1, int y1, int x2, int y2);
    bool isSameRow(int x1, int x2);
    bool isSameColumn(int y1, int y2);
    bool hasLegalMoves();
    void gameLoop();
    void updateMap(int count);
    //void breakThree();
    bool needsUpdate();
    void breakStuff(int x, int y);
    void breakHorizontal(int x, int y);
    void breakVertical(int x, int y);

};

GameEngine::GameEngine(string mapPath, string futurePath){
    this->mapPath = mapPath;
    this->futurePath = futurePath;
    readMap(mapPath);
    readFuture(futurePath);

}

void GameEngine::readMap(string mapPath){
    ifstream mapFile(mapPath);
    int counter = 0;
    int i=0;
    int j=0;
    if(mapFile){
        cout<<"map loaded"<<endl;
    }

    while(mapFile){
        string line;
        getline(mapFile, line);

        j=0; //j resets to 0 after each line
        for(char c: line){ //for each char in string
            if(c!=','){
                map[i][j] = atoi(&c); //char into int
                j++;
            }
        }
        i++; //next line

        counter++;
    }

    printMap();
    gameLoop();

}

void GameEngine::readFuture(string futurePath){
    ifstream mapFile(mapPath);
    int counter = 0;
    int i=0;
    int j=0;
    if(mapFile){
        cout<<"map future loaded"<<endl;
    }

    while(mapFile){
        string line;
        getline(mapFile, line);

        j=0; //j resets to 0 after each line
        for(char c: line){ //for each char in string
            if(c!=','){
                fmap[i][j] = atoi(&c); //char into int
                j++;
            }
        }
        i++; //next line

        counter++;
    }
}

void GameEngine::printMap(){
    int height = sizeof (map) / sizeof (*map);
    int width = sizeof (*map) / sizeof (int);
    //cout << height << width << endl;

    for(int i=0; i<height; i++){ //ideally this would be mapsize something somwething
        for(int j=0; j<width; j++){
            if(j != 9){
                cout << map[i][j] << " ";
            } else {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
}


bool GameEngine::needsUpdate(){
	for(int x=0; x<8; x++){
		for(int y=0; y<8; y++){
			if((map[x][y]==map[x+1][y] && map[x][y] == map[x+2][y]) || (map[x][y]==map[x][y+1] && map[x][y]==map[x][y+2])){
				return true;
			}
		}
	}
	return false;
}


//makeMove changes two elements on the grid
void GameEngine::makeMove(int x1, int y1, int x2, int y2){
	swap(map[x1][y1],map[x2][y2]);
}


bool GameEngine::isLegalMove(int x1, int y1, int x2, int y2){
	if(isVerticalLegal(x1, y1, x2, y2) || isHorizontalLegal(x1, y1, x2, y2)){
			if (isAdjecent(x1,y1, x2, y2)){
		return true;
		}
	}

	return false;
}

bool GameEngine::isAdjecent(int x1, int y1, int x2, int y2){
if (!((x1 == x2 && abs(y1-y2) == 1) || (y1 == y2 && abs(x1-x2) == 1))){
	//std::cout << "Non-Adjecent move, try again" << std::endl;
	return false;}
	else return true;}

bool GameEngine::isVerticalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1][y1-2]) && (map[x2][y2]==map[x1][y1-1]) && y1>1 && y2>y1)
			|| ((map[x1][y1]==map[x2][y2-2]) && (map[x1][y1]==map[x2][y2-1]) && y2>1 && y1>y2)){
		//cout<<"1"<<endl;
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1+2]) && (map[x2][y2]==map[x1][y1+1]) && y1<8 && y1>y2)
			|| ((map[x1][y1]==map[x2][y2+2]) && (map[x1][y1]==map[x2][y2+1]) && y2<8 && y2>y1)){
		//cout<<"2"<<endl;
		return true;
	}
	else if(x1!=x2 && (((map[x2][y2]==map[x1][y1-1]) && (map[x2][y2]==map[x1][y1+1]) && (y1>0 && y1<9))
			|| ((map[x1][y1]==map[x2][y2-1]) && (map[x1][y1]==map[x2][y2+1]) && (y2>0 && y2<9)))){
		//cout<<"3"<<endl;
		return true;
	}
	return false;
}

bool GameEngine::isHorizontalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1-2][y1]) && (map[x2][y2]==map[x1-1][y1]) && x1>1 && x2>x1)
			|| ((map[x1][y1]==map[x2-2][y2]) && (map[x1][y1]==map[x2-1][y2]) && x2>1 && x1>x2)){
		//cout<<"4"<<endl;
		return true;
	}

	else if(((map[x2][y2]==map[x1+2][y1]) && (map[x2][y2]==map[x1+1][y1]) && x1<8 && x1>x2)
			|| ((map[x1][y1]==map[x2+2][y2]) && (map[x1][y1]==map[x2+1][y2]) && x2<8 && x2>x1)){
		//cout<<"5"<<endl;
		return true;
	}

	else if(y1!=y2 &&  (((map[x2][y2]==map[x1-1][y1]) && (map[x2][y2]==map[x1+1][y1]) && (x1>0 && x1<9))
			|| ((map[x1][y1]==map[x2-1][y2]) && (map[x1][y1]==map[x2+1][y2]) && (x2>0 && x2<9)))){
		//cout<<"6"<<endl;
		return true;
	}
	return false;
}

bool GameEngine::hasLegalMoves(){
	for(int x=0; x<9; x++){
		for(int y=0; y<9; y++){
			if(isLegalMove(x, y, x+1, y) || isLegalMove(x, y, x, y+1)){
				//cout<<"found legal move"<<x1<<y1<<endl;
				return true;
			}
		}
	}
	cout<<"no legal move found"<<endl;
	return false;
}

void GameEngine::updateMap(int count){
	//do the update (break 3,4 or 5)
	//update the score
	//score += numberOfTiles*count
	while(needsUpdate()){
		updateMap(count+1);
	}

}

void GameEngine::breakVertical(int x1, int y1){
	int x2=x1+1, count=1; //y2 is always equal to y1 (because we're looking vertically). count=1 because we have at least 1 tile. x2 starts as x1+1
	while(map[x2][y1] == map[x1][y1]){ //while tiles are equal to (x1 y1) starting from the one next to it (x2 y1).
		x2+=1; //update the "next" tile
		if(x2>9){
			count+=1;
			break; //should stop if we reached the end of the map
		}
		count+=1; //increase number of tiles that are equal
	}
	if(count>=3){ //if it found 3 or more matching tiles in a row
		for(int x=x1; x<=x2; x++){
			map[x][y1] = 0; //dunno what this should be (0?)
		}
	} else{ //if it didnt find enough tiles, search starting from x2,y1 (the first non-equal tile)
		if(x2<8 && y1<9){
			breakVertical(x2,y1);
		} else if (x2>=8 && y1<9){
			breakVertical(0,y1+1); //this column is finished, go to the next
		} else {
			break; //do nothing, y1 is 9, our job is done.
		}


		// STILL NEED TO ADD FUNCTIONALITY TO DROP TILES FROM FUTURE MAP (I THINK THAT EXISTS ALREADY?)
	}
}

void GameEngine::breakHorizontal(int x1, int y1){
	int y2=y1+1, count=1; //y2 is always equal to y1 (because we're looking vertically). count=1 because we have at least 1 tile. x2 starts as x1+1
	while(map[x1][y2] == map[x1][y1]){ //while tiles are equal to (x1 y1) starting from the one next to it (x2 y1).
		y2+=1; //update the "next" tile
		if(y2>9){
			count+=1;
			break; //should stop if we reached the end of the map
		}
		count+=1; //increase number of tiles that are equal
	}
	if(count>=3){ //if it found 3 or more matching tiles in a row
		for(int y=y1; y<=y2; y++){
			map[x1][y] = 0; //dunno what this should be (0?)
		}
	} else{ //if it didnt find enough tiles, search starting from x2,y1 (the first non-equal tile)
		if(y2<8 && x1<9){ //if there is still room, horizontally and vertically
			breakHorizontal(x1,y2);
		} else if (y2>=8 && x1<9){ //if there is no room horizontally
			breakHorizontal(x1+1,0); //this row is finished, go to the next
		} else {
			break; //do nothing, x1 is 9, our job is done.
		}


		// STILL NEED TO ADD FUNCTIONALITY TO DROP TILES FROM FUTURE MAP (I THINK THAT EXISTS ALREADY?)
	}
}


void GameEngine::breakStuff(int x, int y){
	breakHorizontal(x, y);
	//nothing should happen in between here. breaks happen "simultaneously" (in the same game loop iteration)
	breakVertical(x, y);
	//i'm not sure how to handle this, so i did horizontal first and then vertical.
	//if after 1 move there is more than one groups of tiles to be broken, they should happen in the same iteration of gameloop...
	for(x=9; x>0;x--){
		for(y=9;y>-1;y--){
			int x2 = x;
			while(map[x][y]==0 && x2>0){
				map[x][y]=map[x2-1][y];
				map[x2-1][y]=0;
				x2--;
			}
		}
	}
	//at this point in the code, we have a map with a bunch of zeros. we should update those.
}


/*void GameEngine::breakThree(){
	for(int x=0; x<10; x++){
			for(int y=0; y<10; y++){
					if(map[x][y]==map[x][y+1] && map[x][y]==map[x][y+2] && y<8){
						while(x>0){
							map[x][y]=map[x-1][y];
							map[x][y+1]=map[x-1][y+1];
							map[x][y+2]=map[x-1][y+2];
							x--;
						}
						}
					if(map[x][y]==map[x+1][y] && map[x][y]==map[x+2][y] && x<8){
						while(x>2){
							map[x][y]=map[x-3][y];
							map[x+1][y]=map[x-2][y];
							map[x+2][y]=map[x-1][y];
							x--;
						}
				}
	}
}
}*/

void GameEngine::gameLoop(){//ask the user for input (x and y have to be a number from 0 to 9)
	int x1, y1, x2, y2;

	while(hasLegalMoves()){
		cout<<"Give the x-coordinate of the first tile"<<endl;
		cin>>x1;
		cout<<"Give the y-coordinate of the first tile"<<endl;
		cin>>y1;

		cout<<"Give the x-coordinate of the second tile"<<endl;
		cin>>x2;
		cout<<"Give the y-coordinate of the second tile"<<endl;
		cin>>y2;
		if(isLegalMove(x1, y1, x2, y2)){
			makeMove(x1, y1, x2, y2);
			//breakThree();
		}
		else{
			cout<<"Invalid move"<<endl;
			break;
		}
		printMap();
	}
}
/* TO DO:
 * -updateMap()
 *  	-tiles falling down from the future map
 *  	-scorekeeping
 */
#endif /* GAMEENGINE_H_ */
