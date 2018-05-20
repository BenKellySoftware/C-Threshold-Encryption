
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
	int size;
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
	b.size = 8;

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
char buffer_to_char(bit_buffer_t b)
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
 * Clears a bit buffer to zeroes
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - b : Bit buffer to clear
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void clear_buffer(bit_buffer_t *b)
{
	b->seek = 0;
	b->size = 0;

	int i;
	for (i = 0; i < 8; ++i)
	{
		b->bit[i] = 0;
	}
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


/* looks like this isnt used */
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
 * Adds one bit to a bit buffer. Returns 1 if the buffer is full after this
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - b : Bit buffer to add to
 * - c : Value to add as the next bit to the bit buffer ('0' or '1')
 *
 * Outputs:
 * - 1 if bit buffer is full, else 0
 *
*******************************************************************************/
int add_bit_char(bit_buffer_t *b, char c)
{
	int val;

	if (c == '0')
		val = 0;
	else if (c == '1')
		val = 1;
	else
	{
		fprintf(stderr, "Error in add_bit_char (Character wasn't a bit)\n");
		exit(4);
	}

	b->bit[b->size++] = val;

	if (b->size == 8)
		return 1;
	return 0;
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

	/* string of bits */
	char *bit_string = "";
	char one_byte;

	int count = 0;
	bit_buffer_t buffer;
	clear_buffer(&buffer);

	/* read the file char by char*/
	char c;
	while ((c = getc(target_p)) != EOF)
	{
		/* for each character, look up what the compressed bit string is */
		/*int success = */char_to_bits(c, &bit_string);

		printf("size of bitstring is %lu\n", strlen(bit_string));

		/* have a count. for each bit we read, increment it by one */
		for (count = 0; count < strlen(bit_string); ++count)
		{
			/*printf("count is up to %d\n", count);*/

			/* move the bits into a bit buffer */
			if (add_bit_char(&buffer, bit_string[count]) == 1)
			{
				/* when the size of the bit buffer is 8, write that byte to a file */
				/*printf("Would write %d\n", buffer_to_char(buffer));*/
				display_buffer(buffer);

				one_byte = buffer_to_char(buffer);
				fwrite(&one_byte, 1, 2, destination_p);

				/* empty the bit buffer */
				clear_buffer(&buffer);
			}
		}

		printf("Left over buffer is of size %d and is : ", buffer.size);
		display_buffer(buffer);

		/* write byte to file */

	}
	/* write the left over bits to file */
	one_byte = buffer_to_char(buffer);
	fwrite(&one_byte, 1, 1, destination_p);


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