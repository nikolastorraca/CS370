CC = gcc
CFLAGS=-Wall

build: scheduler

scheduler: scheduler.c
	$(CC) -o scheduler $(CFLAGS) scheduler.c

clean:
	rm -f *.o scheduler

package:
	tar -czvf Nikolas-Torraca-HW4.tar .