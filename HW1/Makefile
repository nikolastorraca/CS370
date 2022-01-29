
Starter: Executor.o Starter.o
	gcc -Wall -Werror -o Starter Executor.o Starter.o

%.o: %.c
	gcc -c -Wall -Werror -o $@ $<

clean:
	rm -f *.o Starter
