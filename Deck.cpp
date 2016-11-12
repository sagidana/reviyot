#include "Deck.h"

/* Deck implementation:
 * -----------------------------------------------------------
 */

template <typename T> bool comp(const T * const & a, const T * const & b)
{
   return *a < *b;
}

/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Deck::Deck()
{
	this->_maximumNumeric = 1;
	this->_cards.clear();
}

Deck::Deck(int n, bool ordered)
{
	if (n > 0)
		this->_maximumNumeric = n;
	else
		this->_maximumNumeric = 1;
	
	initializeDeck(ordered);
}

Deck::Deck(const Deck & other)
{
	uninitializeDeck();
	
}

Deck::~Deck()
{
	this->_maximumNumeric = 1;
	uninitializeDeck();
}

/* Private methods:
 * -----------------------------------------------------------
 */

void Deck::shuffleDeck()
{
	vector<Card * > vCards(this->_cards.begin(), this->_cards.end());
	random_shuffle(vCards.begin(), vCards.end());
	this->_cards.assign(vCards.begin(), vCards.end());
}

void Deck::initializeDeck(bool ordered)
{
	for ( int shapeInt = Shape::Club; shapeInt <= Shape::Spade; shapeInt++ )
	{
	   	Shape shape = static_cast<Shape>(shapeInt);
		for ( int figureInt = Figure::Jack; figureInt <= Figure::Ace; figureInt++ ) /* Initialize Figure cards. */
		{
		   	Figure figure = static_cast<Figure>(figureInt);
			Card * card = new FigureCard(shape, figure);
			
			this->_cards.push_back(card);
		}

		for (int numeric = 2; numeric <= this->_maximumNumeric; numeric++) /* Initialize numeric cards. */
		{
			Card * card = new NumericCard(shape, numeric);

			this->_cards.push_back(card);
		}
	}

	if (ordered)
		this->_cards.sort(comp<Card>);
	else 
		shuffleDeck();
}

void Deck::uninitializeDeck()
{
	for (auto it=this->_cards.begin(); it!=this->_cards.end(); ++it)
		delete *it;		/* Free memory*/

	this->_cards.clear();
}

/* Public methods:
 * -----------------------------------------------------------
 */

void Deck::setMaximumNumeric(int maximumNumeric)
{
	this->_maximumNumeric = maximumNumeric;
}

void Deck::pushCardFront(Card* card)
{
	this->_cards.push_front(card);
}

Card* Deck::fetchCard()
{
	Card * ret_card = nullptr;
	if (!this->_cards.empty())
	{
		ret_card = this->_cards.back();
		this->_cards.pop_back();
	}
	return ret_card;
}

int Deck::getNumberOfCards()
{
	return this->_cards.size();
}

string Deck::toString()
{
	string ret_string = "";

	list<Card * >::reverse_iterator it;
	for (it=this->_cards.rbegin(); it!=this->_cards.rend(); ++it)
		ret_string += (*it)->toString() + " ";
	
	return ret_string;
}
							








































































































