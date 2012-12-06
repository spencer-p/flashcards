fc: fc.c help.c help.h
	cc -o fc.out fc.c help.c
clean:
	rm *.out fc