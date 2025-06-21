fanout: clean fanout.c
	gcc -o fanout.o fanout.c
	./fanout.o 5

chain: clean chain.c
	gcc -o chain.o chain.c
	./chain.o 5

traverse: clean traverse.c
	gcc -o traverse.o traverse.c
	./traverse.o nestdir

callall: clean fanout.c traverse.c callall.c
	gcc -o fanout.o fanout.c
	gcc -o traverse.o traverse.c
	gcc -o callall.o callall.c
	./callall.o

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.txt