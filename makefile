morsegame: main.o morse.o player.o
	g++ -o morsegame main.o morse.o player.o -lportaudio -lncurses

main.o: main.cpp binout.h
	g++ -c main.cpp -lncurses

morse.o: morse.h morse.cpp
	g++ -c morse.cpp

player.o: player.h player.cpp
	g++ -c player.cpp -lportaudio -lncurses

clean: 
	rm morsegame player.o morse.o main.o
