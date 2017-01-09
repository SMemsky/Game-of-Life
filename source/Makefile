# Makefile for Dexter3000's implementation of Conway's Game of Life

Target = life
TargetPath = ../build/

SFMLDeps = -lsfml-system -lsfml-graphics -lsfml-window

LinuxLinkerFlags = -lGL
MacLinkerFlags = -framework OpenGL

CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++14 -I./ -O0
LDFLAGS = $(SFMLDeps) -lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS += $(LinuxLinkerFlags)
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += $(MacLinkerFlags)
endif

MAIN_OBJECTS = main.o \
	Game.o \
	Map.o

all: game

game: $(MAIN_OBJECTS)
	$(CXX) $(MAIN_OBJECTS) -o $(TargetPath)$(Target) $(LDFLAGS)

main.o: main.cpp \
		Game.h \
		Map.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.cpp Game.h \
		Map.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Map.o: Map.cpp Map.h
	$(CXX) $(CXXFLAGS) -c Map.cpp

clean:
	rm -f *.o

.PHONY: all game clean
