all: 1cyclicbrainfuck cyclicbrainfuck

1cyclicbrainfuck:	1cyclicbrainfuck.c
	gcc -Wall -Wextra 1cyclicbrainfuck.c -o 1cyclicbrainfuck
cyclicbrainfuck:	cyclicbrainfuck.c
	gcc -g -Wall -Wextra cyclicbrainfuck.c -o cyclicbrainfuck

clean:
	$(RM) -f 1cyclicbrainfuck cyclicbrainfuck
.PHONY:	clean all
