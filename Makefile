CC=g++
CFLAGS=-g -Wall -Weffc++ -std=c++11

all: bin/Card.o bin/Hand.o bin/Deck.o bin/Player.o bin/Game.o
	$(CC) -o bin/reviyot src/reviyot.cpp bin/Card.o bin/Hand.o bin/Deck.o bin/Player.o bin/Game.o $(CFLAGS)

bin/Card.o: Include/Card.h src/Card.cpp
	$(CC) -c -o bin/Card.o src/Card.cpp $(CFLAGS)

bin/Hand.o: Include/Hand.h src/Hand.cpp
	$(CC) -c -o bin/Hand.o src/Hand.cpp $(CFLAGS)

bin/Deck.o: Include/Deck.h src/Deck.cpp
	$(CC) -c -o bin/Deck.o src/Deck.cpp $(CFLAGS)

bin/Player.o: Include/Player.h src/Player.cpp
	$(CC) -c -o bin/Player.o src/Player.cpp $(CFLAGS)

bin/Game.o: Include/Game.h src/Game.cpp
	$(CC) -c -o bin/Game.o src/Game.cpp $(CFLAGS)

clean:
	rm bin/*.o
