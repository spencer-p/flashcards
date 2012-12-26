#include "helpers.h"

#define waitfornewline clearin


/*
 * Returns true if value is in array of n values, else false.
 */

bool
search(int value, int values[], int n) {
    // TODO: re-implement as binary search
    sort(values, n);
    for (int i = 0; i < n; i++)
    if (n == 1 && values[0] != value){
		return false;
	}
    if (value > values[n/2]) {
    	for (int i = 0; i < n/2 + 1; i++) {
    		values[i] = values[n/2 + i];
    	}
    	if (search(value, values, n/2 + 1))
    		return true;
    	else
    		return false;
    }
    if (value < values[n/2]) {
    	if (search(value, values, n/2))
    		return true;
    	else
    		return false;
    }
    if (values[n/2] == value)
    	return true;
}


/*m
 * Sorts array of n values.
 */

void
sort(int values[], int n){
    //O(n^2) sort (possibly failed miserably)
    int highestVal;
    int temp;
    for (int i = n - 1; i >= 0; i--){
    	highestVal = maxVal(values, i + 1);
    	temp = values[i];
    	values[i] = values[highestVal];
    	values[highestVal] = temp;
    }
    for (int i = 0; i < n; i++) {
    }
    return;
}


int
maxVal(int values[], int n)
{
	int i;
	int arrayVal = 0;
    int highestVal = values[0];
    for (i = 0; i < n; i++)
    {
        if (values[i] > highestVal){
            highestVal = values[i];
            arrayVal = i;
            }
    }
    return arrayVal;
}

int
minVal(int values[], int n)
{
	int i;
	int arrayVal = 0;
    int lowestVal = values[0];
    for (i = 1; i < n; i++)
    {
        if (values[i] < lowestVal){
            lowestVal = values[i];
            arrayVal = i;
            }
    }
    return arrayVal;
}

void
getCommand(const char *dialog, char *string){
	printf("%s", dialog);
    scanf("%s", string);
	return;
}

void
clearin(void){
    char c = getchar();
    while (c != '\n')
        c=getchar();
}

void
clearscrn(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}
