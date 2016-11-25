#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* 
 * The shape of the card.
 */
enum Shape 
{
	Club,
	Diamond,
	Heart,
	Spade
};

/*
 * The figure of the card.
 */
enum Figure 
{
	Jack,
	Queen,
	King,
	Ace
};

/*
 * The card value.
 */
struct CardValue
{
	int number;
	Figure figure;
	CardValue(): number(0), figure(Figure::Jack) { }
	string toString();
    friend bool operator== (const CardValue &cv1, const CardValue &cv2);
    friend bool operator!= (const CardValue &cv1, const CardValue &cv2);
};

/*
 * The Card abstract class - represent a card instance.
 */
class Card 
{
protected:
	Shape _shape;
	string getShapeString() const;
public:
	Card(string card_string);
	Card(Shape shape);
	Card(const Card & other);
  	virtual ~Card();

	Shape GetShape() const;
  	virtual string toString() const = 0; /* Returns the string representation of the 
									        card "<value><shape>" exp: "12S" or "QD" */
	bool operator< (const Card& other) const;
    friend bool operator== (const Card &c1, const Card &c2);
    friend bool operator!= (const Card &c1, const Card &c2);
	virtual CardValue getCardValue() = 0;
};

/*
 * The FigureCard class represent the 11-13, 1 cards in a deck (those with figures on them).
 */
class FigureCard : public Card 
{
private:
	Figure _figure;
protected:
	string getFigureString() const;
public:
	FigureCard(string card_string);
	FigureCard(Shape shape, Figure figure);
	FigureCard(const FigureCard & other); 	/* copy constructor */
	FigureCard(FigureCard && other); 		/* move constructor */

	FigureCard & operator=(const FigureCard & other); /* copy assignment */
	FigureCard & operator=(FigureCard && other); 	  /* move assignment */
	Figure GetFigure() const;
	virtual string toString() const override;
	virtual CardValue getCardValue() override;
};


/*
 * The NumericCard class represent the 2-10 card in a deck (those with numbers on them).
 */
class NumericCard : public Card 
{
private:
	int _number;
protected:
	string getNumberString() const;
public:
	NumericCard(string card_string);
	NumericCard(Shape shape, int number);
	NumericCard(const NumericCard & other); /* copy constructor */
	NumericCard(NumericCard && other); 		/* move constructor */

	NumericCard & operator=(const NumericCard & other); /* copy assignment */
	NumericCard & operator=(NumericCard && other); 	 	/* move assignment */	
	int GetNumber() const;
	virtual string toString() const override;
	virtual CardValue getCardValue() override;
};

#endif
