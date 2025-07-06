matrix: matrix.c
	gcc -g -pthread -o matrix.o matrix.c
	./matrix.o 10000 1
	./matrix.o 10000 2
	./matrix.o 10000 4
	./matrix.o 10000 8

.PHONY: clean

clean:
	rm -f *.o