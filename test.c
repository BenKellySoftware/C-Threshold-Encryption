#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef RANDOM_H
#include "random.h"
#define RANDOM_H
#endif


#ifndef COLOUR_H
#include "colour.h"
#define COLOUR_H
#endif


void test_random(void);
void test_colour(void);


int main(void)
{
	test_random();
	test_colour();

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