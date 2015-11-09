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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CORES 1000
#define MAX_FREQS 50
#define FREQ_LENGTH 14

static char freqs[MAX_CORES][MAX_FREQS][FREQ_LENGTH];
static int total_freqs; /* Number of freqs for core 0 */


/***********************************************************************
 * Initialise surrounding variables, get available freqs etc
 **********************************************************************/
void gf_init()
{
	char freq_string[4096]; /* POSIX suggested line length. Source of error for CPUs with a huge number of freqs */
	char *next_token = NULL;
	unsigned int i = 0;

	memset(freqs, '\0', sizeof(freqs));

	for (i = 0; i < gc_number() && i < MAX_CORES; i++)
	{
		memset(freq_string, '\0', sizeof(freq_string) );

		/* Get available governor freqs. If no governor, try next cpu */
		if (gf_available(i, freq_string, sizeof(freq_string) ) == -1)
			continue;

		*strchrnul(freq_string, '\n') = '\0';

		/* freq_string is a space separated list of freqs.
		 * Use strtok to find each */
		next_token = strtok(freq_string, " \n");
		total_freqs = 0;
		do
		{
			strncpy(freqs[i][total_freqs], next_token, FREQ_LENGTH);
			total_freqs++;
		} while ((next_token = strtok(NULL, " ")) != NULL);
	}

	/* Hit the limit of storage of cores' frequencies */
	if (i == MAX_CORES)
		info("Unable to add more than %d cores\n", MAX_CORES);
}

/***********************************************************************
 * Return current frequency for core
 **********************************************************************/
int gf_current(int core)
{
	FILE* fd = NULL;
	char buff[4096];
	char path[1024];
	int freq = 0;

	snprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", core);

	if (!(fd = fopen(path, "r")))
		return -1;

	fgets(buff, 13, fd); /* FIXME magic */
	freq = atoi(buff);
	fclose(fd);

	return freq;
}


/***********************************************************************
 * Populate `out` with available frequencies for core
 **********************************************************************/
int gf_available(int core, char* out, int size)
{
	FILE* fd = NULL;
	char path[1024];

	snprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_frequencies", core);

	if (!(fd = fopen(path, "r")))
		return -1;

	fgets(out, size, fd);
	fclose(fd);
	return 0;
}

/***********************************************************************
 * Populate `out` with a formatted, units-added freq label for `freq`
 **********************************************************************/
void gf_get_frequency_label(char *buffer, size_t max_size, int freq)
{
	if (freq >= 1000000000) /* This, ladies and gentlement, is future-proofing */
		snprintf(buffer, max_size, "%.2f THz", (double)freq/1000000000 );
	else if (freq >= 1000000)
		snprintf(buffer, max_size, "%.2f GHz", (double)freq/1000000 );
	else if (freq >= 1000)
		snprintf(buffer, max_size, "%.2f MHz", (double)freq/1000 );
	else
		snprintf(buffer, max_size, "%.2f KHz", (double)freq);
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
unsigned int gf_number()
{
	return total_freqs;
}
