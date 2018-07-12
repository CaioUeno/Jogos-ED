exe : comp
	./Jogo
comp : main.o Map.o Tree.o
	g++ main.o Map.o Tree.o Map.h Tree.h -o Jogo
play : Jogo
	./Jogo
Map.o : Map.c
	g++ Map.c -c
Tree.o : Tree.c
	g++ Tree.c -c
main.o : main.c
	g++ main.c -c
clean :
	rm Jogo Tree.o Map.o main.o
