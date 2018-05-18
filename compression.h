
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef HUFFMAN_H
#include "huffman.h"
#define HUFFMAN_H
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
 * Gets a char from a buffer
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - b : The bit buffer
 *
 * Outputs:
 * - A character that represents the bits
 *
*******************************************************************************/
int buffer_to_char(bit_buffer_t b)
{
	char val;

	int i;
	for (i = 0; i < 8; i++)
	{
		val += b.bit[i] << (7-i);
	}

	return val;
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
 * Gets the next bit in a bit buffer. If we have run out of bits, returns -1.
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - b : Bit buffer to read from
 *
 * Outputs:
 * - 0 or 1 depending on the bit. If out of bits, returns -1
 *
*******************************************************************************/
int get_next_bit(bit_buffer_t *b)
{
	if (b->seek == 8)
	{
		return -1;
	}

	return b->bit[b->seek++];
}


/*******************************************************************************
 * Compresses a file such that it takes up less space on disc
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - target_file      : The file to compress
 * - destination_file : The file to write to
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int compress_file(char *target_file, char *destination_file)
{
	/* open the file */
	FILE *target_p = fopen(target_file, "rb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        exit(1);
    }
    FILE *destination_p = fopen(destination_file, "wb");
    if (destination_p == NULL)
    {
        fprintf(stderr, "Error opening destination file\n");
        exit(2);
    }

	/* read the file char by char*/
	char c;
	while ((c = getc(target_p)) != EOF)
	{
		printf("Writing \n");
        printf("%c\n", c);
	}

	/* for each character, look up what the compressed bit string is */
	/*int success = char_to_bits(file_text[i], &s);*/

	/* loop through the bits in the bit string and turn it into new chars */

	/* write those chars to file */

	/* close the files */
	fclose(target_p);
	fclose(destination_p);

	return 0;
}


/*******************************************************************************
 * Decompresses a file
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - target_file      : The file to decompress
 * - destination_file : The file to write to
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int decompress_file(char *target_file, char *destination_file)
{
	/* open the files */
	FILE *target_p = fopen(target_file, "rb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        exit(1);
    }
    FILE *destination_p = fopen(destination_file, "wb");
    if (destination_p == NULL)
    {
        fprintf(stderr, "Error opening destination file\n");
        exit(2);
    }
    

	/* read characters as individual bits */


	/* find the strings of bits that correlate to a character */

	/* write that character to the file */

	/* close the files */
	fclose(target_p);
	fclose(destination_p);
	
	return 0;
}