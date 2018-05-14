
/*******************************************************************************
 * Compresses a file such that it takes up less space on disc
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - filename : The file to compress
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int compress_file(char *filename);


/*******************************************************************************
 * Decompresses a file
 *
 * Author: 
 * - Tom
 *
 * Inputs:
 * - filename : The file to decompress
 *
 * Output:
 * - 0 if successful, otherwise 1
 *
 ******************************************************************************/
int decompress_file(char *filename);