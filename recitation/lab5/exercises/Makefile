prodcons: prodcons.c
	gcc -pthread -o prodcons prodcons.c
	./prodcons

barrier: barrier.c
	gcc -pthread -o barrier barrier.c
	./barrier

deliver: prodcons.c barrier.c
	zip ../deliver.zip prodcons.c barrier.c Makefile