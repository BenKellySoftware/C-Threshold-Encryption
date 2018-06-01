
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef STDLIB_H
#include <stdlib.h> /*malloc, free*/
#define STDLIB_H
#endif



typedef struct huffman_code {
	unsigned char symbol;
	char code[256];
} huffman_code_t;

typedef struct byte_count_obj {
	unsigned char byte;
	int count;
} byte_count_obj_t;

typedef struct byte_counts {
	byte_count_obj_t items[256];
	int total_byte_count;
} byte_counts_t;

typedef struct node {
	int is_leaf;

	struct node *node1;
	struct node *node2;
	byte_count_obj_t value;
} node_t;

typedef struct node_list {
	int count;
	node_t *items;
} node_list_t;



/*******************************************************************************
 * Creates a new byte counts list
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - None
 *
 * Outputs:
 * - A new list of byte counts
 *
*******************************************************************************/
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


/*******************************************************************************
 * Initialises a new node
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - o : Byte count to use as a reference for the character and count
 *
 * Outputs:
 * - A new leaf node representing the byte count
 *
*******************************************************************************/
node_t new_node(byte_count_obj_t o)
{
	node_t new_node;

	new_node.is_leaf = 1;
	new_node.value.byte = o.byte;
	new_node.value.count = o.count;

	return new_node;
}


/*******************************************************************************
 * Creates a new list of huffman codes
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - None
 *
 * Outputs:
 * - A new huffman code array pointer
 *
*******************************************************************************/
huffman_code_t *new_huffman_codes(void)
{
	huffman_code_t *h = (huffman_code_t*)malloc(sizeof(huffman_code_t)*256);

	/* setting symbols */
	int i;
	for (i = 0; i < 256; i++)
		h[i].symbol = i;

	return h;
}








/*******************************************************************************
 * Gets the frequency of bytes from a file
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - counts : A bytes count object
 * - file_p : A pointer to a file
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void get_byte_counts(byte_counts_t *counts, FILE *file_p)
{
	/* get the filesize of target */
	long filesize;
	fseek(file_p, 0L, SEEK_END);
	filesize = ftell(file_p);
	rewind(file_p);

	counts->total_byte_count += filesize;

	/* show the filesize if debug mode is on */
	#if DEBUG & LOG_LEVEL >= 1
		printf("  Total filesize is %d\n", counts->total_byte_count);
		printf("\n");
	#endif

	/* count them */
	int j;
	unsigned char c;
	for (j = 0; j < filesize; ++j)
	{
		c = getc(file_p);
		counts->items[c].count += 1;
	}
}


/*******************************************************************************
 * Gets total count after traversing down the tree
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - n : Node to get count of
 *
 * Outputs:
 * - total count
 *
*******************************************************************************/
int get_node_count(node_t *n)
{
	int total = 0;

	/* if the node is a leaf node, get the count of the bytecount
	   this node represents */
	if (n->is_leaf)
		total += n->value.count;

	else
	{
		/* node is a branch of two nodes, so add the count of those two nodes */
		total += get_node_count(n->node1);
		total += get_node_count(n->node2);
	}

	return total;
}








/*******************************************************************************
 * Creates a node list out of a byte_counts_t object
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - counts : Byte counts object
 *
 * Outputs:
 * - A new node list
 *
*******************************************************************************/
node_list_t list_from_counts(byte_counts_t counts)
{
	node_list_t list;
	list.items = (node_t*)malloc(sizeof(node_t) * 256);
	list.count = 256;

	int i;
	for (i = 0; i < 256; ++i)
	{
		list.items[i] = new_node(counts.items[i]);
	}

	return list;
}


/*******************************************************************************
 * Creates a branching node with two nodes
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - n1 : First node
 * - n2 : Second node
 *
 * Outputs:
 * - New branching node
 *
*******************************************************************************/
node_t join_nodes(node_t *n1, node_t *n2)
{
	node_t new_node;

	new_node.is_leaf = 0;
	new_node.node1 = n1;
	new_node.node2 = n2;

	return new_node;
}


/*******************************************************************************
 * Changes the order of two nodes such that the larger count node comes first
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - n1 : First node
 * - n2 : Second node
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void order_two_nodes(node_t *n1, node_t *n2)
{
	if (get_node_count(&*n1) < get_node_count(&*n2))
	{
		/* swap the pointer values */
		node_t temp;

		temp = *n1;
		*n1 = *n2;
		*n2 = temp;
	}
}


/*******************************************************************************
 * Sorts a node list so the nodes with larger counts come first
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - list : A node list pointer
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void sort_nodes(node_list_t *list)
{
	int i, j;
	for (i = 0; i < list->count; ++i)
		for (j = 1; j < list->count - i; ++j)
			order_two_nodes(&list->items[j-1], &list->items[j]);
}



/*******************************************************************************
 * Goes through one iteration of reducing the node list
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - list : Node list to reduce
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void reduce_node_list_iter(node_list_t *list)
{
	/* create new list to work off */
	node_list_t new_list;
	new_list.count = list->count-1;
	new_list.items = (node_t*)malloc(sizeof(node_t)*new_list.count);

	/* copy items into new list */
	int i;
	for (i = 0; i < list->count-2; ++i)
	{
		new_list.items[i] = list->items[i];	
	}

	/* make last node the join the last two nodes */
	new_list.items[list->count-2] = join_nodes(
			&list->items[list->count-1],
			&list->items[list->count-2]);

	/* sort list */
	sort_nodes(&new_list);

	/* make the old list this new list */
	*list = new_list;
}


/*******************************************************************************
 * Reduces a node list to one single node
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - list : Node list to reduce
 *
 * Outputs:
 * - A branch node for the whole list
 *
*******************************************************************************/
node_t reduce_node_list(node_list_t list)
{
	/* while there are more than one nodes in the list */
	while(list.count > 1)
		reduce_node_list_iter(&list);

	/* return the last remaining node */
	return list.items[0];
}


/*******************************************************************************
 * Evaluates a huffman code for each symbol
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - codes  : Huffman code list to append to
 * - node   : The head branch to use to make the codes
 * - prefix : Prefix for this nodes code
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void eval_code(huffman_code_t *codes, node_t *node, char prefix[256])
{
	if (node->is_leaf)
	{
		/* copy the symbol to codes */
		codes[node->value.byte].symbol = node->value.byte;

		/* copy the code to codes */
		strcpy(codes[node->value.byte].code, prefix);
	}
	else
	{
		/* create new prefix */
		char node1_prefix[256];
		char node2_prefix[256];
		
		/* that starts with the last prefix */
		strcpy(node1_prefix, prefix);
		strcpy(node2_prefix, prefix);

		/* but with a 0 or 1 at the end */
		strcat(node1_prefix, "0");
		strcat(node2_prefix, "1");

		/* evaluate branches of this node */
		eval_code(codes, node->node1, node1_prefix);
		eval_code(codes, node->node2, node2_prefix);
	}
}








/*******************************************************************************
 * Write codes to a file to use later
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - codes    : huffman code list
 * - filename : filename to write to
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void write_huffman_code_to_file(huffman_code_t *codes, char *filename)
{
	FILE *file_p = fopen(filename, "wb");
	if (file_p == NULL)
	{
		fprintf(stderr, "Error opening huffman code file\n");
		exit(1);
	}

	int i;
	for (i = 0; i < 256; ++i)
		fwrite(&codes[i], sizeof(huffman_code_t), 1, file_p);

	fclose(file_p);
}


/*******************************************************************************
 * Load the huffman symbol|code pairs
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - filename : Filename of the huffman codes
 *
 * Outputs:
 * - A huffman code list
 *
*******************************************************************************/
huffman_code_t *load_huffman_code_from_file(char *filename)
{
	huffman_code_t *codes = (huffman_code_t*)malloc(sizeof(huffman_code_t)*256);

	FILE *file_p = fopen(filename, "rb");
	if (file_p == NULL)
	{
		fprintf(stderr, "Error opening huffman code file\n");
		exit(1);
	}

	int i;
	for (i = 0; i < 256; ++i)
		fread(&codes[i], sizeof(huffman_code_t), 1, file_p);

	fclose(file_p);

	return codes;
}







#if DEBUG
/*******************************************************************************
 * Displays all the counts of bytes in a byte_count object
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - byte_counts : The byte counts obj to display
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void display_byte_counts(byte_counts_t byte_counts)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		printf("    %02x | %d\n", 
			byte_counts.items[i].byte,
			byte_counts.items[i].count);
	}
}


/*******************************************************************************
 * Displays a list of nodes and their counts
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - list : Node list to display
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void display_nodes(node_list_t list)
{
	int i;
	for (i = 0; i < list.count; ++i)
	{
		if (list.items[i].is_leaf)
			printf("  Item 0x%02x count is %d\n",
					list.items[i].value.byte,
					get_node_count(&list.items[i]));
		else
			printf("  Item ?%d? count is %d\n",
					i,
					get_node_count(&list.items[i]));
	}
}


/*******************************************************************************
 * Displays the codes of a huffman code list
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - codes : A list of huffman codes
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void display_codes(huffman_code_t *codes)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		printf("  0x%02x | %s\n", codes[i].symbol, codes[i].code);
	}
}
#endif








/*******************************************************************************
 * Huge obfuscated switch statement for compression. Writes to s a
 * string of characters representing bits to be written to a file
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - c : the character to compress
 * - s : the string to write to
 *
 * Outputs:
 * - 0 if successful, else 1
 *
*******************************************************************************/
int char_to_code(huffman_code_t *codes, unsigned int c, char **s)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		if (c == i)
		{
			*s = codes[i].code;
			return 0;
		}
	}

	return 1;
}


/*******************************************************************************
 * Huge obfuscated if elsif statement for decompression
 *
 * Author
 * - Tom
 *
 * Inputs:
 * - c : Character to store the decompressed bits to
 * - s : String of characters representing bits to decompress
 *
 * Outputs:
 * - Decompressed string
 *
*******************************************************************************/
int code_to_char(huffman_code_t *codes, char *c, char *s)
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		/*printf("checking %s\n", codes[i].code);*/
		if (strcmp(s, codes[i].code) == 0)
		{
			*c = i;
			return 0;
		}
	}

	return 1;
}
