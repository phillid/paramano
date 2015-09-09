/************************************************************************
 * This file is part of Paramano.                                       *
 *                                                                      *
 * Paramano is free software; you can redistribute it and/or            *
 * modify it under the terms of the GNU General Public License as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * License, or (at your option) any later version.                      *
 *                                                                      *
 * Paramano is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Paramano. If not, see                                     *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

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
		fprintf(stderr, "WARN: filename buffer too small");
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

	if(!(fd = fopen(filename, "r")))
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
