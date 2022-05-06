hangman.o: includes/hangman.cpp includes/hangman.h
	g++ -c $<

snakes.o: includes/snakes.cpp includes/snakes.h
	g++ -c $<

tic.o: includes/tic.cpp includes/tic.h
	g++ -c $<

game: main.cpp hangman.o snakes.o tic.o
	g++ $^ -o $@

clean:
	rm -f hangman.o snakes.o tic.o game

.PHONY: clean