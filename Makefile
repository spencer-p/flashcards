fc: fc.c help.c help.h
	cc -o fc fc.c helpers.c -std=c99
clean:
	rm *.out fc
