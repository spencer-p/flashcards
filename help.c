#include <stdio.h>

void
getCommand(char *command){
	printf("What is your command: ");
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
