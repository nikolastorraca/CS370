CC = gcc
CFLAGS=-Wall

#build: Generator Child
#Lucas HexagonialSeries HarmonicSeries

build: Generator Child

Child: Child.c
	$(CC) -o Child $(CFLAGS) Child.c

Generator: Generator.o
	$(CC) -o Generator $(CFLAGS) Generator.c

clean:
	rm -f *.o Generator Child

test:
	./Generator
