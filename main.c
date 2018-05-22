
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef CRYPTO_H
#include "crypto.h"
#define CRYPTO_H
#endif

#ifndef COMPRESSION_H
#include "compression.h"
#define COMPRESSION_H
#endif

#ifndef COLOUR_H
#include "colour.h"
#define COLOUR_H
#endif


/* prototypes */
int retrieve_recipe(char *filename, point_t a, point_t b, point_t c);
int add_recipe(char *filename);
int validPrintMenu(int choice);


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
int retrieve_recipe(char *filename, point_t a, point_t b, point_t c)
{
    return 0;
}


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
int add_recipe(char *filename)
{
    return 0;
}


/*******************************************************************************
 * Main
 * Runs the interface
 *
 * Author: 
 * - Rachel
 *
 * Inputs: 
 * - argc: arguement count
 * - argv: arguement value
 *
 * Outputs: 
 * - none
 *
 * There are two different modes that can be selected (-a and -v).
 * Mode -a is to add a recipe.
 * Mode -v is to view the recipe.
*******************************************************************************/
int main(int argc, char* argv[])
{
	int choice;		  

	colour_printf("blue", "Welcome to the Bepis Gola Database\n");
	if (argc <= 1) /* no arguement entered- therefore use scanf */
	{
		do
		{		
			printf("\n"
			"1. add a recipe\n"
			"2. view the recipe\n"
			"Please enter a number that correlates with your choice above>\n");
			scanf("%d", &choice);
		} 
		while(validPrintMenu(choice));
	}
	else /* arguements already entered */
	{
		if (strcmp(argv[1], "-a") == 0)
		{
			choice = 1;
		}
		else if (strcmp(argv[1], "-v") == 0)
		{
			choice = 2;
		}
		else 
		{
			printf("There is no mode for the arguement you have entered.\n");
			return 1;
		}
	}

	if (choice == 1)
	{
		printf("You have chosen to add a recipe.\n");
		add_recipe(*filename);
	}
	if (choice == 2)
	{
		printf("You have chosen to view the recipe.\n");
		retrieve_recipe(*filename, a, b, c);
	}
	return 0;
}

/*******************************************************************************
 * This function checks for valid choice choice from user. 
 *  
 * Author: 
 * - Rachel
 *
 * Inputs:
 * - The users choice
 *
 * Outputs:
 * - 1 for valid
 * - 0 for invalid
*******************************************************************************/
int validPrintMenu(int choice)
{
    if (choice < 1 || choice > 2)
    {
        printf("Invalid choice\n");
        return 0;
    } 
    return 1;
}