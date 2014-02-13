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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getfreq.h"

static void set_freq_max(char* freq, char* core)
{
	char file_path[100];
	sprintf(file_path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_max_freq", core);

	FILE* fd = fopen(file_path, "w");
	fprintf(fd, freq);
	fclose(fd);
}

static void set_freq_min(char* freq, char* core)
{
	char file_path[100];
	sprintf(file_path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_min_freq", core);

	FILE* fd = fopen(file_path, "w");
	fprintf(fd, freq);
	fclose(fd);
}

static void set_speed(char* freq, char* core)
{
	char file_path[100];
	sprintf(file_path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_setspeed", core);

	FILE* fd = fopen(file_path, "w");
	fprintf(fd, freq);
	fclose(fd);
}

void set_gov(char* gov, char* core)
{
	char file_path[100];
	sprintf(file_path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_governor", core);

	FILE* fd = fopen(file_path, "w");
	fprintf(fd, gov);
	fclose(fd);
}

void set_freq(char* freq, char* core)
{
	set_gov("userspace", core);
	set_speed(freq, core);
}

int main(int argc, char *argv[])
{
	gc_init();
	gf_init();

	if(!argv[1])
	{
		printf("Use -g to set the governor or -f to set the frequency.\n");
	}
	else if(strcmp(argv[1], "-g") == 0)
	{
		if(!argv[2])
			printf("Pass the governor to set after the -g.\n");
		else
		{
			if(!argv[3])
				printf("Use -c to set the core.\n");
			else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf("Pass the core to set after the -c.\n");
				else
					set_gov(argv[2], argv[4]);
			} else
				printf("Use -c to set the core.\n");
		}
	}
	else if(strcmp(argv[1], "-f") == 0)
	{
		if(!argv[2])
		{
			printf("Pass the frequency to set after the -f.\n");
		} else {
			if(!argv[3])
			{
				printf("Use -c to set the core.\n");
			} else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf("Pass the core to set after the -c.\n");
				else
					set_freq(argv[2], argv[4]);
			} else {
				printf("Use -c to set the core.\n");
			}
		}
	} else {
		printf("Use -g to set the governor or -f to set the frequency.\n");
	}
	return 0;
}
