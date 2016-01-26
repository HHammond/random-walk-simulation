CC = gcc
FLAGS = -std=c11

walk: walk.c
	$(CC) walk.c $(FLAGS) -o walk

simulation.txt: walk
	time ./walk 20000 20000 \
		| sort -n \
		| uniq -c \
		| awk 'BEGIN{ print "Value\tFrequency" }{ print $$2,"\t", $$1 }' \
		> simulation.txt

clean:
	- rm simulation.txt
	- rm walk
