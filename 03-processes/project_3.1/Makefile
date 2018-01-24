CC=clang
CFLAGS=-std=c99 -Wall

main: main.o shell.o history.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c shell.h

shell.o: shell.c shell.h history.h

history.o: history.c history.h

test: main
	./main

clean:
	$(RM) main *.o
