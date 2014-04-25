/************************************************************************
 * This file is part of trayfreq-archlinux.                             *
 *                                                                      *
 * trayfreq-archlinux is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public Licence as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * Licence, or (at your option) any later version.                      *
 *                                                                      *
 * trayfreq-archlinux is distributed in the hope that it will be useful,*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public Licence for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public Licence    *
 * along with trayfreq-archlinux. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../strings.h"
#include "../freq_tray/getfreq.h"
#include "../freq_tray/getcore.h"

char file_path[100];


void prepare_path(const char* file, const char* core)
{
	// Sanatise core to make sure there's not monkey business going on -- it's only an integer
	int core_i = atoi(core);

	sprintf(file_path, "/sys/devices/system/cpu/cpu%d/cpufreq/%s", core_i, file);
}

void file_open_error()
{
	printf(S_TRAYFREQ_SET_C_FILE_OPEN_ERROR, file_path);
}

void set_freq_max(const char* freq, const char* core)
{

	prepare_path("scaling_max_freq",core);
	FILE* fd = fopen(file_path, "w");
	if (fd)
	{
		fprintf(fd, freq);
		fclose(fd);
	} else {
		file_open_error();
	}
}

void set_freq_min(char* freq, char* core)
{
	prepare_path("scaling_min_freq",core);

	FILE* fd = fopen(file_path, "w");
	if (fd)
	{
		fprintf(fd, freq);
		fclose(fd);
	} else {
		file_open_error();
	}
}

static void set_speed(char* freq, char* core)
{
	prepare_path("scaling_setspeed",core);

	FILE* fd = fopen(file_path, "w");
	if (fd)
	{
		fprintf(fd, freq);
		fclose(fd);
	} else {
		file_open_error();
	}
}

void set_gov(char* gov, char* core)
{
	prepare_path("scaling_governor",core);

	FILE* fd = fopen(file_path, "w");
	if (fd)
	{
		fprintf(fd, gov);
		fclose(fd);
	} else {
		file_open_error();
	}
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
		printf(S_TRAYFREQ_SET_C_NO_ARGS);
	} else if(strcmp(argv[1], "-g") == 0) {
		if(!argv[2])
			printf(S_TRAYFREQ_SET_C_SET_GOVERNOR_ARG);
		else
		{
			if(!argv[3])
				printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
			else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
				else
					set_gov(argv[2], argv[4]);
			} else
				printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
		}
	} else if(strcmp(argv[1], "-f") == 0) {
		if(!argv[2])
		{
			printf(S_TRAYFREQ_SET_C_SET_FREQUENCY_ARG);
		} else {
			if(!argv[3])
			{
				printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
			} else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
				else
					set_freq(argv[2], argv[4]);
			} else {
				printf(S_TRAYFREQ_SET_C_SET_CORE_ARG);
			}
		}
	} else {
		printf(S_TRAYFREQ_SET_C_NO_ARGS);
	}
	return 0;
}