#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

#include "Player.h"
#include "Deck.h"

using namespace std;

class Game 
{
private:
	string _configurationFile;
	bool _verbal;
	vector<Player *> players;  	/* The list of the players */
	Deck deck;                 	/* The deck of the game */
	int _numberOfTurns;
	
	Card* createCardFromString(string card_string);
	Player* createPlayer(string name, string type, int position);
	Player* getPlayerByPosition(int position);
	void uninitializePlayers();
	void giveCardsToPlayers();
	bool gameFinished();
	vector<Player*> playersWithout(string playerName);
public:
	Game(char* configurationFile);
	Game(const Game& other);
	~Game();
	
	Game & operator=(const Game & other); /* copy assignment */
	void init();
	void play();
	void printState();        	/* Print the state of the game as described in the assignment. */
	void printWinner();       	/* Print the winner of the game as describe in the assignment. */
    void printNumberOfTurns(); 	/* Print the number of played turns at any given time.  */
};

#endif
