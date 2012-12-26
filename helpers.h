/****************************************************************************
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 ***************************************************************************/
 
#include <stdio.h>


/*
 * Returns true if value is in array of n values, else false.
 */

bool 
search(int value, int values[], int n);


/*
 * Sorts array of n values.
 */

void 
sort(int values[], int n);

//finds the highest value in an array of ints
int
maxVal(int values[], int n);

//finds the lowest value in an array of ints
int
minVal(int values[], int n);

//prints a dialog and gets input
void
getCommand(char *dialog, char *string);

//loops over stdin until it finds a \n
void
clearin(void);

//same as above
void
waitfornewline(void);

//clears screen
void
clearscrn(void);