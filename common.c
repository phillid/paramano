/************************************************************************
 * This file is part of trayfreq-archlinux.                             *
 *                                                                      *
 * trayfreq-archlinux is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public Licence as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * Licence, or (at your option) any later version.                      *
 *                                                                      *
 * trayfreq-archlinux is distributed in the hope that it will be useful,*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public Licence for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public Licence    *
 * along with trayfreq-archlinux. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE true
#define FALSE false

/***********************************************************************
 * Gets integer value from file
 **********************************************************************/
int get_int_value_from_file(const char* filename)
{
	FILE* fd;
	char buffer[512];
	int value;

	if(!(fd = fopen(filename, "r")))
		return -1;

	if (fgets(buffer, 100, fd))
		value = get_int(buffer);

	fclose(fd);
	return value;
}


/***********************************************************************
 * Return true/false if a file has specified line or not
 **********************************************************************/
bool file_has_line(const char *filename, const char *line)
{
	FILE* fd;
	char buffer[512];

	if (!(fd = fopen(filename, "r")))
		return FALSE;

	while (fgets(buffer, sizeof(buffer), fd) != NULL)
	{
		if(strstr(buffer, line) != NULL)
		{
			fclose(fd);
			return TRUE;
		}
	}
	fclose(fd);
	return FALSE;
}


/***********************************************************************
 * Fetches first number from a string
 **********************************************************************/
int get_int(const char* string)
{
	char numbers[] = "1234567890";
	char* first_num;

	first_num = strpbrk(string, numbers);
	if(first_num)
		return atoi(first_num);

	return 1;
}
