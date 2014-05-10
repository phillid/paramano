/************************************************************************
 * This file is part of trayfreq-archlinux.                             *
 *                                                                      *
 * trayfreq-archlinux is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public License as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * License, or (at your option) any later version.                      *
 *                                                                      *
 * trayfreq-archlinux is distributed in the hope that it will be useful,*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with trayfreq-archlinux. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

#include "common.h"

#include "debug.h" /* debug() */

#include <stdio.h> /* fopen, fgets, printf */
#include <stdlib.h> /* atoi */
#include <string.h> /* lots of functions */

/***********************************************************************
 * Gets integer value from first line in file
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
 * Return true/false if a file has specified line of text
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
 * Fetches first number (ie the 35 of "35 123") from a
 * string
 **********************************************************************/
int get_int(const char* string)
{
	char* first_num;

	first_num = strpbrk(string, "0123456789");
	debug("first_num: '%s'\n",first_num);
	if(first_num)
		return atoi(first_num);

	debug("first_num was 0, returning 1\n");
	return 1;
}
