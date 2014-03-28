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

#include "getfreq.h"
#include "getcore.h"
#include "math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* [CORE][FREQUENCY NUMBER] */
char AVAILABLE_FREQUENCIES[999][50][13];
int NUMBER_OF_AVAILABLE_FREQUENCIES;

void gf_init()
{
	gchar freq_string[500];

	int i = 0;
	int j = 0;
	for(i = 0; i < gc_number(); ++i)
	{
		memset(freq_string, '\0', 500);

		// Get available governor freqs. If no governor, try next cpu
		if (gf_available(i, freq_string, 500) == -1)
			continue;

		/* go through every frequency in freq_string */
		j = 0;
		gchar* curr = &freq_string[0];
		gchar* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while(end_of_curr)
		{
			memset(AVAILABLE_FREQUENCIES[i][j], '\0', 13);
			memmove(AVAILABLE_FREQUENCIES[i][j], curr, end_of_curr - curr);

			curr = end_of_curr+1;
			end_of_curr = g_strstr_len(curr, strlen(curr), " ");
			++j;
		}
	}
	NUMBER_OF_AVAILABLE_FREQUENCIES = j;
}

int gf_current(int core)
{
	FILE* fd;
	char buff[13];
	char path[80];
	char corestr[4];
	int freq;

	sprintf(corestr, "%i", core);

	sprintf(path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_cur_freq", corestr);

	if(!(fd = fopen(path, "r")))
	return -1;

	fgets(buff, 13, fd);

	freq = atoi(buff);
	fclose(fd);
	return freq;
}

int gf_available(int core, char* out, int size)
{
	FILE* fd;
	char path[80];
	char corestr[4];

	sprintf(corestr, "%i", core);

	sprintf(path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_available_frequencies", corestr);

	if(!(fd = fopen(path, "r")))
		return -1;

	fgets(out, size, fd);

	fclose(fd);
	return 0;
}

void gf_get_frequency_label(int freq, char* out)
{
	int i = 0;
	while(freq/pow(10, i) >= 1)
	  ++i;

	if(i == 7)
		sprintf(out, "%.2f GHz", freq/pow(10, i-1));
	else
		sprintf(out, "%.2d MHz", freq/1000);
}

char* gf_freqa(int core, int index)
{
	return AVAILABLE_FREQUENCIES[core][index];
}

int gf_freqi(int core, int index)
{
	return atoi(gf_freqa(core, index));
}

int gf_number()
{
	return NUMBER_OF_AVAILABLE_FREQUENCIES;
}
