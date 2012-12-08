#include <stdio.h>

void
getCommand(const char *dialog, char *string){
	printf("%s", dialog);
    scanf("%s", string);
	return;
}

void
clearin(void){
	char c;
	do {
	    c = getchar();
	} while (c != '\n');
	return;
}

void
waitfornewline(void){
    char c=getchar();
    while (c != '\n')
        c=getchar();
}

void
clearscrn(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}