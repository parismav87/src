/*
 * GameEngine.h
 *
 *  Created on: 1 okt. 2019
 *      Author: Luc Wolfs
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
	//char controls(); still experimenting on it

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
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
			map[i][j]=randint(0, 4);
			}
		}
	}

	while(mapFile){
		string line;
		getline(mapFile, line);
		if(counter > 0){
			j=0;
			for(char c: line){
				if(c!=','){
					map[i][j] = atoi(&c);
					j++;
				}
			}
			i++;
		}
		counter++;
	}


	printMap();


}

void GameEngine::printMap(){
	string cursor = "|";//the token on the game board which you're currently at.
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
		if(i==0 and j==0){
			cout<<cursor<<map[i][j];
		}
		else{
		cout<<" "<<map[i][j];}
		}
	cout<<endl;
	}
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

