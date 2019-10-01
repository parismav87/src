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
	void read();
};

GameEngine::GameEngine(string mapPath){
	this->mapPath = mapPath;
	read();
}

void GameEngine::read(){

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

		//counter>0 to skip the first line of txt file
		if(counter>0){
			j=0; //j resets to 0 after each line
			for(char c: line){ //for each char in string
				if(c!=','){
					map[i][j] = atoi(&c); //char into int
					j++;
				}
			}
			i++; //next line
		}
		counter++;
	}

	for(int ii=0; ii<5; ii++){
		for(int jj=0; jj<5; jj++){
			cout << map[ii][jj] << endl;
		}
	}






}

#endif /* GAMEENGINE_H_ */
