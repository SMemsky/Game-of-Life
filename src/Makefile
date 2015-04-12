Target = life

CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lGL

all: game

game: main.o Game.o Map.o
	$(CXX) main.o Game.o Map.o -o $(Target) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Map.o: Map.cpp Map.h
	$(CXX) $(CXXFLAGS) -c Map.cpp

clean:
	rm -f *.o

.PHONY: all game clean