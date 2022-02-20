CC = gcc
CFLAGS=-Wall -lrt

build: Starter Reader Lucas HexagonalSeries HarmonicSeries

Lucas: Lucas.c
	$(CC) -o Lucas $(CFLAGS) Lucas.c

HexagonalSeries: HexagonalSeries.c
	$(CC) -o HexagonalSeries $(CFLAGS) HexagonalSeries.c

HarmonicSeries: HarmonicSeries.c
	$(CC) -o HarmonicSeries $(CFLAGS) HarmonicSeries.c

Reader: Reader.c
	$(CC) -o Reader $(CFLAGS) Reader.c

Starter: Starter.c
	$(CC) -o Starter $(CFLAGS) Starter.c 

clean:
	rm -f *.o Starter Reader Lucas HexagonalSeries HarmonicSeries

test:
	./Starter

package:
	tar -czvf Nikolas-Torraca-HW3.tar .
