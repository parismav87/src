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
	Bot player;

	GameEngine game("C:\\Users\\Willeke\\Desktop\\map5.txt", "C:\\Users\\Willeke\\Desktop\\future5.txt", player);

	system("pause");
	return 0;
}