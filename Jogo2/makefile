exe : main.o BlackJack.o Stack.o
	g++ main.o BlackJack.o Stack.o Stack.h  BlackJack.h -o Jogo
	./Jogo
comp : main.o Atom.o
	g++ main.o Atom.o Atom.h -o Jogo
play : Jogo
	./Jogo
BlackJack.o : BlackJack.c
	g++ BlackJack.c -c
Stack.o : Stack.c
	g++ Stack.c -c
main.o : main.c
	g++ main.c -c
clean :
	rm Jogo Stack.o BlackJack.o main.o
