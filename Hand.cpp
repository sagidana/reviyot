#include "Hand.h"

/* Hand implementation:
 * -----------------------------------------------------------
 */

template <typename T> bool comp(const T * const & a, const T * const & b)
{
   return *a < *b;
}

/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Hand::Hand()
{
	this->_cards.clear();
}

Hand::~Hand()
{
	this->_cards.clear();
}

/* Public methods:
 * -----------------------------------------------------------
 */

bool Hand::addCard(Card &card)
{
	try
	{
		this->_cards.push_back(&card);
		return true;
	}
	catch (const std::bad_alloc& e) /* Allocation error. */
	{	
		return false;
	}
}

bool Hand::removeCard(Card &card)
{
	this->_cards.remove_if([&](Card * c)->bool { return (c->toString() == card.toString()); }); /* using the toString method to match the cards. */
	return true; /* Always succeed when the value exist, otherwise do nothing. */
}

int Hand::getNumberOfCards()
{
	return this->_cards.size();
}

string Hand::toString()
{
	string ret_string = "";
	this->_cards.sort(comp<Card>);

	list<Card * >::iterator it;
	for (it=this->_cards.begin(); it!=this->_cards.end(); ++it)
		ret_string += (*it)->toString() + " ";
	
	return ret_string;
}





























































