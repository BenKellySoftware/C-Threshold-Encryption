
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

#ifndef CRYPTO_H
#include "crypto.h"
#define CRYPTO_H
#endif

#define DEBUG 1


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
void test_encrypt_text(void);
void test_decrypt_text(void);
void test_crypto_file(void);
void test_polynomials(void);
void test_pick_point(void);
void test_full_key_gen(void);
void test_get_key_from_poly(void);


int main(void)
{
	/*test_random();*/
	test_colour();
	/*test_bit_buffer_creation();*/
	/*test_bit_buffer_reading();*/
	/*test_compress_char();*/
	/*test_compression();*/
	/*test_compressed_file();*/
	/*test_decompression();*/
	/*test_full_compress();*/
	/*test_node_linking();*/
	/*test_huffman_code_generating();*/
	/*test_encrypt_text();*/
	/*test_decrypt_text();*/
	/*test_crypto_file();*/
	test_polynomials();
	test_pick_point();
	test_full_key_gen();
	test_get_key_from_poly();
	
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


void display_key(unsigned char *key)
{
	int i;
	printf("Key is 0x");
	for (i = 0; i < 6; ++i)
	{
		if (key[i] < 0)
			printf("%02x ", 256+key[i]);
		else
			printf("%02x ", key[i]);
	}
	printf("\n");
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

	char *target_file = "Test/decompress_this_file.txt";

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
	char *compress_this = "Test/image_1_compressed.bmp";
	char *decompress_this = "Test/image_1_decompressed.bmp";

	huffman_code_t *codes = load_huffman_code_from_file("hackerman.codes");


	printf("\n  Copying %s to %s\n", base_file, compress_this);	
	char command_1[1000];
	sprintf(command_1, "cp %s %s", base_file, compress_this);
	system(command_1);

	
	printf("\n  Compressing file...\n");
	compress_file(codes, compress_this);


	printf("\n  Copying %s to %s\n", compress_this, decompress_this);	
	char command_2[1000];
	sprintf(command_2, "cp %s %s", compress_this, decompress_this);
	system(command_2);


	printf("\n  Decompressing file...\n");
	decompress_file(codes, decompress_this);

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

	printf("\n");
}


void test_huffman_code_generating(void)
{
	printf("Running test_huffman_code_generating\n");

	node_list_t nl = create_example_node_list();
	sort_nodes(&nl);

	display_nodes(nl);

	node_t n = reduce_node_list(nl);

	printf("Item 0 count is %d\n", get_node_count(&n));

	huffman_code_t *codes = new_huffman_codes();
	eval_code(codes, &n, "");

	display_codes(codes);

	printf("\n");
}


void test_encrypt_text(void)
{
	printf("Running test_encrypt_text\n");

	/*char *plaintext = "Hello, world!";*/
	char plaintext[6] = {0xde, 0xad, 0xbe, 0xef, 0x00, 0xff};
	int data_len = 6;

	/* init rand */
	int seed = 12345;
	init_rand(seed);

	/* generate key ? */
	unsigned char *key = generate_key();

	display_key(key);

	/* spoof data to encrypt? */
	char *cyphertext = encrypt_data(key, plaintext, data_len);

	printf("plain: %s\n", plaintext);
	printf("crypt: %s\n", cyphertext);

	printf("\n");
}


void test_decrypt_text(void)
{
	printf("Running test_decrypt_text\n");

	char test_text[6] = {0xde, 0xad, 0xbe, 0xef, 0x00, 0xff};
	int data_len = 6;

	/* init rand */
	int seed = 54321;
	init_rand(seed);

	/* generate key ? */
	unsigned char *key = generate_key();

	display_key(key);

	char *cyphertext = encrypt_data(key, test_text, data_len);

	char *plaintext = encrypt_data(key, cyphertext, data_len);

	printf("crypt: %s\n", cyphertext);
	printf("plain: %s\n", plaintext);

	printf("\n");
}


void test_crypto_file(void)
{
	printf("Running test_crypto_file\n");

	int seed = 1337;
	init_rand(seed);

	/* generate key ? */
	unsigned char *key = generate_key();

	display_key(key);

	char *base_file = "Test/image_2.bmp";
	char *encrypt_this = "Test/image_2_encrypted.bmp";
	char *decrypt_this = "Test/image_2_decrypted.bmp";


	printf("\n  Copying %s to %s\n", base_file, encrypt_this);	
	char command_1[1000];
	sprintf(command_1, "cp %s %s", base_file, encrypt_this);
	system(command_1);

	
	printf("\n  Compressing file...\n");
	encrypt_file(key, encrypt_this);


	printf("\n  Copying %s to %s\n", encrypt_this, decrypt_this);	
	char command_2[1000];
	sprintf(command_2, "cp %s %s", encrypt_this, decrypt_this);
	system(command_2);


	printf("\n  Decompressing file...\n");
	decrypt_file(key, decrypt_this);

	printf("\n  Done!\n");
	printf("\n");
}


void test_polynomials(void)
{
	printf("Running test_polynomials\n");

	int seed = 739;
	init_rand(seed);

	unsigned char *key = generate_key();

	display_key(key);

	polynomial_t poly = create_polynomial_from_key(key);

	printf("a is 0x%x\n", poly.a);
	printf("b is 0x%x\n", poly.b);
	printf("c is 0x%x\n", poly.c);

	printf("\n");
}


void test_pick_point(void)
{
	printf("Running test_pick_point\n");

	printf("polynomial is 4x^2 + 3x + 57\n");

	/* x = 8 */
	point_t p1;
	p1.x = 8;
	p1.y = 4*8*8 + 3*8 + 57;

	/* x = 3 */
	point_t p2;
	p2.x = 3;
	p2.y = 4*3*3 + 3*3 + 57;

	/* x = 10 */
	point_t p3;
	p3.x = 10;
	p3.y = 4*10*10 + 3*10 + 57;


	printf("p1 is (%lf, %lf)\n", p1.x, p1.y);
	printf("p2 is (%lf, %lf)\n", p2.x, p2.y);
	printf("p3 is (%lf, %lf)\n", p3.x, p3.y);
	

	polynomial_t poly = find_polynomial(p1, p2, p3);

	printf("A is %d\n", poly.a);
	printf("B is %d\n", poly.b);
	printf("C is %d\n", poly.c);

	printf("\n");
}


void test_full_key_gen(void)
{
	printf("Running test_full_key_gen\n");

	int seed = 75843;
	init_rand(seed);

	unsigned char *key = generate_key();
	display_key(key);


	polynomial_t poly = create_polynomial_from_key(key);
	printf("A is %d\n", poly.a);
	printf("B is %d\n", poly.b);
	printf("C is %d\n", poly.c);


	point_t p1 = pick_point(poly);
	point_t p2 = pick_point(poly);
	point_t p3 = pick_point(poly);
	printf("p1 is (%lf, %lf)\n", p1.x, p1.y);
	printf("p2 is (%lf, %lf)\n", p2.x, p2.y);
	printf("p3 is (%lf, %lf)\n", p3.x, p3.y);
	

	polynomial_t poly_2 = find_polynomial(p1, p2, p3);

	printf("A is %d\n", poly_2.a);
	printf("B is %d\n", poly_2.b);
	printf("C is %d\n", poly_2.c);

	printf("\n");
}


void test_get_key_from_poly(void)
{
	printf("Running test_get_key_from_poly\n");

	int seed = 739;
	init_rand(seed);

	unsigned char *key = generate_key();
	display_key(key);

	polynomial_t poly = create_polynomial_from_key(key);
	printf("A is 0x%x\n", poly.a);
	printf("B is 0x%x\n", poly.b);
	printf("C is 0x%x\n", poly.c);

	unsigned char *got_key = retrieve_key_from_polynomial(poly);
	display_key(got_key);

	printf("\n");
}
