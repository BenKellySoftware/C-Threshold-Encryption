
/* DEBUG is either 0 or 1 */
#define DEBUG 0

/* LOG_LEVEL is 0 to 4 */
#define LOG_LEVEL 0


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
	/* check if any files were entered */
	if (argc <= 1)
	{
		fprintf(stderr, "No files entered for using as reference\n");
		return 1;
	}

	printf("Generating a huffman code file...\n");

	/* file pointer to use */
	FILE *file_p;

	/* byte count array */
	byte_counts_t counts = new_byte_counts();

	/* count the occurances of each byte in each file */
	int i;
	for (i = 1; i < argc; ++i)
	{
		#if DEBUG & LOG_LEVEL >= 0
			printf("Reading file: %s\n", filenames[i]);
		#endif

		file_p = fopen(filenames[i], "rb");
		if (file_p == NULL)
		{
			fprintf(stderr, "Failed opening file\n");
			return 1;
		}

		/* count the frequency of each byte */
		get_byte_counts(&counts, file_p);

		/* display these only in debug mode */
		#if DEBUG & LOG_LEVEL >= 4
			printf("  Displaying byte counts:\n");
			display_byte_counts(counts);
			printf("\n");
		#endif
	}

	/* create a list of nodes for the tree */
	node_list_t list = list_from_counts(counts);
	sort_nodes(&list);

	/* display the nodes only in debug mode */
	#if DEBUG & LOG_LEVEL >= 3
		printf("Displaying the list of nodes\n");
		display_nodes(list);
		printf("\n");
	#endif

	/* reduce the node list to a tree */
	node_t head = reduce_node_list(list);

	/* generate the huffman code */
	huffman_code_t *codes = new_huffman_codes();
	eval_code(codes, &head, "");

	/* only display the codes when in debug mode */
	#if DEBUG & LOG_LEVEL >= 2
		printf("Displaying the generated huffman codes\n");
		display_codes(codes);
		printf("\n");
	#endif

	if (!write_huffman_code_to_file(codes, "hackerman.codes"))
		return 1;

	printf("Done!\n");

	return 0;
}
