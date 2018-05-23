
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif


int rand_int(int min_num, int max_num)
{
    /*
    Generates random int x that fits
    min_num <= x < max_num
    */

    unsigned int
        num_bins = (unsigned int) max_num - min_num,
        num_rand = (unsigned int) RAND_MAX,
        bin_size = num_rand / num_bins,
        defect   = num_rand % num_bins;

    int x;

    do {
        x = rand();
    } while (num_rand - defect <= (unsigned int)x);

    return x/bin_size + min_num;
}


void init_rand(int seed)
{
    srand(seed);
}