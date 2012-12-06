fc: fc.c help.c help.h
	cc -o fc fc.c help.c
clean:
	rm *.out fc
