
#ifndef STDIO_H
#define STDIO_H value
#include <stdio.h>
#endif

#ifndef STRING_H
#define STRING_H value
#include <string.h>
#endif

/* ansi codes for terminal colour */
#define COLOUR_DEFAULT "\x1B[0m"
#define COLOUR_RED     "\x1B[31m"
#define COLOUR_GREEN   "\x1B[32m"
#define COLOUR_YELLOW  "\x1B[33m"
#define COLOUR_BLUE    "\x1B[34m"
#define COLOUR_MAGENTA "\x1B[35m"
#define COLOUR_CYAN    "\x1B[36m"
#define COLOUR_WHITE   "\x1B[37m"


/*******************************************************************************
 * Prints text in a colour
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - colour  : Colour to print things in
 * - message : Text to print in the colour
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void colour_printf(const char *colour, const char* message)
{
	/* Set the colour to what was asked */
	if (strcmp(colour, "red") == 0)
		printf(COLOUR_RED);
	else if (strcmp(colour, "green") == 0)
		printf(COLOUR_GREEN);
	else if (strcmp(colour, "yellow") == 0)
		printf(COLOUR_YELLOW);
	else if (strcmp(colour, "blue") == 0)
		printf(COLOUR_BLUE);
	else if (strcmp(colour, "magenta") == 0)
		printf(COLOUR_MAGENTA);
	else if (strcmp(colour, "cyan") == 0)
		printf(COLOUR_CYAN);
	else if (strcmp(colour, "white") == 0)
		printf(COLOUR_WHITE);
	else
		printf(COLOUR_DEFAULT);

	/* Print the message */
	printf("%s", message);

	/* Set colour to hatever the default terminal colour is */
	printf(COLOUR_DEFAULT);	
}