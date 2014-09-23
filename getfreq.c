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

#include "getfreq.h"
#include "getcore.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* [CORE][FREQUENCY NUMBER] */
char freqs[999][50][13];
int total_freqs;


/***********************************************************************
 * Initialise surrounding variables, get available freqs etc
 **********************************************************************/
void gf_init()
{
	char freq_string[500];
	unsigned int i;

	for(i = 0; i < gc_number(); i++)
	{
		memset(freq_string, '\0', sizeof(freq_string) );

		// Get available governor freqs. If no governor, try next cpu
		if (gf_available(i, freq_string, sizeof(freq_string) ) == -1)
		{
			debug("Couldn't find freq scaling on core %d\n",i);
			continue;
		}

		// freq_string is a space separated list of freqs so
		// iterate over each frequency in freq_string
		char* curr = &freq_string[0];
		char* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while(end_of_curr)
		{
			// TO DO : get rid of magic constants
			memset(freqs[i][total_freqs], '\0', 13); // TO DO: get rid of magic constant 13
			memmove(freqs[i][total_freqs], curr, end_of_curr - curr);

			curr = end_of_curr+1;
			end_of_curr = g_strstr_len(curr, strlen(curr), " ");
			total_freqs++;
		}
	}
	debug("Found %d frequencies\n",total_freqs);
}

/***********************************************************************
 * Return current frequency for core
 **********************************************************************/
int gf_current(int core)
{
	FILE* fd;
	char buff[13]; // TO DO : magic constant
	char* path;
	int freq;

	asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", core);

	if(!(fd = fopen(path, "r")))
	{
        free(path);
        asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_cur_freq", core);
		if (!(fd = fopen(path, "r"))) 
        {
            debug("Couldn't open '%s'\n", path);
            free(path);
            return -1;
        }
	}

	fgets(buff, 13, fd);

	freq = atoi(buff);
	fclose(fd);
	debug("Found freq %d on core %d\n",freq,core);

	free(path);
	return freq;
}


/***********************************************************************
 * Populate `out` with available frequencies for core
 **********************************************************************/
int gf_available(int core, char* out, int size)
{
	FILE* fd;
	char* path;

	asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_frequencies", core);

	if(!(fd = fopen(path, "r")))
	{
		debug("Couldn't open '%s'\n",path);
		free(path);
		return -1;
	}

	fgets(out, size, fd);

	fclose(fd);
	free(path);
	return 0;
}

/***********************************************************************
 * Populate `out` with a formatted, units-added freq label for freq
 **********************************************************************/
char* gf_get_frequency_label(int freq)
{
	char *string;
	if(freq >= 1000000) // >= 1 million KHz (1GHz)
		asprintf(&string, "%.2f GHz", ((float)freq/1000000) );
	else
		asprintf(&string, "%.2d MHz", freq/1000);

	debug("Prepared freq label '%s' for freq %d\n",string,freq);

	return string;
}

/***********************************************************************
 * Return freq value at index for core, as a string
 **********************************************************************/
char* gf_freqa(int core, int index)
{
	return freqs[core][index];
}

/***********************************************************************
 * Return freq value at index for core, as an int
 **********************************************************************/
int gf_freqi(int core, int index)
{
	return atoi(gf_freqa(core, index));
}

/***********************************************************************
 * Return total number of frequencies
 **********************************************************************/
int gf_number()
{
	return total_freqs;
}
