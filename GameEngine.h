/*
 * GameEngine.h
 *
 *  Created on: Oct 1, 2019
 *      Author: Paris
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

class GameEngine{
private:
	int map[5][5];
	string mapPath;
public:
	GameEngine(string mapPath);
	void readMap();
	void printMap();
};

GameEngine::GameEngine(string mapPath){
	this->mapPath = mapPath;
	readMap();
}

void GameEngine::readMap(){

	//read the map txt file into a file stream
	ifstream mapFile(mapPath);

	// counter for text file lines
	int counter = 0;
	//counters for map array
	int i = 0;
	int j = 0;

	//check whether the file was loaded correctly
	if(mapFile){
		cout<< "map loaded" << endl;
	}

	//while there are lines to read
    while(mapFile){
        string line; //declare line string
        getline(mapFile, line); //text line into string
        
        //cout << line << endl;
        
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
    //cout the map (line by line)
    for(int i=0; i<10; i++){ //ideally this would be mapsize something somwething
        for(int j=0; j<10; j++){
            if(j != 9){
                cout << map[i][j] << " ";
            } else {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
}



#endif /* GAMEENGINE_H_ */
