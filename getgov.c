/************************************************************************
 * This file is part of paramano.                                       *
 *                                                                      *
 * paramano is free software; you can redistribute it and/or            *
 * modify it under the terms of the GNU General Public License as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * License, or (at your option) any later version.                      *
 *                                                                      *
 * paramano is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with paramano. If not, see                                     *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

#include "string.h"
#include "getgov.h"
#include "getcore.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* [CORE][GOVERNOR NUMBER] */
char governors[999][50][13];
int total_governors;

/***********************************************************************
 * Grab all available governors
 **********************************************************************/
void gg_init()
{
	gchar gov_string[500];
	int i = 0;
	total_governors = 0;
	for(i = 0; i < gc_number(); ++i)
	{
		memset(gov_string, '\0', sizeof(gov_string) );
		gg_available(i, gov_string, sizeof(gov_string) );

		// go through every governor in gov_string
		gchar* curr = (char*)&gov_string;
		gchar* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while(end_of_curr)
		{
			memset(governors[i][total_governors], '\0', 13);
			memmove(governors[i][total_governors], curr, end_of_curr - curr);

			curr = end_of_curr+1;
			end_of_curr = g_strstr_len(curr, strlen(curr), " ");
			total_governors++;
		}
	}
}


/***********************************************************************
 * Populate out with current governor for core
 **********************************************************************/
int gg_current(int core, char* out, int size)
{
	FILE* fd;
	char path[FILE_PATH_SIZE];

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", core);

	if(!(fd = fopen(path, "r")))
	{
		debug("Couldn't open '%s'\n",path);
		return -1;
	}

	fgets(out, size, fd);
	// Chomp
	gchar* newline = g_strrstr(out, "\n");
	*newline = '\0';

	debug("Current gov for core %d is '%s'\n",core,out);

	fclose(fd);
	return 0;
}


/***********************************************************************
 * Populate out with number of available cores
 **********************************************************************/
int gg_available(int core, char* out, int size)
{
	FILE* fd;
	char path[80];

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_governors", core);

	if(!(fd = fopen(path, "r")))
	{
		debug("Couldn't open '%s'\n",path);
		return -1;
	}

	fgets(out, size, fd);

	fclose(fd);
	return 0;
}


/***********************************************************************
 * Return pointer to name of gov
 **********************************************************************/
char* gg_gov(int core, int index)
{
	return governors[core][index];
}

/***********************************************************************
 * Return total number of governors
 **********************************************************************/
int gg_number()
{
	return total_governors;
}
