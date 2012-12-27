#include "helpers.h"

/*
 * Returns 0 if value is in array of n values, else 1.
 */

int
binsearch(int value, int values[], int n) {
	sort(values, n);
	if (n == 1 && value == values[0])
		return 0;
	if (n == 1 && value != values[0])
		return 1;
	if (value > values[n/2]) {
		if (binsearch(value, &values[n/2], n/2) == 0)
			return 0;
	}
	else if (value < values[n/2]) {
		if (binsearch(value, values, n/2) == 0)
			return 0;
	}
	else if (value == values[n/2])
		return 0;
	return 1;
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
getCommand(char *dialog, char *string){
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
waitfornewline(void){
    char c = getchar();
    while (c != '\n')
        c=getchar();
}

void
clearscrn(void) {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}