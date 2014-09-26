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

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdio.h>

int  get_int_value_from_file(const char* filename);
int  get_int(const char* string);
bool file_has_line(const char *filename, const char *line);
FILE* check_for_file(char* path);

// <ew> Stringification of line number
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define STR_LINE STRING(__LINE__)
// </ew>


#ifdef DEBUG
/*
 Make debug macros into empty space if debug mode's not enabled.
 Otherwise, make debug macro calls into appropriate printf()s
*/
 #define debug(...)	printf("DEBUG: "__FILE__":"STR_LINE" --- "__VA_ARGS__)
#else
 #define debug(...);
#endif

#define info(...)	printf("INFO: "__FILE__":"STR_LINE" --- "__VA_ARGS__)
#define FILE_PATH_SIZE 2048
#endif
