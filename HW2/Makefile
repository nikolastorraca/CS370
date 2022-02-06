CC = gcc
CFLAGS=-Wall

#build: Generator Child
#Lucas HexagonialSeries HarmonicSeries

build: Generator Lucas HexagonalSeries HarmonicSeries

Lucas: Lucas.c
	$(CC) -o Lucas $(CFLAGS) Lucas.c

HexagonalSeries: HexagonalSeries.c
	$(CC) -o HexagonalSeries $(CFLAGS) HexagonalSeries.c

HarmonicSeries: HarmonicSeries.c
	$(CC) -o HarmonicSeries $(CFLAGS) HarmonicSeries.c

Generator: Generator.o
	$(CC) -o Generator $(CFLAGS) Generator.c

clean:
	rm -f *.o Generator Lucas HexagonalSeries HarmonicSeries

test:
	./Generator

package:
	tar -czvf Nikolas-Torraca-HW2.tar .
