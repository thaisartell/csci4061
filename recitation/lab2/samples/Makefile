p1: clean p1.c
	gcc -o p1.o p1.c
	./p1.o
	
p2: clean p2.c
	gcc -o p2.o p2.c
	./p2.o 0
	./p2.o 1
	./p2.o 2
	./p2.o 3

p3: clean p3.c
	gcc -o p3.o p3.c
	./p3.o 5

p4: clean p4.c
	gcc -o p4.o p4.c
	./p4.o

p5: clean p5.c
	gcc -o p5.o p5.c
	./p5.o p5_text.txt 1
	./p5.o p5_text.txt 2
	./p5.o p5_text.txt 3

p6: clean p6.c
	gcc -o p6.o p6.c
	./p6.o tdir
	
.PHONY: clean

clean:
	rm -f *.o
	rm -f *.txt