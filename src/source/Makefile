#
# ICP Project - 6.5.2015
# Makefile
# Authors: Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
#          Irena Talašová   (xtalas04@stud.fit.vutbr.cz)
#

# Names of output executable files

NAME=labyrinth2015-cli

# Headers directory

INC=../header

# Names of object files

OBJECT=main.o arguments.o exception.o gameboard.o game.o playerlist.o stone.o player.o cardpack.o treasurecard.o holdingtreasure.o

# Compiler

CXX=g++

# Compiler flags

CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g -W -O3 -I$(INC)/

# Start rule

.PHONY: all clean

all: labyrinth2015-cli

# Universal rule to generate obejct files	

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking required object files to runnable binary files

$(NAME): $(OBJECT)
	$(CXX) $(OBJECT) -o ../../$@

clean:
	rm -f *~ *.o

# End of Makefile
