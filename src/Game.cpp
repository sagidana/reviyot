#include "../Include/Game.h"

/* Game implementation:
 * -----------------------------------------------------------
 */
/* C-tors & D-tors
 * -----------------------------------------------------------
 */

Game::Game(char* configurationFile) : _configurationFile(configurationFile), _verbal(false), players(vector<Player*>()), deck(Deck()), _numberOfTurns(0) { }

Game::Game(const Game& other) : _configurationFile(other._configurationFile), _verbal(other._verbal), players(vector<Player*>()), deck(other.deck), _numberOfTurns(other._numberOfTurns)
{
	uninitializePlayers();
	
	for (auto it=other.players.begin(); it!=other.players.end(); ++it)
	{
		if (PlayerType1 * pt1 = dynamic_cast<PlayerType1 * >(*it))		
			this->players.push_back(new PlayerType1(*pt1));
		else if (PlayerType2 * pt2 = dynamic_cast<PlayerType2 * >(*it))		
			this->players.push_back(new PlayerType2(*pt2));
		else if (PlayerType3 * pt3 = dynamic_cast<PlayerType3 * >(*it))		
			this->players.push_back(new PlayerType3(*pt3));
		else if (PlayerType4 * pt4 = dynamic_cast<PlayerType4 * >(*it))		
			this->players.push_back(new PlayerType4(*pt4));
	}	
}

Game::~Game()
{
	uninitializePlayers();
}

/* Private methods:
 * -----------------------------------------------------------
 */

void Game::uninitializePlayers()
{
	for (auto it = this->players.begin(); it != this->players.end(); ++it)
		delete *it;
		
	this->players.clear();
}

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

Player* Game::getPlayerByPosition(int position)
{
	for(auto it = this->players.begin(); it != this->players.end(); ++it)
		if ((*it)->getPosition() == position)
			return *it;

	return nullptr;
}

void Game::giveCardsToPlayers()
{
	for (auto it=this->players.begin(); it!=this->players.end(); ++it)
	{
		(*it)->AddCardsFromDeck(7, &this->deck);
	}
}

bool Game::gameFinished()
{
	for (auto it=this->players.begin(); it!=this->players.end(); ++it)
		if ((*it)->isFinished())
			return true;
	return false;
}

vector<Player*> Game::playersWithout(string playerName)
{
	vector<Player*> ret_players;
	
	for (auto it=this->players.begin(); it!=this->players.end(); ++it)
		if ((*it)->getName() != playerName)
			ret_players.push_back(*it);
	
	return ret_players;
}

/* Public methods:
 * -----------------------------------------------------------
 */

Game & Game::operator=(const Game & other)
{
	uninitializePlayers();
	
	this->_configurationFile = other._configurationFile;
	this->_verbal = other._verbal;
	this->deck = other.deck;
	
	for (auto it=other.players.begin(); it!=other.players.end(); ++it)
	{
		if (PlayerType1 * pt1 = dynamic_cast<PlayerType1 * >(*it))		
			this->players.push_back(new PlayerType1(*pt1));
		else if (PlayerType2 * pt2 = dynamic_cast<PlayerType2 * >(*it))		
			this->players.push_back(new PlayerType2(*pt2));
		else if (PlayerType3 * pt3 = dynamic_cast<PlayerType3 * >(*it))		
			this->players.push_back(new PlayerType3(*pt3));
		else if (PlayerType4 * pt4 = dynamic_cast<PlayerType4 * >(*it))		
			this->players.push_back(new PlayerType4(*pt4));
	}

	return *this;
}

void Game::init()
{
	ifstream file(this->_configurationFile);
    string line; 
	
	while (getline(file, line)) 						/* First parameter. */
		if ((line.size() > 0) && (line[0] != '#')) 		/* Ignoring comments. */
			break;
	this->_verbal = (line == "1") ? true : false;
	
	while (getline(file, line)) 						/* Second parameter. */
		if ((line.size() > 0) && (line[0] != '#')) 		/* Ignoring comments. */
			break;

	int max_numeric_value;
	stringstream(line) >> max_numeric_value;
	
	this->deck.setMaximumNumeric(max_numeric_value); /* TODO: Still dont see the point for that member. */

	while (getline(file, line)) 						/* Third parameter. */
		if ((line.size() > 0) && (line[0] != '#')) 		/* Ignoring comments. */
			break;

	/* Initialize the deck! */
	string card_string;
	stringstream ss(line);
	while (ss >> card_string)
		this->deck.pushCardFront(createCardFromString(card_string));

	/* Initialize the players! */
	int position = 0;
    while (getline(file, line)) 							/* Players list! */
    {
		if ((line.size() == 0) || (line[0] == '#'))  		/* Ignoring comments. */
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
    
   	giveCardsToPlayers();
}

void Game::play()
{
	while (!gameFinished())
	{
		Player * currentPlayer = getPlayerByPosition(this->_numberOfTurns % this->players.size());
		
		if (this->_verbal)
		{
			cout << "Turn " << this->_numberOfTurns + 1 << endl;
			printState();
			cout << currentPlayer->getPlayDecision(playersWithout(currentPlayer->getName())) << endl;;
			cout << endl;
		}

		currentPlayer->play(&this->deck, playersWithout(currentPlayer->getName()));
		
		this->_numberOfTurns++;
	}
}

void Game::printState()
{	
	cout << "Deck: " << this->deck.toString() << endl;
	
	for (auto it=this->players.begin(); it!=this->players.end(); ++it)
		cout << (*it)->toString() << endl;
}

void Game::printWinner()
{
	list<Player*> winners;
	for (auto it=this->players.begin(); it!=this->players.end(); ++it)
		if ((*it)->isFinished())
			winners.push_back(*it);
	if (winners.size() == 1)
		cout << "***** The Winner is: " << winners.back()->getName() << " *****" << endl;
	else if (winners.size() == 2)
	{
		string second = winners.back()->getName();
		winners.pop_back();
		string first = winners.back()->getName();		
		winners.pop_back();
		
		cout << "***** The winners are: " << first << " and " << second << " *****" << endl;
	}
}

void Game::printNumberOfTurns()
{
	cout << "Number of turns: " << this->_numberOfTurns << endl;
}
























































































































