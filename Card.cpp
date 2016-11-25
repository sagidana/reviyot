#include "Card.h"

/* Card implementation:
 * -----------------------------------------------------------
 */

bool operator== (const CardValue &cv1, const CardValue &cv2)
{
	if (cv1.number > 0 && cv2.number > 0)
		return cv1.number == cv2.number;
	if (cv1.number == 0 && cv2.number == 0)
		return cv1.figure == cv2.figure;
	return false;
}
bool operator!= (const CardValue &cv1, const CardValue &cv2)
{
	return !(cv1 == cv2);
}

bool operator== (const Card &c1, const Card &c2)
{
    return c1.toString() == c2.toString();
}
 
bool operator!= (Card &c1, Card &c2)
{
    return !(c1 == c2);
}
 

string CardValue::toString()
{
	if (this->number >= 2)
		return std::to_string(this->number);
	switch (this->figure)
	{
		case Figure::Jack:
			return "J";
		case Figure::Queen:
			return "Q";
		case Figure::King:
			return "K";
		case Figure::Ace:
			return "A";
	}
	return "";
}

/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Card::Card(string card_string)
{
	switch (card_string.back())
	{
		case 'C':
		{
			this->_shape = Shape::Club;
			break;	
		}
		case 'D':
		{
			this->_shape = Shape::Diamond;
			break;	
		}
		case 'H':
		{
			this->_shape = Shape::Heart;
			break;	
		}
		case 'S':
		{
			this->_shape = Shape::Spade;
			break;	
		}
	}
}

Card::Card(Shape shape) : _shape(shape) { }

Card::Card(const Card & other) : Card(other.GetShape()) { }

Card::~Card() { }

/* Protected methods:
 * ------------------------------------------------------------
 */

string Card::getShapeString() const
{
	switch (this->_shape)
	{
		case Shape::Club:
			return "C";
		case Shape::Diamond:
			return "D";
		case Shape::Heart:
			return "H";
		case Shape::Spade:
			return "S";
		default:
			return "";
	}
}

/* Public methods:
 * ------------------------------------------------------------
 */

Shape Card::GetShape() const
{
	return this->_shape;
}

bool Card::operator< (const Card& other) const
{
	const FigureCard * this_fCard = dynamic_cast<const FigureCard * >(this);	
	const NumericCard * this_nCard = dynamic_cast<const NumericCard * >(this);
	const FigureCard * other_fCard = dynamic_cast<const FigureCard * >(&other);	
	const NumericCard * other_nCard = dynamic_cast<const NumericCard * >(&other);

	if (this_fCard && other_fCard)
	{
		if (this_fCard->GetFigure() == other_fCard->GetFigure())
			return this->GetShape() < other.GetShape();
		return this_fCard->GetFigure() < other_fCard->GetFigure();
	}
	else if (this_nCard && other_nCard)
	{
		if (this_nCard->GetNumber() == other_nCard->GetNumber())
			return this->GetShape() < other.GetShape();
		return this_nCard->GetNumber() < other_nCard->GetNumber();
	}
	else if (this_fCard && other_nCard)
		return false;
	else
		return true;
}

/* FigureCard implementation:
 * -----------------------------------------------------------
 */

/* C-tors & D-tors
 * -----------------------------------------------------------
 */

FigureCard::FigureCard(string card_string) : Card(card_string)
{
	string figure_string = card_string.substr(0, card_string.size() - 1); /* Without the last letter. */
	
	if (figure_string == "J")
		this->_figure = Figure::Jack;
	else if(figure_string == "Q")
		this->_figure = Figure::Queen;
	else if(figure_string == "K")
		this->_figure = Figure::King;
	else if(figure_string == "A")
		this->_figure = Figure::Ace;
}

FigureCard::FigureCard(Shape shape, Figure figure) : Card (shape), _figure(figure) { }

FigureCard::FigureCard(const FigureCard & other) : Card(other.GetShape()), _figure(other.GetFigure()) { }

FigureCard::FigureCard(FigureCard && other) : Card(other.GetShape()), _figure(other.GetFigure()) { }

/* Protected methods:
 * ------------------------------------------------------------
 */

string FigureCard::getFigureString() const
{
	switch (this->_figure)
	{
		case Figure::Jack:
			return "J";
		case Figure::Queen:
			return "Q";
		case Figure::King:
			return "K";
		case Figure::Ace:
			return "A";
		default:
			return "";
	}
}

/* Public methods:
 * ------------------------------------------------------------
 */

FigureCard & FigureCard::operator=(const FigureCard & other)
{
	this->_shape = other.GetShape();
	this->_figure = other.GetFigure();
	return *this;
}

FigureCard & FigureCard::operator=(FigureCard && other)
{
	this->_shape = other.GetShape();
	this->_figure = other.GetFigure();
	return *this;
}


Figure FigureCard::GetFigure() const
{
	return this->_figure;
}

string FigureCard::toString() const
{
	string shape = getShapeString();
	string figure = getFigureString();
	
	return figure + shape;
}

CardValue FigureCard::getCardValue()
{
	CardValue card_value;
	card_value.figure = GetFigure();

	return card_value;
}

/* NumericCard implementation:
 * -----------------------------------------------------------
 */

/* C-tors & D-tors
 * -----------------------------------------------------------
 */

NumericCard::NumericCard(string card_string) : Card(card_string)
{
	string number_string = card_string.substr(0, card_string.size() - 1); /* Without the last letter. */
	stringstream(number_string) >> this->_number;
}

NumericCard::NumericCard(Shape shape, int number) : Card (shape), _number(number) { }

NumericCard::NumericCard(const NumericCard & other) : Card(other.GetShape()), _number(other.GetNumber()) { }

NumericCard::NumericCard(NumericCard && other) : Card(other.GetShape()), _number(other.GetNumber()) { }

/* Protected methods:
 * -----------------------------------------------------------
 */

string NumericCard::getNumberString() const
{
	return std::to_string(this->_number);
}

/* Public methods:
 * -----------------------------------------------------------
 */

NumericCard & NumericCard::operator=(const NumericCard & other) 
{
	this->_number = other.GetNumber();
	this->_shape = other.GetShape();
	return *this;
}

NumericCard & NumericCard::operator=(NumericCard && other) 	
{
	this->_number = other.GetNumber();
	this->_shape = other.GetShape();
	return *this;
}

string NumericCard::toString() const
{
	string shape = getShapeString();
	string number = getNumberString();
	
	return number + shape;
}

int NumericCard::GetNumber() const
{
	return this->_number;
}

CardValue NumericCard::getCardValue()
{
	CardValue card_value;
	card_value.number = GetNumber();
	return card_value;
}


















































































































	

