all: main

main: main.o list.o tree.o out_tree.o
	gcc main.o list.o tree.o out_tree.o -o main

main.o: main.c
	gcc -c main.c

list.o: list.c
	gcc -c list.c

tree.o: tree.c
	gcc -c tree.c

out_tree.o: out_tree.c
	gcc -c out_tree.c

clean:
	rm -rf *.o hello