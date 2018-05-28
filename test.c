
/* NOTE : This file is for writing tests to check if functionality works.
   DO NOT SUBMIT THIS FILE */

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
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

#ifndef HUFFMAN_H
#include "huffman.h"
#define HUFFMAN_H
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
void test_node_linking(void);
void test_huffman_code_generating(void);

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
	/*test_node_linking();*/
	/*test_huffman_code_generating();*/
	
	return 0;
}


node_list_t create_example_node_list(void)
{
	byte_counts_t counts = new_byte_counts();

	counts.items[0].byte = 'a';
	counts.items[1].byte = 'b';
	counts.items[2].byte = 'c';
	counts.items[3].byte = 'd';
	counts.items[4].byte = 'e';
	
	counts.items[0].count = 1;
	counts.items[1].count = 6;
	counts.items[2].count = 15;
	counts.items[3].count = 23;
	counts.items[4].count = 9;

	printf("making new nodes\n");
	node_t n0 = new_node(counts.items[0]);
	node_t n1 = new_node(counts.items[1]);
	node_t n2 = new_node(counts.items[2]);
	node_t n3 = new_node(counts.items[3]);
	node_t n4 = new_node(counts.items[4]);

	printf("creating list of nodes\n");
	node_list_t nl;
	nl.items = (node_t*)malloc(sizeof(node_t) * 9);
	nl.count = 5;

	nl.items[0] = n0;
	nl.items[1] = n1;
	nl.items[2] = n2;
	nl.items[3] = n3;
	nl.items[4] = n4;

	return nl;
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

	huffman_code_t *codes = load_huffman_code_from_file("hackerman.codes");

	unsigned char file_text[7] = {0x20, 0xff, 0x00, 0xde, 0xad, 0xbe, 0xef};

	int i;
	for (i = 0; i < 7; ++i)
	{
		char *s = "";
		printf("  Character compressing is %i\n", file_text[i]);

		int success = char_to_code(codes, file_text[i], &s);

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

	huffman_code_t *codes = load_huffman_code_from_file("hackerman.codes");

	int success = compress_file(codes, target_file);
	printf("Was %sa success\n", success ? "not " : "");

	printf("\n");
}


void test_decompression(void)
{
	printf("Running test_decompression\n");

	char *target_file = "Test/decompress_this_file.txt.compressed";

	huffman_code_t *codes = load_huffman_code_from_file("hackerman.codes");

	int success = decompress_file(codes, target_file);
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
	char *compressed_file = "Test/image_1_copy.bmp.compressed";

	huffman_code_t *codes = load_huffman_code_from_file("hackerman.codes");

	printf("\n  Compressing file...\n");
	compress_file(codes, base_file);

	printf("\n  Copying %s.compressed to %s\n", base_file, compressed_file);	
	char command[1000];
	sprintf(command, "cp %s.compressed %s", base_file, compressed_file);
	system(command);

	printf("\n  Decompressing file...\n");
	decompress_file(codes, compressed_file);

	printf("\n  Done!\n");
	printf("\n");
}


void test_node_linking(void)
{
	printf("Running test_node_linking\n");

	node_list_t nl = create_example_node_list();
	sort_nodes(&nl);

	printf("List of nodes before huffman blasting it\n");
	display_nodes(nl);

	node_t n = reduce_node_list(nl);
	printf("Last node is...\n");

	printf("Item 0 count is %d\n", get_node_count(&n));
}


void test_huffman_code_generating(void)
{
	node_list_t nl = create_example_node_list();
	sort_nodes(&nl);

	display_nodes(nl);

	node_t n = reduce_node_list(nl);

	printf("Item 0 count is %d\n", get_node_count(&n));

	huffman_code_t *codes = new_huffman_codes();
	eval_code(codes, &n, "");

	view_codes(codes);
}