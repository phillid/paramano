/************************************************************************
 * This file is part of trayfreq.                                       *
 *                                                                      *
 * trayfreq is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published    *
 * by the Free Software Foundation; either version 3 of the License, or *
 * (at your option) any later version.                                  *
 *                                                                      *
 * trayfreq is distributed in the hope that it will be useful,	        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with trayfreq. If not, see <http://www.gnu.org/licenses/>.     *
 ************************************************************************/

#include "getgov.h"
#include "getcore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* [CORE][GOVERNOR NUMBER] */
gchar AVAILABLE_GOVERNORS[999][50][13];
gint NUMBER_OF_AVAILABLE_GOVERNORS;

void gg_init()
{
	gchar gov_string[500];
	int i = 0;
	int j = 0;
	for(i = 0; i < gc_number(); ++i)
	{
		memset(gov_string, '\0', 500);
		gg_available(i, gov_string, 500);

		/* go through every governor in gov_string */
		j = 0;
		gchar* curr = &gov_string[0];
		gchar* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while(end_of_curr)
		{
		memset(AVAILABLE_GOVERNORS[i][j], '\0', 13);
		memmove(AVAILABLE_GOVERNORS[i][j], curr, end_of_curr - curr);

		curr = end_of_curr+1;
		end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		++j;
		}
	}
	NUMBER_OF_AVAILABLE_GOVERNORS = j;
}

int gg_current(int core, char* out, int size)
{
	FILE* fd;
	char path[80];
	char corestr[4];

	sprintf(corestr, "%i", core);

	sprintf(path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_governor", corestr);

	if(!(fd = fopen(path, "r")))
		return -1;

	fgets(out, size, fd);

	/* remove newline at the end */
	gchar* newline = g_strrstr(out, "\n");
	*newline = '\0';

	fclose(fd);
	return 0;
}

int gg_available(int core, char* out, int size)
{
	FILE* fd;
	char path[80];
	char corestr[4];

	sprintf(corestr, "%i", core);

	sprintf(path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_available_governors", corestr);

	if(!(fd = fopen(path, "r")))
		return -1;

	fgets(out, size, fd);

	fclose(fd);
	return 0;
}

char* gg_gov(int core, int index)
{
	return AVAILABLE_GOVERNORS[core][index];
}

int gg_number()
{
	return NUMBER_OF_AVAILABLE_GOVERNORS;
}
