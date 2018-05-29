
#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef CRYPTO_H
#include "crypto.h"
#define CRYPTO_H
#endif

#ifndef COMPRESSION_H
#include "compression.h"
#define COMPRESSION_H
#endif

#ifndef COLOUR_H
#include "colour.h"
#define COLOUR_H
#endif


#define HUFFMAN_CODE_FILE "hackerman.codes"


/* prototypes */
int retrieve_recipe(char *filename, point_t a, point_t b, point_t c);
int add_recipe(char *filename);
int valid_print_menu(int choice);
void display_usage(void);


/*******************************************************************************
 * Asks for three keys, and runs the steps to decrypt and decompress
 * a given file.
 *
 * Author: 
 * - Leah
 *
 * Inputs:
 * - filename : The file to be decrypted
 * - a        : The first point to be used to decrypt
 * - b        : The second point to be used to decrypt
 * - c        : The third point to be used to decrypt
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 *
*******************************************************************************/
int retrieve_recipe(char *filename, point_t a, point_t b, point_t c)
{
    /* decrypting */
    polynomial_t poly = find_polynomial(a, b, c);
    unsigned char *key = retrieve_key_from_polynomial(poly);
    if (decrypt_file(key, filename))
        return 1;

    /* decompressing */
    huffman_code_t *codes = load_huffman_code_from_file(HUFFMAN_CODE_FILE);
    if (codes == NULL)
        return 1;
    if(decompress_file(codes, filename))
        return 1;

    return 0;
}


/*******************************************************************************
 * Runs through the steps to compress and encrypt a recipe
 *
 * Author: 
 * - Leah
 *
 * Inputs:
 * - filename : the file to be compressed and encrypted
 *
 * Outputs:
 * - 0 if successful, otherwise 1
 *
*******************************************************************************/
int add_recipe(char *filename)
{
    /* compressing */
    huffman_code_t *codes = load_huffman_code_from_file(HUFFMAN_CODE_FILE);
    if (codes == NULL)
        return 1;

    if (compress_file(codes, filename))
        return 1;

    /* encrypting */
    unsigned char *key = generate_key();
    polynomial_t poly = create_polynomial_from_key(key);
    if (encrypt_file(key, filename))
        return 1;

    /* display points */
    point_t p;
    int point_num;
    for (point_num = 0; point_num < KEY_COUNT; ++point_num)
    {
        p = pick_point(poly);
        printf("Point %d is (%d, %d)\n", point_num, (int)p.x, (int)p.y);
    }

    return 0;
}


/*******************************************************************************
 * Main
 * Runs the interface
 *
 * Author: 
 * - Rachel
 *
 * Inputs: 
 * - argc: arguement count
 * - argv: arguement value
 *
 * Outputs: 
 * - none
 *
 * There are two different modes that can be selected (-a and -v).
 * Mode -a is to add a recipe.
 * Mode -v is to view the recipe.
 *
*******************************************************************************/
int main(int argc, char* argv[])
{

    /*Allows random numbers for the crypto points and keys*/
    init_rand();

    char choice[1024];
    char file_dir[1024];
    point_t point_keys[3];

    colour_printf("blue", "Welcome to the Bepis Gola Database\n");
    if (argc <= 1) /* no arguement entered- therefore use scanf */
    {
        do
        {
            colour_printf("green", 
                "1. add a recipe\n"
                "2. view the recipe\n"
                "3. exit\n"
                "Please enter a number that correlates with your choice>\n");
            scanf("%s", choice);
            if (strcmp(choice, "1") == 0)
            {
                colour_printf("green", "Please enter the recipe file directory>"
                    "\n");

                scanf("%s", file_dir);

                if (add_recipe(file_dir))
                    return 1;
            }
            else if(strcmp(choice, "2") == 0)
            {
                colour_printf("green", "Please enter the recipe file directory>"
                    "\n");

                scanf("%s", file_dir);
                
                colour_printf("green", "KEY 1: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[0].x, &point_keys[0].y);
                colour_printf("green", "KEY 2: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[1].x, &point_keys[1].y);
                colour_printf("green", "KEY 3: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[2].x, &point_keys[2].y);
                /*TODO: look into how you make the input unreadable, like when
                you type in passwords in bash. this would be good for these keys*/
                if (retrieve_recipe(file_dir,
                                    point_keys[0],
                                    point_keys[1],
                                    point_keys[2]))
                {
                    return 1;
                }
            }
            else if (strcmp(choice, "3") == 0)
            {
                return 0;
            }
            else
            {
                colour_printf("red", "Invalid choice\n");
            }
        } 
        while(1);
    }
    else /* arguements already entered */
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            /*print help menu*/
            display_usage();
            exit(1);
        }
        if (strcmp(argv[1], "-a") == 0)
        {
            /* check if argc == 3, ie they entered ./main.out -a target_file */
            if (argc == 3)
            {
                strcpy(file_dir, argv[2]);
            }
            else
            {
                /* if they havent entered files, ask them to enter the target */
                /* and dest file */
                colour_printf("green", "Please enter the recipe file directory>"
                              "\n");
                scanf("%s", file_dir);
            }

            if (add_recipe(file_dir))
                return 1;
        }
        else if (strcmp(argv[1], "-v") == 0)
        {
            /* check if argc == 6, ie they entered ./main.out -v target_file */
            /* key1 key2 key3 */
            if (argc == 6)
            {
                strcpy(file_dir, argv[2]);

                sscanf(argv[3], "%lf,%lf", &point_keys[0].x, &point_keys[0].y);
                sscanf(argv[4], "%lf,%lf", &point_keys[1].x, &point_keys[1].y);
                sscanf(argv[5], "%lf,%lf", &point_keys[2].x, &point_keys[2].y);
            }
            else
            {
                /* if they havent entered files, ask them to enter the target*/ 
                /* file and points */
                colour_printf("green", "Please enter the recipe file directory>"
                              "\n");
                scanf("%s", file_dir);
                colour_printf("green", "KEY 1: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[0].x, &point_keys[0].y);
                colour_printf("green", "KEY 2: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[1].x, &point_keys[1].y);
                colour_printf("green", "KEY 3: Please enter two key numbers, "
                              "separated by a comma>");
                scanf("%lf, %lf", &point_keys[2].x, &point_keys[2].y);
            }
            if (retrieve_recipe(file_dir,
                point_keys[0],
                point_keys[1],
                point_keys[2]))
                {
                    return 1;
                }
        }
        else 
        {
            colour_printf("red", "There is no mode for the arguement you have " 
                          "entered.\n");
            return 1;
        }
    }

    return 0;   
}


/*******************************************************************************
 * This function checks for valid choice choice from user. 
 *  
 * Author: 
 * - Rachel
 *
 * Inputs:
 * - The users choice
 *
 * Outputs:
 * - 1 for valid
 * - 0 for invalid
*******************************************************************************/
int valid_print_menu(int choice)
{
    if (choice < 1 || choice > 2)
    {
        colour_printf("red", "Invalid choice\n");
        return 0;
    } 
    return 1;
}


/*******************************************************************************
 * This function displays the help menu.  
 *  
 * Author: 
 * - Rachel
 *
 * Inputs:
 * - none
 *
 * Outputs:
 * - none
*******************************************************************************/
void display_usage(void)
{
    colour_printf("cyan", "Help Menu:\n"
        "\n"
        "  -a   [adds a recipe to the Database] \n"
        "\n"
        "  -a target_file    [adds target_file directly to the Database\n"
        "                    otherwise program will prompt input of\n"
        "                    target_file]\n"
        "\n"
        "  -v   [views a recipe already in the Database]\n"
        "\n"
        "  -v target_file key1 key2 key3    [opens target_file directly using\n"
        "                                   3 keys otherwise the program will\n"
        "                                   prompt input of target_file\n"
        "                                   and 3 keys]\n"
        "\n"
        "  -h   [help menu]\n");
}

/*errors in red
warnings in yellow
general in blue
good in green */
