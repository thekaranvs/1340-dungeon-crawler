hangman.o: includes/hangman.cpp includes/hangman.h
	g++ -pedantic-errors -std=c++11 -c -w $<

snakes.o: includes/snakes.cpp includes/snakes.h
	g++ -pedantic-errors -std=c++11 -c -w $<

tic.o: includes/tic.cpp includes/tic.h
	g++ -pedantic-errors -std=c++11 -c -w $<
	
main.o : main.cpp includes/tic.h includes/snakes.h includes/hangman.h
	g++ -pedantic-errors -std=c++11 -c -w $<

game: main.o hangman.o snakes.o tic.o
	g++ -pedantic-errors -std=c++11 $^ -o $@

clean:
	rm -f hangman.o snakes.o tic.o main.o game

.PHONY: clean
