#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

class GameEngine{
private:
    int map[10][10]; //map of game tiles
    int fmap[10][10]; //map of future tiles
    int mapCopy[10][10]; //clone of map, necessary for calculations
    int totalScore=0; //total game score
    string mapPath; //directory of map file
    string futurePath; //directory of future map file
public:
    GameEngine(string mapPath, string futurePath);
    void readMap(string path, int *arr);
    int* getMap();
    void printMap();
    void printMapCopy();
    void makeMove(int* arr);
    bool isLegalMove(int x1, int y1, int x2, int y2);
    bool isAdjecent(int x1, int y1, int x2, int y2);
    bool isVerticalLegal(int x1, int y1, int x2, int y2);
    bool isHorizontalLegal(int x1, int y1, int x2, int y2);
    bool isSameRow(int x1, int x2);
    bool isSameColumn(int y1, int y2);
    bool hasLegalMoves();
    void updateMap(int count);
    bool needsUpdate();
    void breakStuff(int x, int y, int points);
    void breakHorizontal(int x, int y, int points);
    void breakVertical(int x, int y, int points);
    void restoreMap();
    void updateZeros(int *arr);
    void replaceZeros();
    int getScore();
    void addScore(int points);
    void printScore();

};


//constructor for game engine class. Reads the maps and assigns them to variables.
GameEngine::GameEngine(string mapPath, string futurePath){
    this->mapPath = mapPath;
    this->futurePath = futurePath;
    readMap(mapPath, *map);
    readMap(futurePath, *fmap);
    printMap();
}

//print score in terminal
void GameEngine::printScore(){
	cout<< "------------"<< endl;
	cout<<"Total Score: "<<getScore()<<endl;
	cout<<endl;
}


//open and read map file and assign it into an array
void GameEngine::readMap(string path, int *arr){
    ifstream mapFile(path);
    int counter = 0;
    int j=0;
    if(mapFile){
        cout<<"map loaded"<<endl;
    }

    while(mapFile){
        string line;
        getline(mapFile, line);

        for(char c: line){ //for each char in string
            if(c!=','){
                *(arr+j)= atoi(&c); //char into int
                j++;
            }
        }
        counter++;
    }
}

//return map variable
int* GameEngine::getMap(){
	return *map;
}

//print map in readable format in terminal
void GameEngine::printMap(){
    int height = sizeof (map) / sizeof (*map);
    int width = sizeof (*map) / sizeof (int);

    for(int i=0; i<height; i++){
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


//print the map clone in terminal.
void GameEngine::printMapCopy(){
    int height = sizeof (map) / sizeof (*map);
    int width = sizeof (*map) / sizeof (int);

    for(int i=0; i<height; i++){
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


//for each tile, check if is forming a triad (vertical or horizontal). If yes, this should be resolved.
bool GameEngine::needsUpdate(){
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			if((x<8 && map[x][y]==map[x+1][y] && map[x][y] == map[x+2][y] && map[x][y]!=0) || (y<8 && map[x][y]==map[x][y+1] && map[x][y]==map[x][y+2] && map[x][y]!=0)){
				return true;
			}
		}
	}
	return false;
}


//makeMove swaps two elements on the grid
void GameEngine::makeMove(int* arr){
	int x1= arr[0];
	int y1= arr[1];
	int x2= arr[2];
	int y2= arr[3];

	swap(map[x1][y1],map[x2][y2]);
}



//check whether a move is legal (it is legal if it results in a triad, vertical or horizontal)
bool GameEngine::isLegalMove(int x1, int y1, int x2, int y2){
	if((isVerticalLegal(x1, y1, x2, y2) || isHorizontalLegal(x1, y1, x2, y2)) && map[x1][y1]!=0 && map[x2][y2]!=0){
			if (isAdjecent(x1,y1, x2, y2)){
		return true;
		}
	}

	return false;
}


//check if two tiles are next to each other (engine doesn't allow swap between non-adjacent tiles)
bool GameEngine::isAdjecent(int x1, int y1, int x2, int y2){
if (!((x1 == x2 && abs(y1-y2) == 1) || (y1 == y2 && abs(x1-x2) == 1))){
	return false;}
	else return true;}


//check if a move is legal vertically (makes a vertical triad)
bool GameEngine::isVerticalLegal(int x1, int y1, int x2, int y2){
	if(((map[x2][y2]==map[x1][y1-2]) && (map[x2][y2]==map[x1][y1-1]) && y1>1 && y2>=y1)
			|| ((map[x1][y1]==map[x2][y2-2]) && (map[x1][y1]==map[x2][y2-1]) && y2>1 && y1>=y2)){
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1+2]) && (map[x2][y2]==map[x1][y1+1]) && y1<8 && y1>=y2)
			|| ((map[x1][y1]==map[x2][y2+2]) && (map[x1][y1]==map[x2][y2+1]) && y2<8 && y2>=y1)){
		return true;
	}
	else if(x1!=x2 && (((map[x2][y2]==map[x1][y1-1]) && (map[x2][y2]==map[x1][y1+1]) && (y1>0 && y1<9))
			|| ((map[x1][y1]==map[x2][y2-1]) && (map[x1][y1]==map[x2][y2+1]) && (y2>0 && y2<9)))){
		return true;
	}
	return false;
}


//check if a move is legal horizontally (makes a horizontal triad)
bool GameEngine::isHorizontalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1-2][y1]) && (map[x2][y2]==map[x1-1][y1]) && x1>1 && x2>=x1)
			|| ((map[x1][y1]==map[x2-2][y2]) && (map[x1][y1]==map[x2-1][y2]) && x2>1 && x1>=x2)){
		return true;
	}

	else if(((map[x2][y2]==map[x1+2][y1]) && (map[x2][y2]==map[x1+1][y1]) && x1<8 && x1>=x2)
			|| ((map[x1][y1]==map[x2+2][y2]) && (map[x1][y1]==map[x2+1][y2]) && x2<8 && x2>=x1)){
		return true;
	}

	else if(y1!=y2 &&  (((map[x2][y2]==map[x1-1][y1]) && (map[x2][y2]==map[x1+1][y1]) && (x1>0 && x1<9))
			|| ((map[x1][y1]==map[x2-1][y2]) && (map[x1][y1]==map[x2+1][y2]) && (x2>0 && x2<9)))){
		return true;
	}
	return false;
}

//check if the current map state has any legal moves (moves that would lead to triads, horizontal or vertical)
bool GameEngine::hasLegalMoves(){
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			if((x!=9 && isLegalMove(x, y, x+1, y)) || (y!=9 && isLegalMove(x, y, x, y+1))){
				return true;
			}
		}
	}
	cout<<"no legal move found"<<endl;
	return false;
}


//update the map after a move is made
void GameEngine::updateMap(int count){
	for(int x=0; x<10; x++){
		for(int y=0; y<10; y++){
			mapCopy[x][y]=map[x][y];
		}
	}
	breakStuff(0, 0, count);
	updateZeros(*mapCopy);
	replaceZeros();
	updateZeros(*fmap);


}


//break tiles in columns
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
		for(int x=x1; x<=x2-1; x++){
			mapCopy[x][y1] = 0; //broken tiles are replaced with zeros
			addScore(points); //add points for each broken tile
		}
	}
	if(x2<8 && y1<=9){
		breakVertical(x2,y1, points);
	} else if (x2>=8 && y1<9){
		breakVertical(0,y1+1, points); //this column is finished, go to the next
	}
}

//break tiles in rows
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
//			cout<<"added "<<points<<endl;
		}
	}
	if(y2<8 && x1<=9){ //if there is still room, horizontally and vertically
		breakHorizontal(x1,y2, points);
	} else if (y2>=8 && x1<9){ //if there is no room horizontally
		breakHorizontal(x1+1,0, points); //this row is finished, go to the next
	}
}

//break tiles that form triads (or longer sets)
void GameEngine::breakStuff(int x, int y, int points){
	breakHorizontal(x, y, points);
	//nothing should happen in between here. breaks happen "simultaneously" (in the same game loop iteration)
	breakVertical(x, y, points);
}


//copy map clone into original map
void GameEngine::restoreMap(){
	 for(int i=0; i<10; i++){
	        for(int j=0; j<10; j++){
	        	map[i][j]=mapCopy[i][j];
	        }
	 }
}

//put zeros in 'broken' tiles' places
void GameEngine::updateZeros(int *arr){
	int arrClone[10][10];
	for(int i=0; i<100; i++){
		arrClone[i/10][i%10] = arr[i];
	}
	for(int j=0; j<10; j++){
		int countZeros =0;
		for(int i=9; i>=0; i--){
			if(arrClone[i][j]==0){
				countZeros+=1;
			} else {
				if(countZeros>0){
					arrClone[i+countZeros][j] = arrClone[i][j];
					arrClone[i][j] = 0;
				}
			}
		}
	}


	for(int x=0;x<10;x++){
		for(int y=0;y<10;y++){
			arr[x*10+y]=arrClone[x][y];
		}
	}

}



//replace broken tiles with new ones
void GameEngine::replaceZeros(){
	for(int x=9; x>-1;x--){
			for(int y=9;y>-1;y--){
				if(mapCopy[x][y]==0){
					int x2 = x;
					while(x2>-1){
						int x3 = (x2-x)+9;
						swap(mapCopy[x2][y], fmap[x3][y]);
						x2--;
					}

				}
			}
	}
}


//return score
int GameEngine::getScore(){
	return totalScore;
}


//add points to score
void GameEngine::addScore(int points){
	totalScore+=points;
}


#endif /* GAMEENGINE_H_ */
