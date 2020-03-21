all: check

check: project.o parse.o checkRules.o checkFoundations.o checkTableau.o	checkCards.o checkMoves.o checkStock.o 
	gcc -o check project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o

main.o: project.c
	gcc -c project.c

parse.o: parse.c parse.h
	gcc -c parse.c

checkRules.o: checkRules.c checkRules.h
	gcc -c checkRules.c

checkFoundations.o: checkFoundations.c checkFoundations.h
	gcc -c checkFoundations.c

checkTableau.o: checkTableau.c checkTableau.h
	gcc -c checkTableau.c

checkCards.o: checkCards.c checkCards.h
	gcc -c checkCards.c

checkStock.o: checkStock.c checkStock.h
	gcc -c checkStock.c

checkMoves.o: checkMoves.c checkMoves.h
	gcc -c checkMoves.c

clean:
	rm *.o check