p1: p1.c
	gcc -pthread -o p1.o p1.c
	./p1.o 1 2

p2: p2.c
	gcc -pthread -o p2.o p2.c
	./p2.o 32 8

p3: p3.c
	gcc -pthread -o p3.o p3.c
	./p3.o 32 8

p4: p4.c
	gcc -pthread -o p4.o p4.c
	# Run [ for i in {1..1000}; do ./p4.o; done | sort -n | uniq -c ] on terminal to see the race condition

p5: p5.c
	gcc -pthread -o p5.o p5.c
	# Run [ for i in {1..1000}; do ./p5.o; done | sort -n | uniq -c ] on terminal to see the race condition

.PHONY: clean

clean:
	rm -f *.o