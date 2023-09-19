CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = chess
OBJECTS = main.o Bishop.o ComputerPlayer.o GameBoard.o King.o Knight.o Pawn.o Piece.o Player.o Queen.o Rook.o TextDisplay.o scoreboard.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
