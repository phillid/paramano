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

#define MAX_CORES 1000
#define MAX_FREQS 50
#define FREQ_LENGTH 14

char freqs[MAX_CORES][MAX_FREQS][FREQ_LENGTH];
int total_freqs; // Number of freqs for core 0


/***********************************************************************
 * Initialise surrounding variables, get available freqs etc
 **********************************************************************/
void gf_init()
{
	char freq_string[4096]; // POSIX suggested line length. Source of error for CPUs with a huge number of freqs
	char *next_token;
	unsigned int i;

	memset(freqs, '\0', sizeof(freqs));


	for(i = 0; (i < gc_number() && i < MAX_CORES); i++)
	{
		memset(freq_string, '\0', sizeof(freq_string) );

		// Get available governor freqs. If no governor, try next cpu
		if (gf_available(i, freq_string, sizeof(freq_string) ) == -1)
		{
			debug("Couldn't find freq scaling on core %d\n",i);
			continue;
		}

		*strchrnul(freq_string, '\n') = '\0';

		// freq_string is a space separated list of freqs
		// Use strtok to find each
		next_token = strtok(freq_string, " \n");
		total_freqs = 0;
		do
		{
			chomp(next_token);
			debug("Found frequency #%d (%s KHz)\n",freq,next_token);
			strncpy(freqs[i][total_freqs], next_token, FREQ_LENGTH);
			total_freqs++;
		} while((next_token = strtok(NULL, " ")) != NULL);
	}

	// Hit the limit of storage of cores' frequencies
	if (i == MAX_CORES)
		info("Unable to add more than %d cores\n", MAX_CORES);

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
		debug("Couldn't open '%s'\n",path);
		free(path);
		return -1;
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
 * Populate `out` with a formatted, units-added freq label for `freq`
 **********************************************************************/
char* gf_get_frequency_label(int freq)
{
	char *string;
	if(freq >= 1000000000) // >= 1 billion KHz (1 THz) This, ladies and gentlement, is future-proofing ;)
		asprintf(&string, "%.2f THz", (float)freq/1000000000 );
	else if(freq >= 1000000) // >= 1 million KHz (1 GHz)
		asprintf(&string, "%.2f GHz", (float)freq/1000000 );
	else if (freq >= 1000) // >= 1 thousand KHz (1 MHz)
		asprintf(&string, "%.2f MHz", (float)freq/1000 );
	else // < 1000 KHz (1 MHz)
		asprintf(&string, "%.2f KHz", (float)freq);

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
