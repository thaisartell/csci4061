# Complete the Makefile to generate unlinked object files dep1.o, dep2.o and executable root.o
# There are multiple ways to complete the Makefile
# You should not remove root, dep1, dep2. The final solution will ensure that calling 'make -f Makefile1.mk root' will execute root.o

root: dep1 dep2
	./root.o

root.o: root.c
	gcc -o root.o root.c

# Execute object file d1.o
dep1: dep1.o
	./dep1.o

# Compile d1.o
dep1.o: dep1.c
	gcc -o dep1.o -c dep1.c

# Execute object file d2.o
dep2: dep2.o
	./dep2.o

# Compile d2.o
dep2.o: dep2.c
	gcc -o dep2.o -c dep2.c
