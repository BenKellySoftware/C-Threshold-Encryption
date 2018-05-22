
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef MATH_H
#include <math.h>
#define MATH_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef BYTECOUNT_H
#include "bytecount.h"
#define BYTECOUNT_H
#endif

#ifndef NODES_H
#include "nodes.h"
#define NODES_H
#endif


int main(int argc, char const *filenames[])
{
	printf("Generating a huffman code file\n");

	/* check if any files */
	if (argc <= 1)
	{
		fprintf(stderr, "No files entered for using as reference\n");
		exit(1);
	}


	/* file pointer to use */
	FILE *file_p;


	/* byte count array */
	byte_counts_t probs = new_byte_prob();


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

		get_byte_counts(&probs, file_p);

		display_byte_counts(probs);
	}

	/* code */
	return 0;
}