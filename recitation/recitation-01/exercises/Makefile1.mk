# Complete the Makefile to generate unlinked object files dep1.o, dep2.o and executable root.o
# There are multiple ways to complete the Makefile
# You should not remove root, dep1, dep2. The final solution will ensure that calling 'make -f Makefile1.mk root' will execute root.o

root: dep1 dep2
	gcc -g -o root.o root.c dep1.o dep2.o

dep1:
	gcc -o dep1.o -c dep1.c

dep2:
	gcc -o dep2.o -c dep2.c