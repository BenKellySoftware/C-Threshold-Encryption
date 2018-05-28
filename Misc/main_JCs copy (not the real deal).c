
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
	int error = 0; /*boolean for error. if 0, all good. if 1, we have problems*/
	
	/*******************************DECOMPRESSION******************************/
	error = decompress_file(new_huffman_codes(), filename);
	if (error == 1)
	{
		/*TODO: debug message here*/
		return 1;
	}

	/*******************************OPEN FILE**********************************/
	long* filesize_encrypt = (long*)malloc(1 * sizeof(long));
	FILE* file_encrypt;
	file_encrypt = fopen(filename, "r");
	char* data_encrypt = (char*)malloc(1 * sizeof(char));

	if (file_encrypt != NULL)
	{
		/*write to file*/
		fseek(file_encrypt, 0, SEEK_END);
		*filesize_encrypt = ftell(file_encrypt);
		rewind(file_encrypt);
		
		data_encrypt = (char*)realloc((*filesize_encrypt) * sizeof(char));
		char * file_encrypt_tempbuffer = (char*)malloc(sizeof(char)*(*filesize)); /*allocate memory to contain the file*/

		long fread_result = fread(file_encrypt_tempbuffer, 1, *filesize, file); /*store WHOLE FILE in file_buffer*/
		if (fread_result != *filesize) { /*if buffer is, for whatever reason, a different size to what we anticipated*/
			/*TODO: debug message here*/
			return 1;
		}
		else {
			/*write the data (up until this point, we keep data separate from parameters for secutrity purposes)*/
			*data_encrypt = *file_encrypt_tempbuffer;
		}/*if|fread_result*/
		free(file_encrypt_tempbuffer);
	}
	else
	{
		/*TODO: debug message here*/
		return 1;
	}
	if (fclose(file_encrypt) == 1)
	{
		/*TODO: debug message here*/
		return 1;
	}

	/*********************************DECRYPTION*******************************/
	char* data_clean = (char*)malloc(filesize_encrypt * sizeof(char));
	char* key_master = (char*)malloc(MASTER_KEY_LEN * sizeof(char));

	polynomial_t polynom = find_polynomial(a, b, c);
	/*TODO: put a function in crypto that converts the polynomial into a string*/

	error = decrypt_file(data_encrypt, key_master, filesize_encrypt, data_clean);
	if (error == 1)
	{
		/*TODO: debug message here*/
		return 1;
	}
	
	/*********************************SAVE FILE********************************/
	FILE* file_clean; /*file stream*/
	file = fopen(filename, "w");
	long fread_result = fwrite(data, 1, filesize_encrypt, file_clean);
	if (fread_result != filesize_encrypt)
	{
		/*TODO: debug message here*/
		return 1;
	}
	if (fclose(file) == 1) {
		/*TODO: debug message here*/
		return 1;
	}


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
	int error = 0; /*boolean for error. if 0, all good. if 1, we have problems*/
	
	/*********************************OPEN FILE********************************/
	FILE* file_clean; /*file stream*/
	char* data_clean = (char*)malloc(1 * sizeof(char));
	long* filesize_clean = (long*)malloc(1 * sizeof(long));
	file_clean = fopen(filename, "r");
	if (file_clean != NULL) {
		/*read file*/
		fseek(file_clean, 0, SEEK_END); /*go to end*/
		*filesize_clean = ftell(file_clean); /*find location value at end*/
		rewind(file_clean); /*go back to beginning*/

		char * file_clean_tempbuffer = (char*)malloc(sizeof(char)*(*filesize_clean)); /*allocate memory to contain the file*/
		data_clean = realloc((*filesize_clean) * sizeof(char));

		long fread_result = fread(file_clean_tempbuffer, 1, *filesize_clean, file); /*store WHOLE FILE in file_buffer*/
		if (fread_result != *filesize_clean) { /*if buffer is, for whatever reason, a different size to what we anticipated*/
			/*TODO: debug message here*/
			return 1;
		}
		else {
			/*write the data (up until this point, we keep data separate from parameters for secutrity purposes)*/
			*data = *file_clean_tempbuffer;
		}/*if|fread_result*/
		free(file_clean_tempbuffer);

	}
	else {
		/*TODO: debug message here*/
		return 1;
	}/*if|file!=NULL*/

	if (fclose(file) == 1) {
		/*TODO: debug message here*/
		return 1;
	}

	/********************************ENCRYPTION********************************/
	char* data_encrypt = (char*)malloc(1 * sizeof(char));
	char* key_master = (char*)malloc(MASTER_KEY_LEN * sizeof(char));
	error = encrypt_file(data_clean, key_master, filesize_clean, data_encrypt);
	if (error == 1) {
		/*TODO: debug message here*/
		return 1;
	}
	/*TODO: put a function in crypto that converts char key into polynomial*/


	/********************************COMPRESSION*******************************/
	

	/*********************************SAVE FILE********************************/
	

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
	char* file_dir;
	point_t point_keys[3];

	colour_printf("blue", "Welcome to the Bepis Gola Database\n");
	if (argc <= 1) /* no arguement entered- therefore use scanf */
	{
		do
		{		
			printf("\n"
			"1. add a recipe\n"
			"2. view the recipe\n"
			"Please enter a number that correlates with your choice>\n");
			scanf("%d", &choice);
			
			if (choice == 1)
			{
				printf("Please enter the recipe file directory>\n");
				scanf("%s", file_dir);
			}
			else if(choice == 2)
			{
				printf("Please enter the recipe file directory>\n");
				scanf("%s", file_dir);
				

				printf("KEY 1: Please enter two key numbers, spearated by a comma>");
				scanf("%i, %i", &point_keys[0].x, &point_keys[0].y);
				printf("KEY 2: Please enter two key numbers, separated by a comma>");
				scanf("%i, %i", &point_keys[1].x, &point_keys[1].y);
				printf("KEY 3: Please enter two key numbers, separated by a comma>");
				scanf("%i, %i", &point_keys[2].x, &point_keys[2].y);
				/*TODO: look into how you make the input unreadable, like when
				you type in passwords in bash. this would be good for these keys*/

			}
			/*all other entries are handled by validPrintMenu*/
		} 
		while(!validPrintMenu(choice));
	}
	else /* arguements already entered */
	{
		if (strcmp(argv[1], "-h") == 0)
		{
			/*print help menu*/
			printf("");/*TODO: help menu*/
		}
		if (strcmp(argv[1], "-a") == 0)
		{
			/* check if argc == 4, ie they entered ./main.out -a target_file */
			if (argc == 4)
			{
				file_dir = argv[2];
			}
			else
			{
				/* if they havent entered files, ask them to enter the target and dest file */
				printf("Please enter the recipe file directory>\n");
				scanf("%s", file_dir);
			}
			choice = 1;
		}
		else if (strcmp(argv[1], "-v") == 0)
		{
			/* check if argc == 4, ie they entered ./main.out -v target_file key1 key2 key3 */
			if (argc == 4)
			{
				file_dir = argv[2];
				point_keys[0] = argv[3];
				point_keys[1] = argv[4];
				point_keys[2] = argv[5];
			}
			else
			{
				/* if they havent entered files, ask them to enter the target file and points */
				printf("Please enter the recipe file directory>\n");
				scanf("%s", file_dir);
				printf("KEY 1: Please enter two key numbers, spearated by a comma>");
				scanf("%i, %i", &point_keys[0].x, &point_keys[0].y);
				printf("KEY 2: Please enter two key numbers, separated by a comma>");
				scanf("%i, %i", &point_keys[1].x, &point_keys[1].y);
				printf("KEY 3: Please enter two key numbers, separated by a comma>");
				scanf("%i, %i", &point_keys[2].x, &point_keys[2].y);
			}
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
		add_recipe(file_dir);
	}
	if (choice == 2)
	{
		retrieve_recipe(file_dir, point_keys[0], point_keys[1], point_keys[2]);
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