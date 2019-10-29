
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
    //char controls(); still experimenting on it
    void makeMove(int x1, int y1, int x2, int y2);
    bool isLegalMove(int x1, int y1, int x2, int y2);
    bool isAdjecent(int x1, int y1, int x2, int y2);
    bool isVerticalLegal(int x1, int y1, int x2, int y2);
    bool isHorizontalLegal(int x1, int y1, int x2, int y2);
    bool isSameRow(int x1, int x2);
    bool isSameColumn(int y1, int y2);

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

}

void GameEngine::printMap(){
    int height = sizeof (map) / sizeof (*map);
    int width = sizeof (*map) / sizeof (int);
    //cout << height << width << endl;

    for(int i=height; i>-1; i--){ //ideally this would be mapsize something somwething
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
	if(isVerticalLegal(x1, y1, x2, y2) or isHorizontalLegal(x1, y1, x2, y2)){
			if (isAdjecent(x1,x2,y1,y2)){
		return true;
		}
	}
	else cout << "No valid move made";

	return false;
}

bool GameEngine::isAdjecent(int x1, int y1, int x2, int y2){
if (!((x1 == x2 && abs(y1-y2) == 1) || (y1 == y2 && abs(x1-x2) == 1))){
	std::cout << "Non-Adjecent move, try again" << std::endl;
	return false;}
	else return true;}

bool GameEngine::isVerticalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1][y1-2]) and (map[x2][y2]==map[x1][y1-1]))
			or ((map[x1][y1]==map[x2][y2-2]) and(map[x1][y1]==map[x2][y2-1]))){
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1+2]) and (map[x2][y2]==map[x1][y1+1]))
			or ((map[x1][y1]==map[x2][y2+2]) and(map[x1][y1]==map[x2][y2+1]))){
		return true;
	}
	else if(((map[x2][y2]==map[x1][y1-1]) and (map[x2][y2]==map[x1][y1+1]))
			or ((map[x1][y1]==map[x2][y2-1]) and(map[x1][y1]==map[x2][y2+1]))){
		return true;
	}
	return false;
}

bool GameEngine::isHorizontalLegal(int x1, int y1, int x2, int y2){ // check before swap is made
	if(((map[x2][y2]==map[x1-2][y1]) and (map[x2][y2]==map[x1-1][y1]))
			or ((map[x1][y1]==map[x2-2][y2]) and(map[x1][y1]==map[x2-1][y2]))){
		return true;
	}

	else if(((map[x2][y2]==map[x1+2][y1]) and (map[x2][y2]==map[x1+1][y1]))
			or ((map[x1][y1]==map[x2+2][y2]) and(map[x1][y1]==map[x2+1][y2]))){
		return true;
	}

	else if(((map[x2][y2]==map[x1-1][y1]) and (map[x2][y2]==map[x1+1][y1]))
			or ((map[x1][y1]==map[x2-1][y2]) and(map[x1][y1]==map[x2+1][y2]))){
		return true;
	}
	return false;
}

#endif /* GAMEENGINE_H_ */
