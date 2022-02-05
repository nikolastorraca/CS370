CC = gcc
CFLAGS=-Wall

#build: Generator Child
#Lucas HexagonialSeries HarmonicSeries

build: Generator Child Lucas HexagonalSeries HarmonicSeries

Child: Child.c
	$(CC) -o Child $(CFLAGS) Child.c

Lucas: Lucas.c
	$(CC) -o Lucas $(CFLAGS) Lucas.c

HexagonalSeries: HexagonalSeries.c
	$(CC) -o HexagonalSeries $(CFLAGS) HexagonalSeries.c

HarmonicSeries: HarmonicSeries.c
	$(CC) -o HarmonicSeries $(CFLAGS) HarmonicSeries.c

Generator: Generator.o
	$(CC) -o Generator $(CFLAGS) Generator.c

clean:
	rm -f *.o Generator Child Lucas HexagonalSeries HarmonicSeries

test:
	./Generator
