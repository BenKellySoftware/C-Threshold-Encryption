
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


struct node {
	struct node *node1;
	struct node *node2;
	byte_count_obj_t *value;
	char *code;
};
typedef struct node node_t;

typedef struct node_list {
	int count;
	node_t *items;
} node_list_t;


int get_node_count(node_t n)
{
	int total = 0;

	if (n.value)
		total += n.value->count;

	else
	{
		if (n.node1)
			total += get_node_count(*n.node1);
		else
			printf("There was an error with node1\n");

		if (n.node2)
			total += get_node_count(*n.node2);
		else
			printf("There was an error with node2\n");
	}

	return total;
}


node_t new_node(byte_count_obj_t *o)
{
	node_t new_node;

	new_node.value = o;
	
	return new_node;
}


node_t join_nodes(node_t *n1, node_t *n2)
{
	node_t new_node;

	new_node.node1 = n1;
	new_node.node2 = n2;
	new_node.value = NULL;

	return new_node;
}