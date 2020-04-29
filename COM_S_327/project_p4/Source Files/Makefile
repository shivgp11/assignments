all: check advance game

check: project.o parse.o checkRules.o checkFoundations.o checkTableau.o	checkCards.o checkMoves.o checkStock.o 
	gcc -o check project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o

advance: project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o 
	gcc -o advance project.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkMoves.o checkStock.o

game: game.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkStock.o display.o checkMoves.o random.o
	gcc -o game game.o parse.o checkRules.o checkFoundations.o checkTableau.o checkCards.o checkStock.o display.o checkMoves.o random.o /share/cs327/lib/libtermbox.a

game.o: game.c 
	gcc -c -I/share/cs327/include game.c /share/cs327/lib/libtermbox.a

project.o: project.c 
	gcc -c project.c 

display.o: display.c display.h
	gcc -c -I/share/cs327/include display.c /share/cs327/lib/libtermbox.a

random.o: random.c
	gcc -c random.c

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

compare.o: compare.c 
	gcc -c compare.c

clean:
	rm *.o check advance game