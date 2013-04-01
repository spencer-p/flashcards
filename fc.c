//
//  main.c
//  flashcards
//
//  Created by Spencer Peterson on 10/26/12.
//  Copyright (c) 2012 Spencer Peterson. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

void
help(void);

void
printCard(int cardNum, int side);

int
getCards(char *path);

void
study(void);

void
multiplechoice(void);

void
mascfem(void);

void
fillintheblank(void);

void
learn(void);

char *
cardtext(int num, char side);

int
cardsize(char side);

typedef struct card_t
{
    char front[64];
    char back[128];
} card;

#define VERSION "1.4"
//1.1 lettered multiplechoice instead of numbered
//1.2 refined getcards, no residual cards
//1.3 fill in the blank has become usable
//1.4 learn mode is usable. new help command.
#define CARDFRONT 64
#define CARDBACK 128
#define AMTOFCARDS 128

card gCards[128];
char deckTitle[64];
int gNumCards = 0;
char gCommand[32];
int frontback = 0;
//0 is for prompt with front. 1 is for prompt with back

//gCards[0].front = "a";
//strcpy (gCards[0].front, "a");

//free(gCard[i].front);
//free(gCards[0].back);

int
main(void) {
    int commandfound = 0;
    do {
        printf("(v%s)[main] ", VERSION);
        getCommand("What is your command: ", gCommand);
        strlower(gCommand);
        if (strcmp(gCommand, "study") == 0) {
            study();
            commandfound = 1;
        }
        if (strcmp(gCommand, "multiplechoice") == 0) {
            multiplechoice();
            commandfound = 1;
        }
        if (strcmp(gCommand, "getcards") == 0) {
            printf("Path to your .txt file: ");
    		char path[128];
    		scanf("%s", path);
            getCards(path);
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
        if (strcmp(gCommand, "learn") == 0) {
        	learn();
        	commandfound = 1;
        }
        if (strcmp(gCommand, "help") == 0) {
            help();
            commandfound = 1;
        }
        if (strcmp(gCommand, "frontback") == 0){
            if (frontback == 0) {
                printf("Toggling to prompt with back.\n");
                frontback = 1;
            }
            else if (frontback == 1) {
                printf("Toggling to prompt with front.\n");
                frontback = 0;
            }
        }
        else if (commandfound == 0) {
            if (strcmp(gCommand, "quit") != 0) {
                printf("(v%s)[main] Command \"%s\" not found. Try 'help' if you need it.\n", VERSION, gCommand);
            }
        }
        commandfound = 0;
    } while (strcmp(gCommand, "quit") != 0);
}

void
help(void) {
    printf("\nGETCARDS: takes a path to data in a text file and reads it into the program's memory.\n\nSTUDY: prints out data. use n for next and f for flip.\n\nMULTIPLECHOICE: asks multiple choice questions.\n\nFITB: fill in the blank questions.\n\nLEARN: asks you to type in the definition of a word twice each. helps you totally learn definitions.\n\nQUIT: quits. can be used nearly anywhere.\n\n");
}

void
printCard(int cardNum, int side){
	clearscrn();
    if (side == 1){
    	printf("%s, #%d (back)\n\n", deckTitle, cardNum + 1);
        printf("%s", cardtext(cardNum, 'b'));
    }
    if (side == 0){
        printf("%s, #%d (front)\n\n", deckTitle, cardNum + 1);
        printf("%s", cardtext(cardNum, 'f'));
    }
	printf("\n\n");
}

int
getCards(char *path) {
    for (int i = 0; i <= AMTOFCARDS; i++)
        memset(&gCards[i], 0, sizeof(card));
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
                        if (j == cardsize('f') - 1) {
                            printf("Card #%d ran out of front space.\n", i);
                            gCards[i].front[j] = '\0';
                            side = 1;
                        }
                        else {
                            gCards[i].front[j] = c;
                        }
                    }
                    if (1 == side) {
                        if (j == cardsize('b') - 1) {
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
        gCommand[0] = ' ';
        return 1;
    }
    fclose(rawcards);
    gCommand[0] = ' ';
    gNumCards = i;
    printf("[getcards] Loaded set \"%s\"\n", deckTitle);
    return 0;
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
    if(gNumCards < 4) {
        printf("Not enough cards for this.\n");
        return;
    }
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
        num = rand() % gNumCards;
        clearscrn();
        printf("%d.) What does \'%s\' correspond to?\n\n", x + 1, cardtext(num, 'f'));
        key = (rand() % 4) + 97;
        for (i = 'a'; i <= 'd'; i++) {
            if (i == key) {
                printf("(%c) %s\n", (char)i, cardtext(num, 'b'));
            }
            else if (i != key){
                do {
                    random = rand() % gNumCards;
                } while (random == num || random == others[0] || random == others[1] || random == others[2] || random == others[3]);
                others[i-97] = random;
                printf("(%c) %s\n", (char)i, cardtext(random, 'b'));
            }
        }
        printf("\n");
        scanf("%c", &choice);
        choice = tolower(choice);
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
        	printf("Incorrect. The answer was '%s'.\n", cardtext(num, 'b'));
            waitfornewline();
        }
    }
    printf("You got %d out of %d correct.\n\n", score, x);
    waitfornewline();
    clearscrn();
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
        printf("Is \'%s\' masculine or feminine?\n\n", cardtext(num, 'f'));
        if (strcmp(cardtext(num, 'b'), "masc") == 0 ) {
            key = 1;
        }
        if (strcmp(cardtext(num, 'b'), "fem") == 0) {
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
        	printf("Incorrect. %s is %s.\n", cardtext(num, 'f'), cardtext(num, 'b'));
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
    longer[0] = ' ';
    char nopunc[32];
    char end;
    char temp[cardsize('b')];
    int questions;
    printf("How many questions would you like to be asked? ");
    scanf("%d", &questions);
    clearin();
    for (x = 0; x < questions; x++) {
        longer[0] = ' ';
        clearscrn();
        num = rand() % gNumCards;
        strncpy(temp, cardtext(num, 'b'), cardsize('b'));
        result = NULL;
        //puts first string in longest
        result = strtok(cardtext(num, 'b'), " ;,:.?\\/");
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
        strlower(key);
        strncpy(cardtext(num, 'b'), temp, cardsize('b'));
        printf("%d.) Fill in the Blank\n\n%s = ", (x + 1), cardtext(num, 'f'));
        result = strtok(cardtext(num, 'b'), " ");
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
        strncpy(cardtext(num, 'b'), temp, cardsize('b'));
        printf("\n\n");
        scanf("%s", choice);
        strlower(choice);
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
    }
    printf("You got %d out of %d correct.\n\n", score, x);
    waitfornewline();
    clearscrn();
    return;
}

void
learn(void) {
    //i for loops, num is the number of the chosen card, score for questions right
	int num, notlearned = gNumCards, learned[gNumCards];
    for (int i = 0; i < gNumCards; i++) {
        learned[i] = 0;
    }
    
    //key for what the answer is checked against, answer is user input
	char key[cardsize('b')], answer[cardsize('b')];
	srand((unsigned int) time(NULL));
    
    clearin();
    
    for (int i = 0; notlearned != 0; i++) {
        //choose a card and copy it into key
        do {
            num = rand() % gNumCards;
        } while (learned[num] >= 2);
        strncpy(key, cardtext(num, 'b'), cardsize('b'));
        strlower(key);
        
   		clearscrn();
  	    printf("%d of %d learned | this card correct %d times\n", gNumCards-notlearned, gNumCards, learned[num]);
        printf("%d.) What is \'%s?\'\n\n", i + 1, cardtext(num, 'f'));
        
        //read an answer from the user, stopping when it reads a newline
        int x = 0;
        while (1) {
            answer[x] = getc(stdin);
            if (answer[x] == '\n') {
                answer[x] = '\0';
                break;
            }
            x++;
        }
        answer[x] = '\0';
        strlower(answer);
        
        if(strcmp(answer, key) == 0) {
            printf("Correct!\n");
            learned[num]++;
            if (learned[num] == 2) {
                printf("You have learned this card!\n");
                notlearned--;
            }
            waitfornewline();
        } else if (strcmp(answer, "quit") == 0) {
            return;
        } else {
            learned[num] = 0;
            do {
                printf("Not quite. The answer was \'%s.\'\nTry again:\n", key);
                int x = 0;
                while (1) {
                    answer[x] = getc(stdin);
                    if (answer[x] == '\n') {
                        answer[x] = '\0';
                        break;
                    }
                    x++;
                }
                answer[x] = '\0';
                strlower(answer);
                if (strcmp(answer, "quit") == 0) {
                    return;
                }
            } while (strcmp(answer, key) != 0);
            printf("Correct.\n");
            waitfornewline();
        }
    }
	printf("You have learned everything!\n");
	waitfornewline();
	clearscrn();
    return;
}

char *
cardtext(int num, char side) {
    switch(side) {
        case 'f':
            if (frontback == 0) {
                return gCards[num].front;
            }
            if (frontback == 1) {
                return gCards[num].back;
            }
            break;
        case 'b':
            if (frontback == 1) {
                return gCards[num].front;
            }
            if (frontback == 0) {
                return gCards[num].back;
            }
            break;
    }
    return 0;
}

int
cardsize(char side) {
    switch (side) {
        case 'f':
            if (frontback == 0) {
                return CARDFRONT;
            }
            if (frontback == 1) {
                return CARDBACK;
            }
            break;
        case 'b':
            if (frontback == 0) {
                return CARDBACK;
            }
            if (frontback == 1) {
                return CARDFRONT;
            }
            break;
    }
    return 0;
}
