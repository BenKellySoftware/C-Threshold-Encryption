#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){
	FILE * fPointer;
	fPointer = fopen("NewFile", "wb");

	FILE *file_p;
	file_p = fopen("black.bmp", "rb");
	fseek(file_p, 0L, SEEK_END);/*Go to the end of this file*/
	int size = ftell(file_p);/* get the position we are in the file as a number of bytes */
	rewind(file_p);/* go back to the start of the file so we can read it */
	printf("%d\n", size);/*Prints size for da refererence*/

	/*For loop for the size of file*/	
	int i;
	for ( i = 0; i < size; i++)
	{
		char* b = (char*)malloc(sizeof(char)*size);
		fread(b, sizeof(char), size, file_p);
		fwrite(b, sizeof(char), size, fPointer);
	}

	fclose(fPointer);
	fclose(file_p);

	return 0; 

}