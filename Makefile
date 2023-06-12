CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = cell.o chamber.o character.o decorator.o enemy.o floor.o game.o main.o observer.o player.o potion.o seed.o subject.o textdisplay.o thing.o treasure.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}
	