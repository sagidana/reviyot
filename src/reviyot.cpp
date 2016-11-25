#include <iostream>

#include "../Include/Game.h"

using namespace std;

template <typename T> bool comp(const T * const & a, const T * const & b)
{
   return *a < *b;
}


int main(int argc, char **argv) 
{
	char* configurationFile = argv[1];

	Game game = Game(configurationFile);
	game.init();
 	Game initializedGame = game;
 	game.play(); 
	
	cout << std::endl;
 	game.printWinner();
	game.printNumberOfTurns();
	cout << "----------" << endl;
	cout<<"Initial State:"<<endl;
  	initializedGame.printState();
	cout<<"----------"<<endl;
	cout<<"Final State:"<<endl;
	game.printState();
	
	return 0;
}

