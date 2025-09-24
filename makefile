snake : graphique.o pommes.o serpent.o obstacles.o main.o
	gcc -o snake graphique.o serpent.o pommes.o obstacles.o main.o -lgraph
run : snake
	./snake
graphique.o : graphique.c
	gcc -c graphique.c -lgraph
serpent.o : serpent.c
	gcc -c serpent.c -lgraph
pommes.o : pommes.c
	gcc -c pommes.c -lgraph
obstacles.o : obstacles.c
	gcc -c obstacles.c -lgraph
main.o : main.c
	gcc -c main.c -lgraph
clean :
	rm -f main.o graphique.o serpent.o pommes.o obstacles.o snake
