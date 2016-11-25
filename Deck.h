#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "Card.h"

using namespace std;

class Deck 
{
private:
	int _maximumNumeric;
	list<Card * > _cards;
	
	void initializeDeck(bool ordered);
	void uninitializeDeck();
	void shuffleDeck();
public:
	Deck();
	Deck(int n, bool ordered); 		/* The n parameter is the maximum number of NumericCard that this deck going to have. */
	Deck(const Deck & other);
	~Deck();

	Deck & operator=(const Deck & other); /* copy assignment */
	
	void setMaximumNumeric(int maximumNumeric);
	void pushCardFront(Card* card);
	Card* fetchCard();   	/* Returns the top card of the deck and remove it rom the deck */
	int getNumberOfCards(); /* Get the number of cards in the deck */
	string toString(); 		/* Return the cards in top-to-bottom order in a single line, 
							   cards are separated by a space ex: "12S QD AS 3H" */
};

#endif
