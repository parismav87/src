#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

class GameEngine{
private:
    int map[10][10];
    int fmap[10][10];
    int mapCopy[10][10];
    int totalScore=0;
    string mapPath;
    string futurePath;
public:
    GameEngine(string mapPath, string futurePath);
    void readMap(string mapPath);
    void printMap();
    void printMapCopy();
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
    void breakStuff(int x, int y, int points);
    void breakHorizontal(int x, int y, int points);
    void breakVertical(int x, int y, int points);
    void restoreMap();
    void updateZeros();
    int getScore();
    void addScore(int points);
    void printScore();

};



GameEngine::GameEngine(string mapPath, string futurePath){
    this->mapPath = mapPath;
    this->futurePath = futurePath;
    readMap(mapPath);
    readFuture(futurePath);

}


void GameEngine::printScore(){
	cout<< "------------"<< endl;
	cout<<"Total Score: "<<getScore()<<endl;
	cout<<endl;
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
    cout<<endl;
}

void GameEngine::printMapCopy(){
    int height = sizeof (map) / sizeof (*map);
    int width = sizeof (*map) / sizeof (int);
    //cout << height << width << endl;

    for(int i=0; i<height; i++){ //ideally this would be mapsize something somwething
        for(int j=0; j<width; j++){
            if(j != 9){
                cout << mapCopy[i][j] << " ";
            } else {
                cout << mapCopy[i][j];
            }
        }
        cout << endl;
    }
}

bool GameEngine::needsUpdate(){
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			if((x<8 && map[x][y]==map[x+1][y] && map[x][y] == map[x+2][y] && map[x][y]!=0) || (y<8 && map[x][y]==map[x][y+1] && map[x][y]==map[x][y+2] && map[x][y]!=0)){
				return true;
			}
		}
	}
//	cout<<"I don't need update"<<endl;
	return false;
}


//makeMove changes two elements on the grid
void GameEngine::makeMove(int x1, int y1, int x2, int y2){
	swap(map[x1][y1],map[x2][y2]);
}


bool GameEngine::isLegalMove(int x1, int y1, int x2, int y2){
	cout<<map[x1][y1]<<"  "<<map[x2][y2]<<endl;
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
	if(((map[x2][y2]==map[x1][y1-2]) && (map[x2][y2]==map[x1][y1-1]) && y1>1 && y2>=y1)
			|| ((map[x1][y1]==map[x2][y2-2]) && (map[x1][y1]==map[x2][y2-1]) && y2>1 && y1>=y2)){
		//cout<<"1"<<endl;
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1+2]) && (map[x2][y2]==map[x1][y1+1]) && y1<8 && y1>=y2)
			|| ((map[x1][y1]==map[x2][y2+2]) && (map[x1][y1]==map[x2][y2+1]) && y2<8 && y2>=y1)){
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
	if(((map[x2][y2]==map[x1-2][y1]) && (map[x2][y2]==map[x1-1][y1]) && x1>1 && x2>=x1)
			|| ((map[x1][y1]==map[x2-2][y2]) && (map[x1][y1]==map[x2-1][y2]) && x2>1 && x1>=x2)){
		//cout<<"4"<<endl;
		return true;
	}

	else if(((map[x2][y2]==map[x1+2][y1]) && (map[x2][y2]==map[x1+1][y1]) && x1<8 && x1>=x2)
			|| ((map[x1][y1]==map[x2+2][y2]) && (map[x1][y1]==map[x2+1][y2]) && x2<8 && x2>=x1)){
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
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			mapCopy[x][y]=map[x][y];
		}
	}
	breakStuff(0, 0, count);
	updateZeros();
	//update the score
	//score += numberOfTiles*count


}

void GameEngine::breakVertical(int x1, int y1, int points){
	int x2=x1+1, count=1; //y2 is always equal to y1 (because we're looking vertically). count=1 because we have at least 1 tile. x2 starts as x1+1
	while(map[x2][y1]!=0 && map[x2][y1] == map[x1][y1]){ //while tiles are equal to (x1 y1) starting from the one next to it (x2 y1).
		x2+=1; //update the "next" tile
		if(x2>9){
			count+=1;
			break; //should stop if we reached the end of the map
		}
		count+=1; //increase number of tiles that are equal
	}
	if(count>=3){ //if it found 3 or more matching tiles in a row
		cout<<"count "<<count<<endl;
		for(int x=x1; x<=x2-1; x++){
			mapCopy[x][y1] = 0; //dunno what this should be (0?)
			addScore(points); //add points for each broken tile
		}
	}
	if(x2<8 && y1<=9){
		breakVertical(x2,y1, points);
	} else if (x2>=8 && y1<9){
		breakVertical(0,y1+1, points); //this column is finished, go to the next
	}
}

void GameEngine::breakHorizontal(int x1, int y1, int points){
	int y2=y1+1, count=1; //y2 is always equal to y1 (because we're looking vertically). count=1 because we have at least 1 tile. x2 starts as x1+1
	while(map[x1][y2]!=0 && map[x1][y2] == map[x1][y1]){ //while tiles are equal to (x1 y1) starting from the one next to it (x2 y1).
		y2+=1; //update the "next" tile
		if(y2>9){
			count+=1;
			break; //should stop if we reached the end of the map
		}
		count+=1; //increase number of tiles that are equal
	}
	if(count>=3){ //if it found 3 or more matching tiles in a row
		for(int y=y1; y<=y2-1; y++){
			mapCopy[x1][y] = 0; //dunno what this should be (0?)
			addScore(points);//add points for each broken tile
			cout<<"added "<<points<<endl;
		}
	}
	if(y2<8 && x1<=9){ //if there is still room, horizontally and vertically
		breakHorizontal(x1,y2, points);
	} else if (y2>=8 && x1<9){ //if there is no room horizontally
		breakHorizontal(x1+1,0, points); //this row is finished, go to the next
	}
}


void GameEngine::breakStuff(int x, int y, int points){
	breakHorizontal(x, y, points);
	//nothing should happen in between here. breaks happen "simultaneously" (in the same game loop iteration)
	breakVertical(x, y, points);
//	printMap();
//	cout<<endl;
	//i'm not sure how to handle this, so i did horizontal first and then vertical.
	//if after 1 move there is more than one groups of tiles to be broken, they should happen in the same iteration of gameloop...

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
void GameEngine::restoreMap(){
	 for(int i=0; i<10; i++){ //ideally this would be mapsize something somwething
	        for(int j=0; j<10; j++){
	        	map[i][j]=mapCopy[i][j];
	        }
	 }
}

void GameEngine::updateZeros(){
	for(int x=9; x>0;x--){
		for(int y=9;y>-1;y--){
			int x2 = x;
			while(mapCopy[x][y]==0 && x2>0){
				mapCopy[x][y]=mapCopy[x2-1][y];
				mapCopy[x2-1][y]=0;
				x2--;
			}
		}
	}
}

int GameEngine::getScore(){
	return totalScore;
}

void GameEngine::addScore(int points){
	totalScore+=points;
}

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
			int points=1;
			makeMove(x1, y1, x2, y2);
			printMap();
			cout<<endl;
			while(needsUpdate()){
				cout<<"I need an update"<<endl;
				updateMap(points);
				restoreMap();
				printMap();
				printScore();

				points+=1;
			}
			//breakThree();
//			cout<<points<<endl;
		}
		else{
			cout<<"Invalid move, try again"<<endl;
		}

	}
	cout<<"The game has ended"<<endl;
	cout<<getScore()<<endl;
}
/* TO DO:
 * -updateMap()
 *  	-tiles falling down from the future map
 *  	-scorekeeping
 *  	-if no legal moves anymore-->then break
 */
#endif /* GAMEENGINE_H_ */
