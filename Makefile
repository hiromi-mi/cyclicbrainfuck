cyclicbrainfuck:	cyclicbrainfuck.c
	gcc -Wall -Wextra cyclicbrainfuck.c -o cyclicbrainfuck

clean:
	$(RM) -f cyclicbrainfuck
.PHONY:	clean
