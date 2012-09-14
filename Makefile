CC = gcc
FLAGS = -ansi -Wall -pedantic
GOODFLAGS = -O3

rpn_calc: rpn_calc.c
	$(CC) $(GOODFLAGS) rpn_calc.c -g -o rpn_calc

all: clean rpn_calc

backup: clean zip

clean:
	rm -f rpn_calc *.o

zip:
	@-tar -czf rpn_calc.tgz Makefile *.c
	
.PHONY: clean zip
