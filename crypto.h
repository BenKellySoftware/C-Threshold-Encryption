#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

/* Number of individual keys we create */
#define KEY_COUNT 5

/* structure for holding the coefficients of polynomial */
typedef struct polynomial {
	int a, b, c;
} polynomial_t;


/* structure for a point on a polynomial */
typedef struct point {
	float x, y;
} point_t;



/*******************************************************************************
 * Encrypts a file with a key using (encryption method)
 *
 * Author: 
 * - Jack
 *
 * Inputs:
 * - filename : Path to file to encrypt
 * - key      : Key used to encrypt file
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 *
*******************************************************************************/
int encrypt_file(char *filename, char *key);


/*******************************************************************************
 * Decrypts a file with its key using (encryption method)
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
 *
*******************************************************************************/
int decrypt_file(char *filename, char *key);


/*******************************************************************************
 * Generates a random key
 *
 * Author: 
 * - Jack
 *
 * Inputs:
 * - None
 *
 * Outputs:
 * - Generated key
 *
*******************************************************************************/
char *generate_key(void);


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
polynomial_t create_polynomial_from_key(char *key) {
	polynomial_t line;
	line.a = (key[0] << 24) | (key[1] << 16) | (key[2] << 8) | key[3];
	line.b = (key[4] << 24) | (key[5] << 16) | (key[6] << 8) | key[7];
	line.c = (key[8] << 24) | (key[9] << 16) | (key[10] << 8) | key[11];
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
point_t pick_point(polynomial_t p);


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
polynomial_t find_polynomial(point_t a, point_t b, point_t c);


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
char *retrieve_key_from_polynomial(polynomial_t p);