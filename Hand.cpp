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

Hand::Hand(const Hand & other)
{
	uninitializeCards();
	
	for (auto it=other._cards.begin(); it!=other._cards.end(); ++it)
	{
		if (NumericCard * nCard = dynamic_cast<NumericCard * >(*it))		
			this->_cards.push_back(new NumericCard(*nCard));
		else if(FigureCard * fCard = dynamic_cast<FigureCard * >(*it))
			this->_cards.push_back(new FigureCard(*fCard));
	}
}

Hand::~Hand()
{
	uninitializeCards();
}

/* Private methods:
 * -----------------------------------------------------------
 */

void Hand::uninitializeCards()
{
	for (auto it=this->_cards.begin(); it!=this->_cards.end(); ++it)
		delete *it;		/* Free memory*/

	this->_cards.clear();
}


/* Public methods:
 * -----------------------------------------------------------
 */

Hand & Hand::operator=(const Hand & other)
{
	uninitializeCards();
	
	for (auto it=other._cards.begin(); it!=other._cards.end(); ++it)
	{
		if (NumericCard * nCard = dynamic_cast<NumericCard * >(*it))		
			this->_cards.push_back(new NumericCard(*nCard));
		else if(FigureCard * fCard = dynamic_cast<FigureCard * >(*it))
			this->_cards.push_back(new FigureCard(*fCard));
	}
	return *this;
}

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
	this->_cards.remove_if([&](Card * c)->bool { return (c->toString() == card.toString()); }); /* using the toString 																									method to match the cards. */
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





























































