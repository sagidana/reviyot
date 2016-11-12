#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <algorithm>

#include "Card.h"
#include "Hand.h"
#include "Deck.h"

using namespace std;

class Player : public Hand 
{
private:
	const string _name;
	const int _position;

	Card* findCard(CardValue card_value);
protected:
	Player* getMostCardsPlayer(vector<Player*> players);	
	Player* getPlayerByPosition(int position, vector<Player*> players);
public:
	Player(string name, int position);
	virtual ~Player();

	string getName();   /* Returns the name of the player */
	int getPosition(); 	/* Returns the position of the player */
	void AddCardsFromDeck(int numberOfCards, Deck* deck);
	bool isFinished();
	list<Card*> giveMePlease(CardValue card_value); 
	void discardSets();
	string toString();
	
	virtual void play(Deck* deck, vector<Player*> players) = 0;
};

class PlayerType1 : public Player 
{  
protected:
 	CardValue getMostAppearancesCard();	
public:
	PlayerType1(string name, int position);

	virtual void play(Deck* deck, vector<Player * > players) override;
};

class PlayerType2 : public Player 
{  
protected:
	CardValue getLeastAppearancesCard();	
public:
	PlayerType2(string name, int position);

	virtual void play(Deck* deck, vector<Player * > players) override;
};

class PlayerType3 : public Player 
{  
private:
	int _nextAskedPlayer;
protected:
	CardValue getHighestCard();
public:
	PlayerType3(string name, int position);

	virtual void play(Deck* deck, vector<Player * > players) override;
};

class PlayerType4 : public Player 
{  
private:
	int _nextAskedPlayer;
protected:
	CardValue getLowestCard();
public:
	PlayerType4(string name, int position);

	virtual void play(Deck* deck, vector<Player * > players) override;
};

#endif
