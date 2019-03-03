#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/***********************************************************************
 * Return integer value from first line in file (formatted filename)
 **********************************************************************/
int get_int_value_from_filef(const char* format, ...)
{
	int value = 0;
	va_list a;
	va_start(a, format);
	value = vget_int_value_from_filef(format, a);
	va_end(a);
	return value;
}


/***********************************************************************
 * va_list wrapper function for get_int_value_from_filef()
 **********************************************************************/
int vget_int_value_from_filef(const char* format, va_list args)
{
	char filename[1024];
	if (vsnprintf(filename, sizeof(filename), format, args) == sizeof(filename))
		info("Error: filename buffer too small");
	return get_int_value_from_file(filename);
}


/***********************************************************************
 * Return integer value from first line in file
 **********************************************************************/
int get_int_value_from_file(const char* filename)
{
	FILE* fd = NULL;
	char buffer[512];
	int value = 0;

	if (!(fd = fopen(filename, "r")))
		return -1;

	if (fgets(buffer, sizeof(buffer), fd))
		value = get_int(buffer);

	fclose(fd);
	return value;
}


/***********************************************************************
 * Truncates a string at the first '\r' or '\n'
 **********************************************************************/
void chomp(char *string)
{
	string[strcspn(string, "\r\n")] = '\0';
}


/***********************************************************************
 * Fetches first number (ie the 35 of "35 123") from a
 * string
 **********************************************************************/
int get_int(const char* string)
{
	return atoi(strpbrk(string, "0123456789"));
}
