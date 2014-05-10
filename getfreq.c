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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* [CORE][FREQUENCY NUMBER] */
char AVAILABLE_FREQUENCIES[999][50][13];
int NUMBER_OF_AVAILABLE_FREQUENCIES;

void gf_init()
{
	// TO DO : get rid of magic constants
	gchar freq_string[500];

	int i = 0;
	int j = 0;
	for(i = 0; i < gc_number(); ++i)
	{
		memset(freq_string, '\0', 500);

		// Get available governor freqs. If no governor, try next cpu
		if (gf_available(i, freq_string, 500) == -1)
		{
			debug("Couldn't find gov on core %d\n",i);
			continue;
		}

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
	debug("Found %d frequencies\n",j);
}

int gf_current(int core)
{
	FILE* fd;
	char buff[13];
	char path[80];
	int freq;

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", core);

	if(!(fd = fopen(path, "r")))
	{
		debug("Couldn't open '%s'\n",path);
		return -1;
	}

	fgets(buff, 13, fd);

	freq = atoi(buff);
	fclose(fd);
	debug("Found freq %d on core %d\n",freq,core);
	return freq;
}

int gf_available(int core, char* out, int size)
{
	FILE* fd;
	char path[80];

	sprintf(path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_frequencies", core);

	if(!(fd = fopen(path, "r")))
	{
		debug("Couldn't open '%s'\n",path);
		return -1;
	}

	fgets(out, size, fd);

	fclose(fd);
	return 0;
}

void gf_get_frequency_label(int freq, char* out)
{
	if(freq >= 1000000) // >= 1 million KHz (1GHz)
		sprintf(out, "%.2f GHz", ((float)freq/1000000) );
	else
		sprintf(out, "%.2d MHz", freq/1000);

	debug("Prepared freq label '%s' for freq %d\n",out,freq);
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
