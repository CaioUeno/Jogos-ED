exe : main.o Atom.o
	g++ main.o Atom.o Atom.h -o Jogo
	./Jogo
comp : main.o Atom.o
	g++ main.o Atom.o Atom.h -o Jogo
play : Jogo
	./Jogo
main.o : main.c
	g++ main.c -c
Atom.o : Atom.c
	g++ Atom.c -c
clean :
	rm Jogo Atom.o main.o
