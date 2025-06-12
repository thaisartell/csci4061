###########################
# p1 target : p1.o dependency (check if p1.o is present in the current folder and is up to date: else check for another target named p1.o)
#	./p1.o recipe
p1: p1.o
	./p1.o

# p1.o depends on file p1.c. Make checks if the file was recently updated, if so, the recipe is run
p1.o: p1.c
	gcc -o $@ p1.o p1.c
###########################

###########################
p2: one two
	# Outputs "p2", since this is the target name
	echo $@

	# Outputs all prerequisites newer than the target
	echo $?

	# Outputs all prerequisites
	echo $^

	touch p2

one:
	touch one

two:
	touch two
###########################

p3: p3.c
	gcc -g -o p3.o p3.c

p4: p4.c
	gcc -g -o p4.o p4.c

###########################

# no dependencies for phony targets
.PHONY: clean

# clean up target
clean:
	rm -f *.o
	rm -f p2 one two

