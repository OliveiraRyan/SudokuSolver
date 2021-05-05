CC=gcc
GCC_OPT = -O2 -Wall -Werror

%.o: %.c
	$(CC) -c -o $@ $< $(GCC_OPT)

cSolver: cSolver.o
	$(CC) $(GCC_OPT) $< -o $@

clean:
	rm *.o