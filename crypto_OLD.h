
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef RANDOM_H
#include "random.h"
#define RANDOM_H
#endif

#ifndef MATH_H
#include <math.h>
#define MATH_H
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
    int x, y;
} point_t;


/* prototypes */

/*I don't think I need these, but I if it turns out I do, I'll uncomment it*/
/*char * generate_key(void);
int find_file_size(char* filename, long* filesize);
int read_file(char* filename, char* data, long* filesize);
double algorithmn_encrypt(double input, double key);
double algorithmn_decrypt(double input, double key);
int write_file(char* filename, char* data, long filesize);*/


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
char * generate_key(void)
{
    char * key = (char*) malloc(MASTER_KEY_LEN * sizeof(char));
	int i;
	for (i = 0; i < MASTER_KEY_LEN; i++)
	{
		key[i] = (char)rand_int(1, 255);
	}
    return key;
};


/*******************************************************************************
 * Simple equations to manipulate data in order to encrypt.
 *
 * The specific mathematical equation being used here is definetely up
 * for debate.
 *
 * Author:
 * - Jack
 *
*******************************************************************************/
double algorithmn_encrypt(double input, double key) {/*input key and clean data, output encrypted data*/
    return pow(input, key);
};

double algorithmn_decrypt(double input, double key) {/*input key and encrypted data, output clean data*/
    return pow(input, (1/key));
};


/*******************************************************************************
 * Encrypts a file with a key using division/ modulus, as well as XORing the
 * keys.
 *
 * Author:
 * - Jack
 *
 * Inputs:
 * - clean data: data that needs to be encrypted
 * - data size: size of data (file) in bytes
 *
 * Outputs:
 * - returns 0 if successful, otherwise 1
 * - key : Key used to encrypt file (given as a pointer)
 * - encrypted data (pointer)
 *
*******************************************************************************/
int encrypt_file(char* data_clean, char* key, long data_size, char* data_encrypt) {
	int error = 0; /*boolean for error. if 0, all good. if 1, we have problems*/

	char * key_rand = generate_key(); /*this is the random key, which is the first half of the full key*/
	/*we must make  decimal version of this, you'll see why in a minute*/
	long key_rand_no = (int)key_rand[0] + (pow(10,3) * (int) key_rand[1]) + (pow(10,6) * (int) key_rand[2]);
	key_rand_no = key_rand_no + (pow(10, 9) * (int)key_rand[3] + pow(10, 12) * (int)key_rand[4] + pow(10, 12) * (int)key_rand[5]);

	/*ENCRYPTION STUFF HERE*/
	char* data_encrypted = (char*) malloc(data_size * sizeof(char)); /*alliocate space for the ENCRYPTED data*/

	int i;
	for (i = 0; i < data_size; i++) {
		data_encrypted[i] = (char) algorithmn_encrypt((double) data_clean[i], key_rand_no);
	}

	if (error == 0) {/*if we have no errors so far, we know it is safe to return the data*/
		*key = *key_rand;/*give back the key*/
		/*give back encrypted data*/
		*data_encrypt = *data_encrypted; /*we pass the values instead of locations, so we can free local storage without troubles*/
	}
	free(data_encrypted);
	free(key_rand);

	return error;
};


/*******************************************************************************
 * Decrypts a file with its key using XORing the key, then multiplying with
 * remainder.
 *
 * Author:
 * - Jack
 *
 * Inputs:
 * - filename : Path to file to decrypt
 * - key      : Key used to decrypt the file
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 * - clean (unencrypted) data (as a pointer)
 *
*******************************************************************************/
int decrypt_file(char* data_encrypted, char* key, long data_size, char* data_cln) {
	int error = 0; /*boolean for error. if 0, all good. if 1, we have problems*/

	/*we must make  decimal version of the key, you'll see why in a minute*/
	long key_no = (int)key[0] + (pow(10, 3) * (int)key[1]) + (pow(10, 6) * (int)key[2]);
	key_no = key_no + (pow(10, 9) * (int)key[3] + pow(10, 12) * (int)key[4] + pow(10, 12) * (int)key[5]);

	char* data_clean = (char*)malloc((data_size) * sizeof(char)); /*alliocate space for the unenccrypted (clean) data*/

	int i;
	for (i = 0; i < data_size; i++) {
		data_clean[i] = (char)algorithmn_decrypt((double)data_encrypted[i], key_no);
	}

	if (error == 0) {/*if we have no errors so far, we know it is safe to return the data*/
		*data_cln = *data_clean; /*we pass the values instead of locations, so we can free local storage without troubles*/
	}
	free(data_clean);
	return error;
};








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
polynomial_t create_polynomial_from_key(char *key)
{
    polynomial_t line;
    line.a = (key[0] << 8) | key[1];
    line.b = (key[2] << 8) | key[3];
    line.c = (key[4] << 8) | key[5];
    return line;
}


/*******************************************************************************
 * Picks a point in the 2D plane that lies on the parabola based
 * on its coefficients
 *
 * Author:
 * - Rachel
 *
 * Inputs:
 * - p : polynomial
 *
 * Outputs:
 * - a new point
 *
*******************************************************************************/
point_t pick_point(polynomial_t poly)
{
    point_t point;

    point.x = rand_int(POINT_X_MIN, POINT_X_MAX);
    point.y = (poly.a * pow(point.x, 2)) + (poly.b * point.x) + poly.c;

    return point;
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
polynomial_t find_polynomial(point_t p1, point_t p2, point_t p3) {
    polynomial_t poly;

    poly.a = p1.y/((p1.x-p2.x)*(p1.x-p3.x)) + p2.y/((p2.x-p1.x)*(p2.x-p3.x)) + p3.y/((p3.x-p1.x)*(p3.x-p2.x));
    poly.b = -p1.y*(p2.x+p3.x)/((p1.x-p2.x)*(p1.x-p3.x))
             -p2.y*(p1.x+p3.x)/((p2.x-p1.x)*(p2.x-p3.x))
             -p3.y*(p1.x+p2.x)/((p3.x-p1.x)*(p3.x-p2.x));

    poly.c = p1.y*p2.x*p3.x/((p1.x-p2.x)*(p1.x-p3.x))
           + p2.y*p1.x*p3.x/((p2.x-p1.x)*(p2.x-p3.x))
           + p3.y*p1.x*p2.x/((p3.x-p1.x)*(p3.x-p2.x));

    return poly;
}


/*******************************************************************************
 * Retreives a key from a set of coefficients of a polynomial
 *
 * Author:
 * - Ben
 *
 * Inputs:
 * - p : polynomial object
 *
 * Outputs:
 * - Coefficients of p joined together as a key
 *
*******************************************************************************/
char *retrieve_key_from_polynomial(polynomial_t p) {
    char *key_p = (char *)malloc(sizeof(char) * MASTER_KEY_LEN);
    return key_p;
}