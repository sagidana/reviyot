#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <list>

#include "Card.h"

using namespace std;

template <typename T> bool comp(const T * const & a, const T * const & b);

class Hand 
{
protected:
	list<Card * > _cards;
public:
	Hand();
	virtual ~Hand();
	bool addCard(Card &card);
	bool removeCard(Card &card);
	int getNumberOfCards(); 		/* Get the number of cards in hand */
	string toString(); 				/* Return a list of the cards, separated by space, 
						  			   in one line, in a sorted order, ex: "2S 5D 10H" */
};

#endif

