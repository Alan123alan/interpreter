CC=cc
CFLAGS=-Wextra -Wall -g -pedantic

main:
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f main
	rm -rf main.dSYM


test:
	$(CC) $(CFLAGS) ./lexer/lexer_test.c ./lexer/lexer.c -o test

clean_test:
	rm -f test
	rm -rf test.dSYM
