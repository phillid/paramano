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

#include "paramano.h"

/* [CORE][GOVERNOR NUMBER] */
static char governors[999][50][13];
static int total_governors;

/***********************************************************************
 * Grab all available governors
 **********************************************************************/
void gg_init()
{
	gchar gov_string[500];
	unsigned int i = 0;
	total_governors = 0;
	for (i = 0; i < gc_number(); i++)
	{
		memset(gov_string, '\0', sizeof(gov_string) );
		gg_available(i, gov_string, sizeof(gov_string) );

		// go through every governor in gov_string
		gchar* curr = (char*)&gov_string;
		gchar* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while (end_of_curr)
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
bool gg_current(int core, char* out, int size)
{
	FILE* fd;
	char *path;
	asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", core);

	if (!(fd = fopen(path, "r")))
	{
		free(path);
		return false;
	}

	fgets(out, size, fd);

	// Get first line
	gchar* newline = g_strrstr(out, "\n");
	*newline = '\0';

	fclose(fd);
	free(path);
	return true;
}


/***********************************************************************
 * Populate `out` with number of available cores
 **********************************************************************/
bool gg_available(int core, char* out, int size)
{
	char *path;
	FILE *fd;
	asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_governors", core);

	if (!(fd = fopen(path, "r")))
	{
		free(path);
		return false;
	}
	fgets(out, size, fd);
	fclose(fd);
	free(path);
	return true;
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
unsigned int gg_number()
{
	return total_governors;
}
