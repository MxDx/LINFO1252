CC=gcc
CFLAGS= -Wall -Werror -g 
LIBS=-lcunit -lpthread -lm
INCLUDE_HEADERS_DIRECTORY=-Iheaders
SRC=src/stack.c

main:
	@$(CC) -c $(SRC) $(CFLAGS)
	@echo "\n Successfully compiled all source files. \n" 
	
	@$(CC) src/philosophe.c -o philosophe $(CFLAGS)

clean:
	rm -f *.o
	rm philosophe