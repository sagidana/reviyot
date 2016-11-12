CC=g++
CFLAGS=-std=c++11

all: Card.o Hand.o Deck.o Player.o Game.o
	$(CC) -o reviyot reviyot.cpp Card.o Hand.o Deck.o Player.o Game.o $(CFLAGS)

Card.o: Card.h Card.cpp
	$(CC) -c -o Card.o Card.cpp $(CFLAGS)

Hand.o: Hand.h Hand.cpp
	$(CC) -c -o Hand.o Hand.cpp $(CFLAGS)

Deck.o: Deck.h Deck.cpp
	$(CC) -c -o Deck.o Deck.cpp $(CFLAGS)

Player.o: Player.h Player.cpp
	$(CC) -c -o Player.o Player.cpp $(CFLAGS)

Game.o: Game.h Game.cpp
	$(CC) -c -o Game.o Game.cpp $(CFLAGS)

