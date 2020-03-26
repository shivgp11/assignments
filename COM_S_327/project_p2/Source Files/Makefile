all: check advance

check: project.o parse.o checkRules.o checkFoundations.o checkTableau.o	checkCards.o checkMoves.o checkStock.o 
	gcc -o check project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o

advance: project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o 
	gcc -o advance project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o

main.o: project.c
	gcc -c project.c

parse.o: parse.c parse.h
	gcc -c parse.c

checkRules.o: checkRules.c check.h
	gcc -c checkRules.c

checkFoundations.o: checkFoundations.c check.h
	gcc -c checkFoundations.c

checkTableau.o: checkTableau.c check.h
	gcc -c checkTableau.c

checkCards.o: checkCards.c check.h
	gcc -c checkCards.c

checkStock.o: checkStock.c check.h
	gcc -c checkStock.c

checkMoves.o: checkMoves.c check.h
	gcc -c checkMoves.c

clean:
	rm *.o check