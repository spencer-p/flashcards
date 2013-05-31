fc: fc.c helpers.c helpers.h
	cc -o fc fc.c helpers.c -std=c99
install: fc.c helpers.c helpers.h
	sudo cc fc.c helpers.c -o /usr/local/bin/flashcards -std=c99
clean:
	rm *.out fc
