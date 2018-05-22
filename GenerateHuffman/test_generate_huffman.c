
#ifndef BYTECOUNT_H
#include "bytecount.h"
#define BYTECOUNT_H
#endif

#ifndef NODES_H
#include "nodes.h"
#define NODES_H
#endif

#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif


/* prototypes */
void test_node_linking(void);


int main(void)
{
	test_node_linking();

	return 0;
}



void test_node_linking(void)
{
	byte_counts_t counts = new_byte_counts();

	counts.items[0].byte = 'a';
	counts.items[1].byte = 'b';
	counts.items[2].byte = 'c';
	counts.items[3].byte = 'd';
	counts.items[4].byte = 'e';
	
	counts.items[0].count = 0;
	counts.items[1].count = 1;
	counts.items[2].count = 2;
	counts.items[3].count = 3;
	counts.items[4].count = 4;

	node_t n0 = new_node(&counts.items[0]);
	node_t n1 = new_node(&counts.items[1]);
	node_t n2 = new_node(&counts.items[2]);
	node_t n3 = new_node(&counts.items[3]);
	node_t n4 = new_node(&counts.items[4]);

	node_t n01 = join_nodes(&n0, &n1);
	node_t n23 = join_nodes(&n2, &n3);
	node_t n401 = join_nodes(&n4, &n01);
	node_t n40123 = join_nodes(&n401, &n23);

	printf("  n0 is %d\n", get_node_count(n0));
	printf("  n1 is %d\n", get_node_count(n1));
	printf("  n2 is %d\n", get_node_count(n2));
	printf("  n3 is %d\n", get_node_count(n3));
	printf("  n4 is %d\n", get_node_count(n4));
	printf("  n01 is %d\n", get_node_count(n01));
	printf("  n23 is %d\n", get_node_count(n23));
	printf("  n401 is %d\n", get_node_count(n401));
	printf("  n40123 is %d\n", get_node_count(n40123));
}