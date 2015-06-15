#
# ICP Project - 6.5.2015
# Makefile
# Authors: Lukáš Rendvanský (xrendv00@stud.fit.vutbr.cz)
#          Irena Talašová   (xtalas04@stud.fit.vutbr.cz)
#

# Names of output executable files

NAME=labyrinth2015
NAME-CLI=labyrinth2015-cli

# Start rule

.PHONY: all clean doxygen pack run

all: $(NAME) $(NAME-CLI)

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
