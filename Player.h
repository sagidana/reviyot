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
	Card* findCard(CardValue card_value);
protected:
	string _name;
	int _position;
	void copyPlayer(const Player * other);
	Player* getMostCardsPlayer(vector<Player*> players);	
	Player* getPlayerByPosition(int position, vector<Player*> players);
public:
	Player(string name, int position);
	Player(const Player & other);
	virtual ~Player();

	Player & operator=(const Player & other); /* copy assignment */
	string getName();   /* Returns the name of the player */
	int getPosition(); 	/* Returns the position of the player */
	void AddCardsFromDeck(int numberOfCards, Deck* deck);
	bool isFinished();
	list<Card*> giveMePlease(CardValue card_value); 
	list<Card*> giveMePlease(CardValue card_value, Deck * deck); 
	void discardSets();
	string toString();

	virtual string getPlayDecision(vector<Player*> players) = 0;
	virtual void play(Deck* deck, vector<Player*> players) = 0;
};

class PlayerType1 : public Player 
{  
protected:
 	CardValue getMostAppearancesCard();	
public:
	PlayerType1(string name, int position);
	PlayerType1(const PlayerType1 & other);

	PlayerType1 & operator=(const PlayerType1 & other); /* copy assignment */
	virtual void play(Deck* deck, vector<Player * > players) override;
	virtual string getPlayDecision(vector<Player*> players) override;
};

class PlayerType2 : public Player 
{  
protected:
	CardValue getLeastAppearancesCard();	
public:
	PlayerType2(string name, int position);
	PlayerType2(const PlayerType2 & other);

	PlayerType2 & operator=(const PlayerType2 & other); /* copy assignment */
	virtual void play(Deck* deck, vector<Player * > players) override;
	virtual string getPlayDecision(vector<Player*> players) override;
};

class PlayerType3 : public Player 
{  
private:
	int _nextAskedPlayer;
protected:
	CardValue getHighestCard();
public:
	PlayerType3(string name, int position);
	PlayerType3(const PlayerType3 & other);

	PlayerType3 & operator=(const PlayerType3 & other); /* copy assignment */
	virtual void play(Deck* deck, vector<Player * > players) override;
	virtual string getPlayDecision(vector<Player*> players) override;
};

class PlayerType4 : public Player 
{  
private:
	int _nextAskedPlayer;
protected:
	CardValue getLowestCard();
public:
	PlayerType4(string name, int position);
	PlayerType4(const PlayerType4 & other);

	PlayerType4 & operator=(const PlayerType4 & other); /* copy assignment */
	virtual void play(Deck* deck, vector<Player * > players) override;
	virtual string getPlayDecision(vector<Player*> players) override;
};

#endif
