#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef RANDOM_H
#include "random.h"
#define RANDOM_H
#endif



void test_random(void);


int main(void)
{
	test_random();

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