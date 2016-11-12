#include "Game.h"

/* Game implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Game::Game(char* configurationFile)
{
	this->_configurationFile = configurationFile;
}

/* Private methods:
 * -----------------------------------------------------------
 */

Player* Game::createPlayer(string name, string type, int position)
{
	if (type == "1")
		return new PlayerType1(name, position);
	else if(type == "2")
		return new PlayerType2(name, position);
	else if(type == "3")
		return new PlayerType3(name, position);
	else if(type == "4")
		return new PlayerType4(name, position);
	
	return nullptr;
}

Card* Game::createCardFromString(string card_string)
{
	Card* card = nullptr;
	if (regex_match(card_string, regex("^\\d.*")))
	{
		card = new NumericCard(card_string);	
	}
	else
		card = new FigureCard(card_string);
	return card;
}

/* Public methods:
 * -----------------------------------------------------------
 */

void Game::init()
{
	ifstream file(this->_configurationFile);
    string line; 
	
	while (getline(file, line)) 	/* First parameter. */
		if (line[0] != '#') 		/* Ignoring comments. */
			break;
	this->_verbal = (line == "1") ? true : false;
	
	while (getline(file, line)) 	/* Second parameter. */
		if (line[0] != '#') 		/* Ignoring comments. */
			break;

	int max_numeric_value;
	stringstream(line) >> max_numeric_value;

	this->deck.setMaximumNumeric(max_numeric_value); /* TODO: Still dont see the point for that member. */

	while (getline(file, line)) 	/* Third parameter. */
		if (line[0] != '#') 		/* Ignoring comments. */
			break;

	/* Initialize the deck! */
	string card_string;
	stringstream ss(line);
	while (ss >> card_string)
		this->deck.pushCardFront(createCardFromString(card_string));

	/* Initialize the players! */
	int position = 0;
    while (getline(file, line)) 	/* Players list! */
    {
		if (line[0] == '#') 		/* Ignoring comments. */
			continue;

		string player_name;
		string player_type;
		stringstream ss(line);
		ss >> player_name;
		ss >> player_type;

		Player* player = createPlayer(player_name, player_type, position); 
		if (player)
			this->players.push_back(player);

		position++;
    }
}

void Game::play()
{

}

void Game::printState()
{

}

void Game::printWinner()
{

}

void Game::printNumberOfTurns()
{

}
