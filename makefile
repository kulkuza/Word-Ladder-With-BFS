build:
	clear
	gcc -std=c99 -pedantic main.c avl.c graph.c mymem.c queue.c set.c stack.c

run:
	clear
	./a.out
