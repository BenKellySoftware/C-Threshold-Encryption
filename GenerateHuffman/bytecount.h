
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

/* used to count bytes */
typedef struct byte_count_obj {
	unsigned char byte;
	int count;
} byte_count_obj_t;

typedef struct byte_counts {
	byte_count_obj_t items[256];
	int total_byte_count;
} byte_counts_t;



byte_counts_t new_byte_counts(void)
{
	byte_counts_t counts;

	counts.total_byte_count = 0;

	int i;
	for (i = 0; i < 256; ++i)
	{
		/* initialising values */
		counts.items[i].byte = i;
		counts.items[i].count = 0;
	}

	return counts;
}


void get_byte_counts(byte_counts_t *counts, FILE *file_p)
{
	/* get the filesize of target */
	long filesize;
	fseek(file_p, 0L, SEEK_END);
	filesize = ftell(file_p);
	rewind(file_p);

	counts->total_byte_count += filesize;
	printf("total filesize is %d\n", counts->total_byte_count);

	/* count them */
	int j;
	unsigned char c;
	for (j = 0; j < filesize; ++j)
	{
		c = getc(file_p);
		counts->items[c].count += 1;
	}
}


void display_byte_counts(byte_counts_t byte_counts)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		printf("%02x | %d\n", 
			byte_counts.items[i].byte,
			byte_counts.items[i].count);
	}
}
