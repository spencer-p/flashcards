//
//  main.c
//  flashcards
//
//  Created by Spencer Peterson on 10/26/12.
//  Copyright (c) 2012 Spencer Peterson. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void
printCard(int cardNum, int side);

void
getCommand(void);

int
getCards(void);

void
clearin(void);

void
waitfornewline(void);

void
study(void);

void
multiplechoice(void);

void
clearscrn(void);

void
mascfem(void);

void
fillintheblank(void);

typedef struct card_t
{
    char front[64];
    char back[128];
} card;

#define VERSION "1.3"
//1.1 lettered multiplechoice instead of numbered
//1.2 refined getcards, no residual cards
//1.3 fill in the blank has become usable
#define CARDFRONT 64
#define CARDBACK 128
#define AMTOFCARDS 128

card gCards[128];
char deckTitle[64];
int gNumCards = 0;
char gCommand[32];

//gCards[0].front = "a";
//strcpy (gCards[0].front, "a");

//free(gCard[i].front);
//free(gCards[0].back);

int
main(void) {
    int commandfound = 0;
    do {
        printf("(v%s)[main] ", VERSION);
        getCommand();
        if (strcmp(gCommand, "study") == 0) {
            study();
            commandfound = 1;
        }
        if (strcmp(gCommand, "multiplechoice") == 0) {
            multiplechoice();
            commandfound = 1;
        }
        if (strcmp(gCommand, "getcards") == 0) {
            getCards();
            commandfound = 1;
        }
        if (strcmp(gCommand, "mascfem") == 0) {
            mascfem();
            commandfound = 1;
        }
        if (strcmp(gCommand, "fitb") == 0) {
            fillintheblank();
            commandfound = 1;
        }
        else if (commandfound == 0) {
            if (strcmp(gCommand, "quit") != 0) {
                printf("(v%s)[main] Command \"%s\" not found.\n", VERSION, gCommand);
            }
        }
        commandfound = 0;
    } while (strcmp(gCommand, "quit") != 0);
}

void
printCard(int cardNum, int side){
	clearscrn();
    if (side == 1){
    	printf("%s, #%d (back)\n\n", deckTitle, cardNum + 1);
        printf("%s", gCards[cardNum].back);
    }
    if (side == 0){
        printf("%s, #%d (front)\n\n", deckTitle, cardNum + 1);
        printf("%s", gCards[cardNum].front);
    }
	printf("\n\n");
}

void
getCommand(void){
	printf("What is your command: ");
    scanf("%s", gCommand);
	return;
}

int
getCards(void) {
    for (int i = 0; i <= AMTOFCARDS; i++)
        memset(&gCards[i], 0, sizeof(card));
    printf("Path to your .txt file: ");
    char path[128];
    scanf("%s", path);
    FILE *rawcards = fopen(path, "r");
    int i;
    if(rawcards != NULL){
        i = 0;
        char c;
        while((c = getc(rawcards)) != '\n'){
            deckTitle[i++] = c;
        }
        deckTitle[i] = '\0';
        int side = 0;
        int j = 0;
        i = 0;
        while((c = getc(rawcards)) != EOF){
            switch (c)
            {
                case ':' : {
                    side = 1;
                    gCards[i].front[j] = '\0';
                    j = 0;
                }
                    break;
                case '\n' : {
                    side = 0;
                    i++;
                    gCards[i].back[j] = '\0';
                    j = 0;
                }
                    break;
                default: {
                    if (0 == side) {
                        if (j == CARDFRONT - 1) {
                            printf("Card #%d ran out of front space.\n", i);
                            gCards[i].front[j] = '\0';
                            side = 1;
                        }
                        else {
                            gCards[i].front[j] = c;
                        }
                    }
                    if (1 == side) {
                        if (j == CARDBACK - 1) {
                            printf("Card #%d ran out of back space.\n", i);
                            gCards[i].back[j] = '\0';
                            side = 0;
                        }
                        else {
                            gCards[i].back[j] = c;
                        }
                    }
                    j++;
                }
            }
        }
    }
    else {
        printf("Could not find file \'%s.\'\n", path);
    }
    fclose(rawcards);
    gCommand[0] = ' ';
    gNumCards = i + 1;
    return 0;
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
study(void) {
    srand((unsigned int) time(NULL));
    int num;
    char cmd;
    do {
        num = rand() % gNumCards;
        printCard(num, 0);
        scanf("%c", &cmd);
        clearin();
        if (cmd == 'f') {
            printCard(num, 1);
            scanf("%c", &cmd);
            clearin();
        }
    } while (cmd != 'q');
    clearscrn();
}

void
multiplechoice(void){
    srand((unsigned int) time(NULL));
    clearin();
    int num;
    int others[4];
    int key;
    int random;
    int i;
    int score = 0;
    char choice;
    int x;
    int questions;
    printf("How many questions would you like to be asked? ");
    scanf("%d", &questions);
    clearin();
    for (x = 0; x < questions; x++){
        others[0] = 0;
        others[1] = 0;
        others[2] = 0;
        others[3] = 0;
        num = x; //rand() % gNumCards;
        clearscrn();
        printf("%d.) What does \'%s\' correspond to?\n\n", x + 1, gCards[num].front);
        key = (rand() % 4) + 97;
        for (i = 'a'; i < 'e'; i++) {
            if (i == key) {
                printf("(%c) %s\n", (char)i, gCards[num].back);
            }
            else if (i != key){
                do {
                    random = rand() % gNumCards;
                } while (strcmp(gCards[random].back, gCards[num].back) == 0 || strcmp(gCards[random].back, gCards[others[0]].back) == 0 || strcmp(gCards[random].back, gCards[others[1]].back) == 0 || strcmp(gCards[random].back, gCards[others[2]].back) == 0 || strcmp(gCards[random].back, gCards[others[3]].back) == 0);
                others[i] = random;
                printf("(%c) %s\n", (char)i, gCards[random].back);
            }
        }
        printf("\n");
        scanf("%c", &choice);
        clearin();
        if (choice == 'q') {
            printf("You got %d out of %d correct.\n", score, x);
            waitfornewline();
            clearscrn();
            return;
        }
        if (choice == key) {
            score++;
            printf("Correct!\n");
            waitfornewline();
        }
        else if (choice != key){
        	printf("Incorrect. The answer was '%s'.\n", gCards[num].back);
            waitfornewline();
        }
    }
    printf("You got %d out of %d correct.\n\n", score, x);
    waitfornewline();
    clearscrn();
}

void
clearscrn(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void
mascfem(void) {
    srand((unsigned int) time(NULL));
    clearin();
    int x;
    int others[2];
    int key;
    char choice;
    int num;
    int score = 0;
    for(x = 0; x < 10; x++) {
        others[0] = 0;
        others[1] = 0;
        num = rand() % gNumCards;
        clearscrn();
        printf("Is \'%s\' masculine or feminine?\n\n", gCards[num].front);
        if (strcmp(gCards[num].back, "masc") == 0 ) {
            key = 1;
        }
        if (strcmp(gCards[num].back, "fem") == 0) {
            key = 2;
        }
        printf("1.) masculine\n2.) feminine\n\n");
        scanf("%c", &choice);
        clearin();
        if (choice == 'q') {
            printf("You got %d out of %d correct.\n", score, x);
            waitfornewline();
            clearscrn();
            return;
        }
        if (atoi(&choice) == key) {
            score++;
            printf("Correct!\n");
            waitfornewline();
        }
        else if (atoi(&choice) != key){
        	printf("Incorrect. %s is %s.\n", gCards[num].front, gCards[num].back);
            waitfornewline();
        }
    }
    printf("You got %d out of %d correct.\n\n", score, x);
    waitfornewline();
    clearscrn();
}

void
fillintheblank(void) {
    srand((unsigned int) time(NULL));
    int score = 0;
    int x;
    char key[32];
    char choice[32];
    int num;
    char *result;
    long length;
    long length2;
    char longest[32];
    char longer[32];
    char nopunc[32];
    char end;
    char temp[CARDBACK];
    int questions;
    printf("How many questions would you like to be asked? ");
    scanf("%d", &questions);
    clearin();
    for (x = 0; x < questions; x++) {
        clearscrn();
        num = rand() % gNumCards;
        strncpy(temp, gCards[num].back, CARDBACK);
        result = NULL;
        //puts first string in longest
        result = strtok(gCards[num].back, " ;,:.?\\/");
        length = strlen(result);
        length2 = 0;
        strncpy(longest, result, 32);
        while (result != NULL) {
            if (strlen(result) > length2 && strlen(result) < length) {
                length2 = strlen(result);
                strncpy(longer, result, 32);
            }
            if (strlen(result) > length) {
                length = strlen(result);
                strncpy(longer, longest, 32);
                strncpy(longest, result, 32);
            }
            if (strlen(result) == length && strcmp(result, longest) != 0) {
                length2 = strlen(result);
                strncpy(longer, result, 32);
            }
            result = strtok(NULL, " ;,:.?\\/");
        }
        if (longer[0] == ' ') {
            strncpy(longer, longest, 32);
        }
        int prob = rand() % 2;
        if (0 == prob) {
            strncpy(key, longest, 32);
        }
        else if (1 == prob){
            strncpy(key, longer, 32);
        }
        strncpy(gCards[num].back, temp, CARDBACK);
        printf("%d.) Fill in the Blank\n\n%s = ", (x + 1), gCards[num].front);
        result = strtok(gCards[num].back, " ");
        while (result != NULL) {
            strncpy(nopunc, result, 32);
            end = nopunc[strlen(nopunc) - 1];
            switch (end) {
                case ',':
                    nopunc[strlen(nopunc) - 1] = '\0';
                    break;
                case ':':
                    nopunc[strlen(nopunc) - 1] = '\0';
                    break;
                case ';':
                    nopunc[strlen(nopunc) - 1] = '\0';
                    break;
                case '.':
                    nopunc[strlen(nopunc) - 1] = '\0';
                    break;
                case '?':
                    nopunc[strlen(nopunc) - 1] = '\0';
                case '\\':
                    nopunc[strlen(nopunc) - 1] = '\0';
                case '/':
                    nopunc[strlen(nopunc) - 1] = '\0';
                default:
                    end = '\0';
                    break;
            }
            if (strcmp(key, nopunc) == 0) {
                printf("_____%c ", end);
            }
            else if (strcmp(key, nopunc) != 0) {
                printf("%s ", result);
            }
            result = strtok(NULL, " ");
        }
        strncpy(gCards[num].back, temp, CARDBACK);
        printf("\n\n");
        scanf("%s", choice);
        if (strcmp(choice, key) == 0) {
            printf("Correct!\n");
            score++;
            clearin();
            waitfornewline();
        }
        else if (strcmp(choice, "quit") == 0) {
            break;
        }
        else {
            printf("Incorrect. The answer was \'%s.\' Type it again for practice:\n", key);
            clearin();
            scanf("%s", choice);
        }
        longer[0] = ' ';
    }
    printf("You got %d out of %d correct.\n\n", score, x);
    waitfornewline();
    clearscrn();
    return;
}
