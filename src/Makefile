Target = life

CXX = g++
CXXFLAGS =
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lGL

all: game

game: main.o Game.o
	$(CXX) main.o Game.o -o $(Target) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

clean:
	rm -f *.o

.PHONY: all game clean