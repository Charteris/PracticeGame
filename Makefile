all: compile link

compile:
	g++ -Isrc/include -c src/main.cpp

link:
	g++ main.o -o sfml-app -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system