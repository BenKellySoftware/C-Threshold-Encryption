
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif


typedef struct bit_buffer {
	int seek;
	int bit[8];
} bit_buffer_t;


/*******************************************************************************
 * Creates a new buffer from a character
 * 
 * Author:
 * - Tom
 *
 * Inputs:
 * - c : The character to make into a buffer
 *
 * Outputs:
 * - A new buffer of the bits that represent the character
 *
*******************************************************************************/
bit_buffer_t char_to_buffer(char c)
{
	bit_buffer_t b;

	/* seek is used for knowing what bit we are up to checking */
	b.seek = 0;

	int i;
	for (i = 0; i < 8; i++)
	{
		b.bit[7-i] = (c >> i) & 1;
	}

	return b;
}


/*******************************************************************************
 * Displays a buffer in its entirety
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - b : The buffer to display
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void display_buffer(bit_buffer_t b)
{
	printf("Seek: %d | Bits: ", b.seek);

	int i;
	for (i = 0; i < 8; i++)
	{
		printf("%d", b.bit[i]);
	}

	printf("\n");
}


/*******************************************************************************
 * Compresses a file such that it takes up less space on disc
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - filename : The file to compress
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int compress_file(char *filename)
{
	return 0;
}


/*******************************************************************************
 * Decompresses a file
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - filename : The file to decompress
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int decompress_file(char *filename)
{
	return 0;
}