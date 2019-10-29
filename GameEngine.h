#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

class GameEngine{
private:
    int map[10][10];
    string mapPath;
public:
    GameEngine(string mapPath);
    void readMap();
    void printMap();
    void makeMove(int x1, int y1, int x2, int y2);
    bool isLegalMove(int x1, int y1, int x2, int y2);
    bool isAdjecent(int x1, int y1, int x2, int y2);
    bool isVerticalLegal(int x1, int y1, int x2, int y2);
    bool isHorizontalLegal(int x1, int y1, int x2, int y2);
    bool isSameRow(int x1, int x2);
    bool isSameColumn(int y1, int y2);
    void gameLoop();

};

GameEngine::GameEngine(string mapPath){
    this->mapPath = mapPath;
    readMap();
}

void GameEngine::readMap(){
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
	if(((map[x2][y2]==map[x1][y1-2]) && (map[x2][y2]==map[x1][y1-1]))
			|| ((map[x1][y1]==map[x2][y2-2]) && (map[x1][y1]==map[x2][y2-1]))){
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1+2]) && (map[x2][y2]==map[x1][y1+1]))
			|| ((map[x1][y1]==map[x2][y2+2]) && (map[x1][y1]==map[x2][y2+1]))){
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1-1]) && (map[x2][y2]==map[x1][y1+1]))
			|| ((map[x1][y1]==map[x2][y2-1]) && (map[x1][y1]==map[x2][y2+1]))){
		return true;
	}
	return false;
}

bool GameEngine::isHorizontalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1-2][y1]) && (map[x2][y2]==map[x1-1][y1]))
			|| ((map[x1][y1]==map[x2-2][y2]) && (map[x1][y1]==map[x2-1][y2]))){
		return true;
	}

	else if(((map[x2][y2]==map[x1+2][y1]) && (map[x2][y2]==map[x1+1][y1]))
			|| ((map[x1][y1]==map[x2+2][y2]) && (map[x1][y1]==map[x2+1][y2]))){
		return true;
	}

	else if(((map[x2][y2]==map[x1-1][y1]) && (map[x2][y2]==map[x1+1][y1]))
			|| ((map[x1][y1]==map[x2-1][y2]) && (map[x1][y1]==map[x2+1][y2]))){
		return true;
	}
	return false;
}

void GameEngine::gameLoop(){//ask the user for input (x and y have to be a number from 0 to 9)
	int x1, y1, x2, y2;

	while(true){
		cout<<"Give the x-coordinate of the first tile"<<endl;
		cin>>x1;
		cout<<"Give the y-coordinate of the first tile"<<endl;
		cin>>y1;

		cout<<"Give the x-coordinate of the second tile"<<endl;
		cin>>x2;
		cout<<"Give the y-coordinate of the second tile"<<endl;
		cin>>y2;
		if(isLegalMove(y1, x1, y2, x2)){
			makeMove(y1, x1, y2, x2);
		}
		else{
			cout<<"Invalid move"<<endl;
			break;
		}
		printMap();
	}
}
#endif /* GAMEENGINE_H_ */
