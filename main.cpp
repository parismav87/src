#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>	

#include "GameEngine.h"
#include "Bot.h"
#include "humanPlayer.h"

using namespace std;

int main()
{
	string PATH_TO_MAP = "C:\\Users\\Willeke\\Desktop\\map5.txt";
	string PATH_TO_FUTURE_MAP = "C:\\Users\\Willeke\\Desktop\\future5.txt";

	HumanPlayer player;
	GameEngine engine(PATH_TO_MAP, PATH_TO_FUTURE_MAP, player);

	system("pause");
	return 0;
}
