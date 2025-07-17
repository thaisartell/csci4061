philo: philo.c
	gcc -pthread -g -o philo philo.c
	./philo > out.txt

.PHONY: deliver clean 

deliver:
	zip ../deliver.zip philo.c out.txt Makefile

clean:
	rm -f philo out.txt