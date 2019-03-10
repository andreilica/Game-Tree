build:minimax

minimax: main.o
	gcc -Wall main.o -o minimax -std=c99

main.o: main.c
	gcc -Wall -c main.c -std=c99

clean:
	rm -rf *.o minimax