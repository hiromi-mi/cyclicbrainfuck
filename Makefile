all: cyclicbrainfuck 2cyclicbrainfuck

cyclicbrainfuck:	cyclicbrainfuck.c
	gcc -Wall -Wextra cyclicbrainfuck.c -o cyclicbrainfuck
2cyclicbrainfuck:	2cyclicbrainfuck.c
	gcc -Wall -Wextra 2cyclicbrainfuck.c -o 2cyclicbrainfuck

clean:
	$(RM) -f cyclicbrainfuck 2cyclicbrainfuck
.PHONY:	clean all
