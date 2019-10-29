
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
    
    //just in case there's no file: create a very basic grid
    else{
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                map[i][j]=randint(0, 4);
            }
        }
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
    //string cursor = "|";//the token on the game board which you're currently at.
    //int height = ((sizeof map) / (sizeof *map));
    //int width = ((sizeof map) / (sizeof *map));
    //cout << height << width << endl;
    
    for(int i=0; i<10; i++){ //ideally this would be mapsize something somwething
        for(int j=0; j<10; j++){
            /*if(i==0 and j==0){
             cout<<cursor<<map[i][j];
             }*/
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
    int temp = map[x1][y1];
    map[x1][y1]= map[x2][y2];
    map[x2][y2]=temp;
}


bool GameEngine::isLegalMove(int x1, int y1, int x2, int y2){
    bool y = isVerticalLegal(x1, y1, x2, y2);
    bool x = isHorizontalLegal(x1, y1, x2, y2);
    bool row = isSameRow(x1, x2);
    bool column = isSameColumn(y1, y2);
    
    if(y and row){
        return true;
    }
    else if(x and column){
        return true;
    }
    return false;
    
    
}


bool GameEngine::isVerticalLegal(int x1, int y1, int x2, int y2){
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

bool GameEngine::isHorizontalLegal(int x1, int y1, int x2, int y2){
    if(((map[x2][y2]==map[x1-2][y1]) and (map[x2][y2]==map[x1-1][y1]))
       or ((map[x1][y1]==map[x2-2][y2]) and(map[x1][y1]==map[x2-2][y2]))){
        return true;
    }
    else if(((map[x2][y2]==map[x1+2][y1]) and (map[x2][y2]==map[x1+1][y1]))
            or ((map[x1][y1]==map[x2+2][y2]) and(map[x1][y1]==map[x2+2][y2]))){
        return true;
        
    }
    else if(((map[x2][y2]==map[x1-1][y1]) and (map[x2][y2]==map[x1+1][y1]))
            or ((map[x1][y1]==map[x2-1][y2]) and(map[x1][y1]==map[x2][y2]))){
        return true;
    }
    return false;
}


bool GameEngine::isSameRow(int x1, int x2){
    if(x1==x2){
        return true;
    }
    return false;
}

bool GameEngine::isSameColumn(int y1, int y2){
    if(y1==y2){
        return true;
    }
    return false;
}





//function for selecting a token on the board. Still in development...
/*char GameEngine::controls(){
 char input;
 cin>>input;
 if(input=='w'){
 return input;
 }
 if(input=='s'){
 return input;
 }
 if(input=='d'){
 return input;
 }
 if(input=='a'){
 return input;
 }
 }*/
#endif /* GAMEENGINE_H_ */
