#include "Player.h"

/* Player implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Player::Player(string name, int position) : _name(name), _position(position) { }

Player::Player(const Player & other)
{
	copyPlayer(&other);
}

Player::~Player() { }

/* Private methods:
 * -----------------------------------------------------------
 */

Card* Player::findCard(CardValue card_value)
{
	Card* ret_card = nullptr;

	auto it = find_if(this->_cards.begin(), this->_cards.end(), [&](Card * c)->bool 
		{ 
			return c->getCardValue() == card_value;
		}); 
	
	if 	(it != this->_cards.end()) /* find_if return the last in case of no results. */
	{
		ret_card = *it;
		removeCard(**it);
	}	

	return ret_card;
}

/* Protected methods:
 * -----------------------------------------------------------
 */
 
void Player::copyPlayer(const Player * other)
{
	uninitializeCards();
	
	for (auto it=other->_cards.begin(); it!=other->_cards.end(); ++it)
	{
		if (NumericCard * nCard = dynamic_cast<NumericCard * >(*it))		
			this->_cards.push_back(new NumericCard(*nCard));
		else if(FigureCard * fCard = dynamic_cast<FigureCard * >(*it))
			this->_cards.push_back(new FigureCard(*fCard));
	}
	
	this->_name = other->_name;
	this->_position = other->_position;
}

Player* Player::getPlayerByPosition(int position, vector<Player*> players)
{
	for(auto it = players.begin(); it != players.end(); ++it)
		if ((*it)->getPosition() == position)
			return *it;

	return nullptr;
}

Player* Player::getMostCardsPlayer(vector<Player*> players)
{
	Player * most_cards_player = nullptr;
	int max_cards = 0;

	for(auto it = players.begin(); it != players.end(); ++it)
	{
		int curr_num_of_cards = (*it)->getNumberOfCards();

		if (curr_num_of_cards > max_cards)
		{
			most_cards_player = *it;
			max_cards = curr_num_of_cards;
		}
		else if (curr_num_of_cards == max_cards)
			if (most_cards_player->getPosition() < (*it)->getPosition())
				most_cards_player = *it;
	}

	return most_cards_player;
}

/* Public methods:
 * -----------------------------------------------------------
 */
 
Player & Player::operator=(const Player & other)
{
	copyPlayer(&other);
	
	return *this;
}
 
string Player::getName() { return this->_name; }

int Player::getPosition() { return this->_position; }

bool Player::isFinished() { return getNumberOfCards() == 0; }

void Player::AddCardsFromDeck(int numberOfCards, Deck* deck)
{
	for (int index = 0; index < numberOfCards; index++)
	{
		Card* card = deck->fetchCard();
		if (card)	
			addCard(*card);
	}
	
	discardSets();
}

string Player::toString()
{
	return getName() + ": " + ((Hand * )this)->toString();
}

list<Card*> Player::giveMePlease(CardValue card_value)
{
	list<Card*> ret_cards;
	Card* card = findCard(card_value);

	while (card != nullptr)
	{
		ret_cards.push_back(card);
		card = findCard(card_value);
	}
	
	return ret_cards;
}

list<Card*> Player::giveMePlease(CardValue card_value, Deck * deck)
{
	list<Card*> ret_cards = giveMePlease(card_value);

	if (ret_cards.size() > 0)
	{
		AddCardsFromDeck(ret_cards.size(), deck);

		discardSets();
	}
	
	return ret_cards;
}

void Player::discardSets()
{
	int number_of_appearances = 0;
	CardValue card_value;
	list<CardValue> values_to_remove;
	
	this->_cards.sort(comp<Card>); /* Sorting the hand before searching for sets */

	for (auto it = this->_cards.begin(); it != this->_cards.end(); ++it)
	{
		CardValue curr_card_value = (*it)->getCardValue();

		if (card_value == curr_card_value)
		{
			number_of_appearances++;
		}
		else
		{
			number_of_appearances = 1;
			card_value = curr_card_value;
		}
		
		if (number_of_appearances == 4)  	/* Removing the set from hand. */
			values_to_remove.push_back(card_value);
	}

	for (auto it_1 = values_to_remove.begin(); it_1 != values_to_remove.end(); ++ it_1)
	{
		list<Card*> temp_cards = giveMePlease(*it_1);
		for (auto it_2 = temp_cards.begin(); it_2 != temp_cards.end(); ++it_2)
			delete *it_2;					/* Freeing memory. */
	}
}

/* PlayerType1 implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

PlayerType1::PlayerType1(string name, int position) : Player(name, position) { }

PlayerType1::PlayerType1(const PlayerType1 & other) : Player(other._name, other._position)
{
	copyPlayer(&other);
}

/* Public methods
 * -----------------------------------------------------------
 */

PlayerType1 & PlayerType1::operator=(const PlayerType1 & other)
{
	copyPlayer(&other);
	
	return *this;
}

void PlayerType1::play(Deck* deck, vector<Player * > players)
{
	CardValue card_value = getMostAppearancesCard();
	Player * most_cards_player = getMostCardsPlayer(players);
	
	cout << getName() << " asked " << most_cards_player->getName() << " for the value " << card_value.toString() << endl;
	list<Card*> given_cards = most_cards_player->giveMePlease(card_value, deck);
	
	if (given_cards.size() == 0)
	{
		Card * card = deck->fetchCard(); 	/* Taking card from the deck. 		*/
		if (card)							/* If the deck is empty do nothing. */
		{
			addCard(*card); 
			discardSets();
		}
		return;
	}
	
	for (auto it = given_cards.begin(); it != given_cards.end(); ++it)
		addCard(**it);

	discardSets();
}

/* Protected methods
 * -----------------------------------------------------------
 */

CardValue PlayerType1::getMostAppearancesCard()
{
	CardValue ret_card_value;
	CardValue last_card_value;
	int max_times = 0;
	int current_card_times = 0;

	this->_cards.sort(comp<Card>); 	/* Sorting the hand before starting to search. */

	for(auto it = this->_cards.begin(); it != this->_cards.end(); ++it)
	{
		CardValue curr_card_value = (*it)->getCardValue();
	
		/* Updating the current card's apperences times. */
		if (last_card_value == curr_card_value)
			current_card_times++;
		else
			current_card_times = 1;	
		
		last_card_value = curr_card_value;
		
		/* Update the card value with most appearances. */
		if (max_times <= current_card_times)
		{
			ret_card_value = last_card_value;
			max_times = current_card_times;
		}
	}
	
	return ret_card_value;
}

/* PlayerType2 implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

PlayerType2::PlayerType2(string name, int position) : Player(name, position) { }

PlayerType2::PlayerType2(const PlayerType2 & other) : Player(other._name, other._position)
{
	copyPlayer(&other);
}

/* Public methods
 * -----------------------------------------------------------
 */

PlayerType2 & PlayerType2::operator=(const PlayerType2 & other)
{
	copyPlayer(&other);
	
	return *this;
}


void PlayerType2::play(Deck* deck, vector<Player * > players)
{
	CardValue card_value = getLeastAppearancesCard();
	Player * most_cards_player = getMostCardsPlayer(players);
	
	cout << getName() << " asked " << most_cards_player->getName() << " for the value " << card_value.toString() << endl;

	list<Card*> given_cards = most_cards_player->giveMePlease(card_value, deck);
	
	if (given_cards.size() == 0)
	{
		Card * card = deck->fetchCard(); 	/* Taking card from the deck. 		*/
		if (card)							/* If the deck is empty do nothing. */
		{
			addCard(*card); 
			discardSets();
		}
		return;
	}

	for (auto it = given_cards.begin(); it != given_cards.end(); ++it)
		addCard(**it);

	discardSets();
}

/* Protected methods
 * -----------------------------------------------------------
 */

CardValue PlayerType2::getLeastAppearancesCard()
{
	if (this->_cards.empty())	/* Check if hand is empty. */
		return CardValue();

	CardValue ret_card_value;
	CardValue last_card_value = this->_cards.front()->getCardValue();
	int min_times = 100;
	int current_card_times = 0;

	this->_cards.sort(comp<Card>); 	/* Sorting the hand before starting to search. */

	for(auto it = this->_cards.begin(); it != this->_cards.end(); ++it)
	{
		CardValue curr_card_value = (*it)->getCardValue();
	
		/* Updating the current card's apperences times. */
		if (last_card_value == curr_card_value)
			current_card_times++;

		if ((last_card_value != curr_card_value) || (it == --this->_cards.end()))
		{
			/* Update the card value with most appearances. */
			if (min_times > current_card_times)
			{
				ret_card_value = last_card_value;
				min_times = current_card_times;
			}
			current_card_times = 1;	
		}
		
		last_card_value = curr_card_value;	/* Update the last card value */
	}
	
	return ret_card_value;
}

/* PlayerType3 implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

PlayerType3::PlayerType3(string name, int position) : Player(name, position), _nextAskedPlayer(0) { }

PlayerType3::PlayerType3(const PlayerType3 & other) : Player(other._name, other._position)
{
	copyPlayer(&other);
	this->_nextAskedPlayer = other._nextAskedPlayer;
}

/* Protected methods
 * -----------------------------------------------------------
 */

CardValue PlayerType3::getHighestCard()
{
	if (this->_cards.empty())
		return CardValue();

	this->_cards.sort(comp<Card>);
	
	return this->_cards.back()->getCardValue();
}

/* Public methods
 * -----------------------------------------------------------
 */

PlayerType3 & PlayerType3::operator=(const PlayerType3 & other)
{
	copyPlayer(&other);
	this->_nextAskedPlayer = other._nextAskedPlayer;

	return *this;
}


void PlayerType3::play(Deck* deck, vector<Player * > players)
{
	if (getPosition() == this->_nextAskedPlayer)
	{
		this->_nextAskedPlayer = (this->_nextAskedPlayer + 1) % (players.size() + 1);
	}

	Player* player = getPlayerByPosition(this->_nextAskedPlayer, players);

	this->_nextAskedPlayer = (this->_nextAskedPlayer + 1) % (players.size() + 1); /* Increase the position for the next turn */

	CardValue card_value = getHighestCard();

	cout << getName() << " asked " << player->getName() << " for the value " << card_value.toString() << endl;

	list<Card*> given_cards = player->giveMePlease(card_value, deck);

	if (given_cards.size() == 0)
	{
		Card * card = deck->fetchCard(); 	/* Taking card from the deck. 		*/
		if (card)							/* If the deck is empty do nothing. */
		{
			addCard(*card); 
			discardSets();
		}
		return;
	}

	for (auto it = given_cards.begin(); it != given_cards.end(); ++it)
		addCard(**it);

	discardSets();	
}

/* PlayerType4 implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

PlayerType4::PlayerType4(string name, int position) : Player(name, position), _nextAskedPlayer(0) { }

PlayerType4::PlayerType4(const PlayerType4 & other) : Player(other._name, other._position)
{
	copyPlayer(&other);
	this->_nextAskedPlayer = other._nextAskedPlayer;
}

/* Protected methods
 * -----------------------------------------------------------
 */

CardValue PlayerType4::getLowestCard()
{
	if (this->_cards.empty())
		return CardValue();

	this->_cards.sort(comp<Card>);
	
	return this->_cards.front()->getCardValue();
}

/* Public methods
 * -----------------------------------------------------------
 */

PlayerType4 & PlayerType4::operator=(const PlayerType4 & other)
{
	copyPlayer(&other);
	this->_nextAskedPlayer = other._nextAskedPlayer;
	return *this;
}


void PlayerType4::play(Deck* deck, vector<Player * > players)
{
	if (getPosition() == this->_nextAskedPlayer)
	{
		this->_nextAskedPlayer = (this->_nextAskedPlayer + 1) % (players.size() + 1);
	}

	Player* player = getPlayerByPosition(this->_nextAskedPlayer, players);

	this->_nextAskedPlayer = (this->_nextAskedPlayer + 1) % (players.size() + 1); /* Increase the position for the next turn */

	CardValue card_value = getLowestCard();

	cout << getName() << " asked " << player->getName() << " for the value " << card_value.toString() << endl;

	list<Card*> given_cards = player->giveMePlease(card_value, deck);

	if (given_cards.size() == 0)
	{
		Card * card = deck->fetchCard(); 	/* Taking card from the deck. 		*/
		if (card)							/* If the deck is empty do nothing. */
		{
			addCard(*card); 
			discardSets();
		}
		return;
	}

	for (auto it = given_cards.begin(); it != given_cards.end(); ++it)
		addCard(**it);

	discardSets();	
}








































































