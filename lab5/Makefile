all: main

main: main.o listnode.o list.o table.o graph.o graphutils.o
	gcc main.o listnode.o list.o table.o graph.o graphutils.o -o main

main.o: main.c
	gcc -c main.c

list.o: list.c
	gcc -c list.c

listnode.o: listnode.c
	gcc -c listnode.c

graph.o: graph.c
	gcc -c graph.c

graphutils.o: graphutils.c
	gcc -c graphutils.c

table.o: table.c
	gcc -c table.c

clean:
	rm -rf *.o main