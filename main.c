#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#include "crypto.h"
#include "compression.h"

/*******************************************************************************
 * Asks for three keys, and runs the steps to decrypt and decompress
 * a given file.
 *
 * Author: 
 * - Leah
 *
 * Inputs:
 * - filename : The file to be decrypted
 * - a        : The first point to be used to decrypt
 * - b        : The second point to be used to decrypt
 * - c        : The third point to be used to decrypt
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 *
*******************************************************************************/
int retrieve_recipe(char *filename, point_t a, point_t b, point_t c);


/*******************************************************************************
 * Runs through the steps to compress and encrypt a recipe
 *
 * Author: 
 * - Leah
 *
 * Inputs:
 * - filename : the file to be compressed and encrypted
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 *
*******************************************************************************/
int add_recipe(char *filename);


/*******************************************************************************
 * Main
 * Runs the interface
 * Author: 
 * - Rachel
 *
 * There are two different modes (-a and -v).
 * Mode -a is to add a recipe.
 * Mode -v is to view the recipe.
*******************************************************************************/
int main(int argc, char* argv[])
{
	int result;						/* result = 1 means that it hasn't worked */

	colour_printf("blue", "Welcome to the Bepis Gola Database\n");

	do
	{
		if (argc <= 1)
		{
			printf("Please specific either mode '-a' to add a recipe");
			printf("or mode '-v' to view the recipe.\n");
			result = 1;					  
		}

		if (strcmp(argv[1], "-a") == 0)
		{
			printf("You have chosen to add a recipe.\n");
			add_recipe(*filename);
			result = 0;
		}
		else if (strcmp(argv[1], "-v") == 0)
		{
			printf("You have chosen to view the recipe.\n");
			retrieve_recipe(*filename, a, b, c);
			result = 0;
		}
		else 
		{
			printf("There is no mode for the input you have entered.\n");
			result = 1;
		}
	} while (result == 1);
	
	return 0;
}