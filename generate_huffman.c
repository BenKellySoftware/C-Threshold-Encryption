
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef HUFFMAN_H
#include "huffman.h"
#define HUFFMAN_H
#endif


int main(int argc, char const *filenames[])
{
	/* check if any files */
	if (argc <= 1)
	{
		fprintf(stderr, "No files entered for using as reference\n");
		exit(1);
	}

	printf("Generating a huffman code file\n");

	/* file pointer to use */
	FILE *file_p;


	/* byte count array */
	byte_counts_t counts = new_byte_counts();


	/* count the occurances of each byte in each file */
	int i;
	for (i = 1; i < argc; ++i)
	{
		printf("Reading file: %s\n", filenames[i]);

		file_p = fopen(filenames[i], "rb");
		if (file_p == NULL)
		{
			fprintf(stderr, "Error opening destination file\n");
			exit(1);
		}

		get_byte_counts(&counts, file_p);

		display_byte_counts(counts);
	}

	
	node_list_t list = list_from_counts(counts);
	sort_nodes(&list);

	display_nodes(list);

	node_t head = reduce_node_list(list);

	huffman_code_t *codes = new_huffman_codes();
	eval_code(codes, &head, "");

	view_codes(codes);

	write_huffman_code_to_file(codes, "hackerman.codes");

	return 0;
}