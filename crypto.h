
#ifndef STDLIB_H
#include <stdlib.h> /*malloc, long*/
#define STDLIB_H
#endif

#ifndef STDIO_H
#include <stdio.h> /*fprintf printf, rewind, fseek*/
#define STDIO_H
#endif

/* Number of individual keys we create */
#define KEY_COUNT 5
#define POINT_X_MIN -100
#define POINT_X_MAX 100
#define MASTER_KEY_LEN 6


/* structure for holding the coefficients of polynomial */
typedef struct polynomial {
    int a, b, c;
} polynomial_t;


/* structure for a point on a polynomial */
typedef struct point {
    double x, y;
} point_t;



/*******************************************************************************
 * Generates random int x that fits between 2 values x
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - min possible value (inclusive)
 * - max possible value (non inclusive)
 *
 * Outputs: 
 * - int x where min <= x < max
 *
*******************************************************************************/
int rand_int(int min, int max)
{
    unsigned int
        num_bins = (unsigned int) max - min,
        num_rand = (unsigned int) RAND_MAX,
        bin_size = num_rand / num_bins,
        defect   = num_rand % num_bins;

    int x;

    do {
        x = rand();
    } while (num_rand - defect <= (unsigned int)x);

    
    #if DEBUG
        printf("Random number is %d\n", x/bin_size + min);
    #endif
    
    return x/bin_size + min;
}


/*******************************************************************************
 * Reads from the random system file to get a seed for the program
 *
 * Author: 
 * - Ben
 *
 * Inputs:
 * - None
 *
 * Outputs: 
 * - None
 *
*******************************************************************************/
void init_rand(void)
{
    FILE *rand_p = fopen("/dev/random", "r");
    char seed = fgetc(rand_p);
    fclose(rand_p);

    #if DEBUG
        printf("Random seed is %c\n", seed);
    #endif

    srand(seed);
}


/*******************************************************************************
 * Generates a random key, based upon the size of the file.
 *
 * Author:
 * - Jack
 *
 * Inputs:
 * - none
 *
 * Outputs:
 * - Generated key
 *
*******************************************************************************/
unsigned char * generate_key(void)
{
    unsigned char *key = (unsigned char *)malloc(MASTER_KEY_LEN);

    int i;
    for (i = 0; i < MASTER_KEY_LEN; i++)
    {
        key[i] = rand_int(1, 255);
    }

    return key;
}


/*******************************************************************************
 * Encrypts a string with a key using XOR
 *
 * Author:
 * - author_name
 *
 * Inputs:
 * - key       : key
 * - plaintext : unencrypted data
 * - data_len  : length of data
 *
 * Outputs:
 * - pointer to cyphertext
 *
*******************************************************************************/
char * encrypt_data(const unsigned char *key, const char *plaintext, int data_len)
{
    /*allocate space for the ENCRYPTED data*/
    char *cyphertext = (char *)malloc(data_len);

    int index_of_key = 0;

    int i;
    for (i = 0; i < data_len; ++i)
    {
        /* xor char of plaintext with char of key */
        cyphertext[i] = (char)(plaintext[i] ^ key[index_of_key++]);
        /*cyphertext[i] = (char)(plaintext[i] ^ '\0');*/

        /* if we reached the end of the key, go back to the start */
        if (index_of_key == MASTER_KEY_LEN)
            index_of_key = 0;
    }

    return cyphertext;
}


/*******************************************************************************
 * Decrypts a string with a key using XOR
 *
 * Author:
 * - author_name
 *
 * Inputs:
 * - key        : key
 * - cyphertext : encrypted data
 * - data_len   : length of data
 *
 * Outputs:
 * - pointer to plaintext
 *
*******************************************************************************/
char * decrypt_data(const unsigned char *key, const char *cyphertext, int data_len)
{
    /*allocate space for the ENCRYPTED data*/
    char *plaintext = (char *)malloc(data_len);

    int index_of_key = 0;

    int i;
    for (i = 0; i < data_len; ++i)
    {
        /* xor char of plaintext with char of key */
        plaintext[i] = (char)(cyphertext[i] ^ key[index_of_key++]);
        /*plaintext[i] = (char)(cyphertext[i] ^ '\0');*/

        /* if we reached the end of the key, go back to the start */
        if (index_of_key == MASTER_KEY_LEN)
            index_of_key = 0;
    }

    return plaintext;
}


/*******************************************************************************
 * Encrypts a file
 *
 * Author:
 * - Jack
 *
 * Inputs:
 * - key         : key
 * - target_file : file to encrypt
 *
 * Outputs:
 * - 0 if success, else 1
 *
*******************************************************************************/
int encrypt_file(const unsigned char *key, const char *target_file)
{
    FILE *target_p;

    /* open the file */
    target_p = fopen(target_file, "rb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        return 1;
    }

    /* get the filesize of target */
    long file_size;
    fseek(target_p, 0L, SEEK_END);
    file_size = ftell(target_p);
    rewind(target_p);

    /* read all data from file */
    char *plaintext = (char *)malloc(file_size);
    fread(plaintext, sizeof(char), file_size, target_p);

    /* close file */
    fclose(target_p);

    /* encrypt data */
    char *cyphertext = encrypt_data(key, plaintext, file_size);

    /* open the file again for writing */
    target_p = fopen(target_file, "wb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        return 1;
    }

    /* write the cyphertext */
    fwrite(cyphertext, file_size, 1, target_p);

    /* close the file */
    fclose(target_p);

    return 0;
}


/*******************************************************************************
 * Decrypts a file
 *
 * Author:
 * - Jack
 *
 * Inputs:
 * - key         : key
 * - target_file : file to decrypt
 *
 * Outputs:
 * - 0 if success, else 1
 *
*******************************************************************************/
int decrypt_file(const unsigned char *key, const char *target_file)
{
    FILE *target_p;

    /* open the file */
    target_p = fopen(target_file, "rb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        return 1;
    }

    /* get the filesize of target */
    long file_size;
    fseek(target_p, 0L, SEEK_END);
    file_size = ftell(target_p);
    rewind(target_p);

    /* read all data from file */
    char *cyphertext = (char *)malloc(file_size);
    fread(cyphertext, sizeof(char), file_size, target_p);

    /* close file */
    fclose(target_p);

    /* decrypt data */
    char *plaintext = decrypt_data(key, cyphertext, file_size);

    /* open the file again for writing */
    target_p = fopen(target_file, "wb");
    if (target_p == NULL)
    {
        fprintf(stderr, "Error opening target file\n");
        return 1;
    }

    /* write the plaintext */
    fwrite(plaintext, file_size, 1, target_p);

    /* close the file */
    fclose(target_p);

    return 0;
}


/*******************************************************************************
 * Creates coefficients of a polynomial from a key
 *
 * Author:
 * - Ben
 *
 * Inputs:
 * - key : key to split into coefficients
 *
 * Outputs:
 * - A polynomial object
 *
*******************************************************************************/
polynomial_t create_polynomial_from_key(const unsigned char *key)
{
    polynomial_t poly;
    poly.a = (key[0] << 8) + key[1];
    poly.b = (key[2] << 8) + key[3];
    poly.c = (key[4] << 8) + key[5];

    return poly;
}


/*******************************************************************************
 * Picks a point in the 2D plane that lies on a parabola based
 * on its coefficients
 *
 * Author:
 * - Rachel
 *
 * Inputs:
 * - poly : polynomial
 *
 * Outputs:
 * - a new point
 *
*******************************************************************************/
point_t pick_point(polynomial_t poly)
{
    point_t new_point;

    int x = rand_int(POINT_X_MIN, POINT_X_MAX);

    new_point.x = x;
    new_point.y = poly.a*x*x + poly.b*x + poly.c;

    return new_point;
}


/*******************************************************************************
 * Finds the coefficients for a polynomial based on the coordinates of
 * three points.
 *
 * Author:
 * - Ben
 *
 * Inputs:
 * - a : First point that lies on the polynomial
 * - b : Second point that lies on the polynomial
 * - c : Third point that lies on the polynomial
 *
 * Outputs:
 * - A polynomial that all three points lay on
 *
*******************************************************************************/
polynomial_t find_polynomial(point_t p1, point_t p2, point_t p3)
{
    polynomial_t poly;

    /* using simultaneous equations and matrix equations
            | p1.x^2  p1.x  1 |
        A = | p2.x^2  p2.x  1 |
            | p3.x^2  p3.x  1 |

            | poly.a |
        B = | poly.b |
            | poly.c |

            | p1.y |
        C = | p2.y |
            | p3.y |

        AB = C
    */

    double D = (
        p1.x * p1.x * p2.x * 1 +
        p2.x * p2.x * p3.x * 1 +
        p3.x * p3.x * p1.x * 1
    ) - (
        p1.x * p1.x * p3.x * 1 +
        p2.x * p2.x * p1.x * 1 +
        p3.x * p3.x * p2.x * 1
    );

    #if DEBUG
        printf("Discriminant is %f\n", D);
    #endif    

    poly.a = (
        (
            p1.x * p3.y * 1 +
            p2.x * p1.y * 1 +
            p3.x * p2.y * 1
        ) - (
            p1.x * p2.y * 1 +
            p2.x * p3.y * 1 +
            p3.x * p1.y * 1 
        )
    )/D;

    poly.b = (
        (
            p1.x * p1.x * p2.y * 1 +
            p2.x * p2.x * p3.y * 1 +
            p3.x * p3.x * p1.y * 1
        ) - (
            p1.x * p1.x * p3.y * 1 +
            p2.x * p2.x * p1.y * 1 +
            p3.x * p3.x * p2.y * 1
        )
    )/D;

    poly.c = (
        (
            p1.x * p1.x * p2.x * p3.y +
            p2.x * p2.x * p3.x * p1.y +
            p3.x * p3.x * p1.x * p2.y
        ) - (
            p1.x * p1.x * p3.x * p2.y +
            p2.x * p2.x * p1.x * p3.y +
            p3.x*p3.x * p2.x * p1.y
        )
    )/D;

    return poly;
}


/*******************************************************************************
 * Retreives a key from a set of coefficients of a polynomial
 *
 * Author:
 * - Ben
 *
 * Inputs:
 * - poly : polynomial object
 *
 * Outputs:
 * - Coefficients of p joined together as a key
 *
*******************************************************************************/
unsigned char * retrieve_key_from_polynomial(polynomial_t poly)
{
    unsigned char *key = (unsigned char *)malloc(MASTER_KEY_LEN);

    key[0] = poly.a >> 8;
    key[1] = poly.a & 0xff;

    key[2] = poly.b >> 8;
    key[3] = poly.b & 0xff;

    key[4] = poly.c >> 8;
    key[5] = poly.c & 0xff;

    return key;
}