
/* NOTE : This file is for writing tests to check if functionality works.
   DO NOT SUBMIT THIS FILE */

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef RANDOM_H
#include "random.h"
#define RANDOM_H
#endif

#ifndef COLOUR_H
#include "colour.h"
#define COLOUR_H
#endif

#ifndef COMPRESSION_H
#include "compression.h"
#define COMPRESSION_H
#endif

/* prototypes */
void test_random(void);
void test_colour(void);
void test_bit_buffer_creation(void);
void test_bit_buffer_reading(void);
void test_compress_char(void);
void test_compression(void);
void test_compressed_file(void);
void test_decompression(void);
void test_full_compress(void);

int main(void)
{
	/*test_random();*/
	/*test_colour();*/
	/*test_bit_buffer_creation();*/
	/*test_bit_buffer_reading();*/
	/*test_compress_char();*/
	/*test_compression();*/
	/*test_compressed_file();*/
	/*test_decompression();*/
	test_full_compress();
	
	return 0;
}


void test_random(void)
{
	printf("Running test_random\n");
	int seed;
	printf("ENTER SEED (int) > ");
	scanf("%d", &seed);

	init_rand(seed);

	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%d\n", rand_int(-5, 5));
	}

	printf("\n");
}


void test_colour(void)
{
	printf("Running test_colours\n");

	colour_printf("red", "this is red text");
	colour_printf("green", " and this is green!\n");

	colour_printf("yellow", "this is yellow wow!");
	colour_printf("blue", " and this is blue?");
	colour_printf("magenta", " now this is magenta\n");

	colour_printf("cyan", "this is cyan,");
	colour_printf("white", " and this is white\n");

	printf("\n");
}


void test_bit_buffer_creation(void)
{
	printf("Running test_bit_buffer_creation\n");

	char c = 'Q';
	printf("Char is %c\n", c);

	bit_buffer_t b = char_to_buffer(c);

	display_buffer(b);

	char val = buffer_to_char(b);
	printf("Reading the buffer back, we get %c\n", val);
	bit_buffer_t b2 = char_to_buffer(val);
	display_buffer(b2);

	printf("\n");
}


void test_bit_buffer_reading(void)
{
	printf("Running test_bit_buffer_reading\n");

	bit_buffer_t b = char_to_buffer('T');
	display_buffer(b);

	int bit;

	int i;
	for (i = 0; i < 9; ++i)
	{
		bit = get_next_bit(&b);

		printf("%d\n", bit);
	}

	printf("\n");
}


void test_compress_char(void)
{
	printf("Running test_compress_char\n");

	unsigned char file_text[7] = {0x20, 0xff, 0x00, 0xde, 0xad, 0xbe, 0xef};

	int i;
	for (i = 0; i < 7; ++i)
	{
		char *s = "";
		printf("  Character compressing is %i\n", file_text[i]);

		int success = char_to_code(file_text[i], &s);

		printf("  Compressed is %s\n", s);
		printf("  Was %sa success\n", success ? "not " : "");

		printf("\n");
	}

	printf("\n");
}


void test_compression(void)
{
	printf("Running test_compression\n");

	char *target_file = "Test/compress_this_file.txt";
	char *destination_file = "Test/compress_this_file.bin";

	int success = compress_file(target_file, destination_file);
	printf("Was %sa success\n", success ? "not " : "");

	printf("\n");
}


void test_decompression(void)
{
	printf("Running test_decompression\n");

	char *target_file = "Test/compress_this_file.bin";
	char *destination_file = "Test/decompress_this_file.txt";

	int success = decompress_file(target_file, destination_file);
	printf("Was %sa success\n", success ? "not " : "");

	printf("\n");
}


void test_compressed_file(void)
{
	printf("Running test_compressed_file\n");
	char *filename = "Test/compress_this_file.bin";

	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error opening target file\n");
		exit(1);
	}
	
	int count = 0;
	char c = '\0';
	while ((c = getc(fp)) && count < 14)
	{
		bit_buffer_t b = char_to_buffer(c);
		display_buffer(b);
		count++;
	}

	fclose(fp);

	printf("\n");
}


void test_full_compress(void)
{
	printf("Running full_test_compression\n");

	char *base_file = "Test/image_1.bmp";
	char *compressed_file = "Test/image_1.bmp.compressed";
	char *uncompressed_file = "Test/image_1_uncompressed.bmp";

	printf("\n  Compressing file...\n");
	compress_file(base_file, compressed_file);

	printf("\n  Decompressing file...\n");
	decompress_file(compressed_file, uncompressed_file);

	printf("\n  Done!\n");
	printf("\n");
}