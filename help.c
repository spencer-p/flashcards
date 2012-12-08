#include <stdio.h>

void
getCommand(const char *dialog, char *command){
	printf("%s", dialog);
    scanf("%s", command);
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
