
#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif


/*******************************************************************************
 * Replaces text in a string. Used to rename file extensions
 *
 * Author:
 * - Tom
 *
 * Inputs:
 * - str : String to replace text in
 * - replace_str : String we are replacing
 * - with_str    : What we are replacing it with
 *
 * Outputs:
 * - None
 *
*******************************************************************************/
void replace_in_string(char **str, char *replace_str, char *with_str)
{
	static char temp[4096];
	static char buffer[4096];
	char *p;

	strcpy(temp, *str);

	/* Is replace_str even in temp? */
	if (!(p = strstr(temp, replace_str)))
	{
		return;
	}

	/* Copy characters from temp start to replace_str */
	strncpy(buffer, temp, p-temp);
	buffer[p-temp] = '\0';

	sprintf(buffer + (p - temp), "%s%s", with_str, p+strlen(replace_str));
	sprintf(temp, "%s", buffer);

	*str = temp;
}