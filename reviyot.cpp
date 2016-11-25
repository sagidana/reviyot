#include <iostream>

#include <list>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

using namespace std;

template <typename T> bool comp(const T * const & a, const T * const & b)
{
   return *a < *b;
}


int main(int argc, char **argv) 
{
	if (argc == 1)
		return 1;

	char* configurationFile = argv[1];

	Game game = Game(configurationFile);
	game.init();
 	Game initializedGame = game;
 	game.play();  
 	
	/*
	cout << std::endl;
 	game.printWinner();
	game.printNumberOfTurns();
	cout << "----------" << endl;
	cout<<"Initial State:"<<endl;
  	initializedGame.printState();
	cout<<"----------"<<endl;
	cout<<"Final State:"<<endl;
	game.printState();
	*/

	/*
	CardValue cv1;
	CardValue cv2;
	cv1.figure = Figure::Ace;
	cv2.figure = Figure::Jack;
	cout << (cv1 == cv2) << endl;
	*/
	
	/*
	Deck d(5, false);
	PlayerType4 p("Sagi", 1);
	p.AddCardsFromDeck(8, &d);
	cout << p.toString() << endl;
	CardValue cv = p.getLowestCard();
	cout << cv.number << ", " << cv.figure << endl;
	*/

	/*
	Deck d(20, false);
	PlayerType2 p("Sagi", 1);
	p.AddCardsFromDeck(24, &d);
	cout << p.toString() << endl;
	CardValue cv = p.getLeastAppearancesCard();
	cout << cv.number << ", " << cv.figure << endl;
	*/

	/*
	Deck d(20, false);
	PlayerType1 p("Sagi", 1);
	p.AddCardsFromDeck(24, &d);
	cout << p.toString() << endl;
	CardValue cv = p.getMostAppearancesCard();
	cout << cv.number << ", " << cv.figure << endl;
	*/

	/*
	p.giveMePlease(5);
	cout << p.toString() << endl;
	p.giveMePlease(Figure::King);
	cout << p.toString() << endl;
	p.giveMePlease(7);
	cout << p.toString() << endl;
	*/

	/*
	Hand h1;
	NumericCard c1(Shape::Heart, 2);
	NumericCard c2(Shape::Spade, 2);
	NumericCard c3(Shape::Heart, 5);
	NumericCard c4(Shape::Heart, 6);
	FigureCard c5(Shape::Club, Figure::Jack);
	FigureCard c6(Shape::Diamond, Figure::Queen);
	FigureCard c7(Shape::Heart, Figure::King);
	FigureCard c8(Shape::Spade, Figure::Ace);
	FigureCard c9(Shape::Spade, Figure::Jack);
	
	h1.addCard(c1);
	h1.addCard(c2);
	h1.addCard(c3);
	h1.addCard(c4);
	h1.addCard(c5);
	h1.addCard(c6);
	h1.addCard(c7);
	h1.addCard(c8);
	h1.addCard(c9);

	cout << h1.getNumberOfCards() << endl;		
	cout << h1.toString() << endl; 

	FigureCard c10(Shape::Heart, Figure::King);
	FigureCard c11(Shape::Spade, Figure::Ace);
	FigureCard c12(Shape::Spade, Figure::Jack);

	h1.removeCard(c10);
	h1.removeCard(c11);
	h1.removeCard(c12);

	cout << h1.getNumberOfCards() << endl;		
	cout << h1.toString() << endl; 
	*/

	/*
	FigureCard fCard1 = FigureCard(Shape::Club, Figure::Ace);
	FigureCard fCard2 = fCard1;
	NumericCard nCard1 = NumericCard(Shape::Heart, 10);
	NumericCard nCard2 = nCard1;

	cout << fCard1.ToString() << endl;
	cout << fCard2.ToString() << endl;
	cout << nCard1.ToString() << endl;
	cout << nCard2.ToString() << endl;

	FigureCard fCard3 = FigureCard(Shape::Club, Figure::Ace);
	FigureCard fCard4 = FigureCard(Shape::Club, Figure::Queen);
	//Card c1 = (Card)fCard1;
	//Card c3 = (Card)fCard3;
	//Card c4 = (Card)fCard4;
	cout << (fCard1 == fCard3)<< endl; 	
	cout << (fCard1 == fCard4) << endl; 	
	*/

	/*
	Card* c1 = new FigureCard(Shape::Club, Figure::Ace);
	Card* c2 = new NumericCard(Shape::Club, 2);

	string s_c1 = c1->ToString();
	string s_c2 = c2->ToString();

	cout << (*c2 < *c1) << endl;
	cout << (s_c2 < s_c1) << endl;
	*/

	/*
	Club,
	Diamond,
	Heart,
	Spade
	*/

	/*
	list<Card * > cards;	
	cards.push_back(new NumericCard(Shape::Heart, 2));
	cards.push_back(new NumericCard(Shape::Spade, 2));
	cards.push_back(new NumericCard(Shape::Club, 2));
	cards.push_back(new NumericCard(Shape::Diamond, 2));
	cards.push_back(new NumericCard(Shape::Heart, 5));
	cards.push_back(new NumericCard(Shape::Heart, 6));
	cards.push_back(new NumericCard(Shape::Heart, 7));
	cards.push_back(new NumericCard(Shape::Heart, 8));
	cards.push_back(new NumericCard(Shape::Heart, 9));
	cards.push_back(new NumericCard(Shape::Heart, 10));
	cards.push_back(new FigureCard(Shape::Club, Figure::Jack));
	cards.push_back(new FigureCard(Shape::Diamond, Figure::Queen));
	cards.push_back(new FigureCard(Shape::Heart, Figure::King));
	cards.push_back(new FigureCard(Shape::Spade, Figure::Ace));
	cards.push_back(new FigureCard(Shape::Spade, Figure::Jack));
	cards.push_back(new FigureCard(Shape::Spade, Figure::Queen));
	cards.push_back(new FigureCard(Shape::Spade, Figure::King));

 	cards.sort(comp<Card>);

	list<Card * >::iterator it;
	for (it=cards.begin(); it!=cards.end(); ++it)
		cout << (*it)->toString() << endl;
	*/

	return 0;
}

