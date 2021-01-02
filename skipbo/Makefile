CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

SRC = $(wildcard *.cpp)

# Creates skipbo executable
skipbo: main.cpp
	$(CC) $(CFLAGS) -o skipbo $(SRC)


SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

Card.o: Card.cpp
	$(CC) $(CFLAGS) -c Card.cpp

Pile.o: Pile.cpp
	$(CC) $(CFLAGS) -c Pile.cpp

DrawPile.o: DrawPile.cpp
	$(CC) $(CFLAGS) -c DrawPile.cpp

FaceUpPile.o: FaceUpPile.cpp
	$(CC) $(CFLAGS) -c FaceUpPile.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp

CommandLineError.o: CommandLineError.cpp
	$(CC) $(CFLAGS) -c CommandLineError.cpp
# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o skipbo
