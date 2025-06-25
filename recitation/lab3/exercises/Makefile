redirect: redirect.c
	gcc -o redirect.o redirect.c
	./redirect.o

server: child server.c
	gcc -o server.o server.c
	./server.o
	
child: child.c
	gcc -o child.o child.c

.PHONY: clean

clean:
	rm *.o
	rm *.txt