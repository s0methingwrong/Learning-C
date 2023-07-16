all: main

main: main.o item_types.o list.o qtree.o out_qtree.o
	gcc main.o item_types.o list.o qtree.o out_qtree.o -o main

main.o: main.c
	gcc -c main.c

list.o: list.c
	gcc -c list.c

qtree.o: qtree.c
	gcc -c qtree.c

out_qtree.o: out_qtree.c
	gcc -c out_qtree.c

item_types.o: item_types.c
	gcc -c item_types.c

clean:
	rm -rf *.o main