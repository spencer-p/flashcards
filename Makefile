fc: fc.c help.c help.h
	cc -o fc fc.c help.c -std=c99
clean:
	rm *.out fc
