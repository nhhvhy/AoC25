/* ParseRotations.c
 * Author -- nhhvhy
 * Date   -- 12-6-2025
 *
 * Params:
 * 	arg[1] -- path to input 'rotations' file
*/

/* Part 1, Day 1  --  Advent of Code 2025
 * Parses an input 'rotations' file and prints the extracted password
 *
 * Rotation files consist of lines with a direction (L || R) followed by an integer (0..99)
 * Assuming a starting 'dial position' of 50, each line moves the dial (L)eft or (R)ight N times,
 * where N is the integer described after the direction. The dial ranges from 0..99, and will 
 * over/underflow when either bound is reached. The password is determined to be the number of times
 * within the sequence at which the dial position is 0.
*/

/* e.g.
 *
 * rule   dial pos   password
 *        50	     0
 * L10    40	     0	
 * R50    90	     0
 * R10    0  	     1
 * L20	  80	     1
 * L101   79 	     1
 * L79	  0	     2
*/

#include <stdio.h>

// struct to represent individual dial turns
struct dialTurn
{	
	// L || R
	char direction;

	// how many steps the dial is turned
	int distance;
};

// parses a given line and returns its value as a dialTurn
struct dialTurn parseTurnStr(char *str)
{
	struct dialTurn t;
	sscanf(str, "%c%d", &t.direction, &t.distance);
	return t;
};

// 'executes' a dialTurn and returns the updated dialPosition
int setDialPosition(struct dialTurn t, int dialPosition) 
{
	if (t.direction == 'L') {
		dialPosition = dialPosition - t.distance;	
	}

	if (t.direction == 'R') {
		dialPosition = dialPosition + t.distance;	
	}

	if (dialPosition < 0) {
		dialPosition = 100 - (dialPosition * -1);	
	}
	
	return (dialPosition % 100);
}

int main(int argc, char* argv []) 
{
	FILE *fptr;
	int bufSize = 10;	// may be problematic if dial turns exceed 10chars  
	char fBuf[bufSize];
	fptr = fopen(argv[1], "r");
	
	int dialPosition = 50;
	int passwordCount = 0;

	while(1) {
		if( !fgets(fBuf, bufSize, fptr)) { 
			fclose(fptr);
			printf("\nThe password is: %d\n\n", passwordCount);
			return 0;
		}
	
		struct dialTurn t = parseTurnStr(fBuf);
		dialPosition = setDialPosition(t, dialPosition);

		if (dialPosition == 0) {
			passwordCount = passwordCount + 1;
		}
	}	
}
