morsegame: main.o morse.o player.o
	g++ -o morsegame main.o morse.o player.o -lportaudio -lncurses -DNCURSES_STATIC

main.o: main.cpp binout.h
	g++ -c main.cpp -lncurses -DNCURSES_STATIC

morse.o: morse.h morse.cpp
	g++ -c morse.cpp

player.o: player.h player.cpp
	g++ -c player.cpp -lportaudio -lncurses -DNCURSES_STATIC

clean: 
	rm morsegame player.o morse.o main.o
