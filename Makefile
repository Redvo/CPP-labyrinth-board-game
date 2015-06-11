#
# ICP Project - 6.5.2015
# Makefile
# Authors: Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
#          Irena Talašová   (xtalas04@stud.fit.vutbr.cz)
#

# Names of output executable files

NAME=labyrinth2015
NAME-CLI=labyrinth2015-cli

# Names of object files

OBJECT=main.o arguments.o exception.o gameboard.o game.o playerlist.o stone.o player.o cardpack.o treasurecard.o holdingtreasure.o

# Compiler

CXX=g++

# Compiler flags

CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g -W -O3 -I$(INC)/

# Start rule

.PHONY: all clean doxygen pack run

all: 
	cd src/source; make
	cd src/gui; /usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake gui.pro
	cd src/gui; make

$(NAME):
	cd src/gui; /usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake gui.pro
	cd src/gui; make

$(NAME-CLI):
	cd src/source; make

clean:
	cd src/source; make clean
	cd src/gui; make clean
	rm $(NAME) $(NAME-CLI)

doxygen:
	cd doc; doxygen Doxyfile

pack:
	zip -r xrendv00-xtalas04.zip Makefile README.txt src/ example/ doc/

run: $(NAME)
	chmod u+x $(NAME)
	./$(NAME)
