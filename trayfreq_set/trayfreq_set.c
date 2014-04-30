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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "../freq_tray/getfreq.h"
#include "../freq_tray/getcore.h"

char file_path[100];


void prepare_path(const char* file, const char* core)
{
	// Sanatise core to make sure there's not monkey business going on
	int core_i = atoi(core);

	sprintf(file_path, "/sys/devices/system/cpu/cpu%d/cpufreq/%s", core_i, file);
}

void file_open_error()
{
	printf( _("FAILED: Couldn't open %s for writing\n") , file_path);
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
	setlocale(LC_ALL,"");
	bindtextdomain("trayfreq","/usr/share/locale");
	textdomain("trayfreq");

	gc_init();
	gf_init();

	if(!argv[1])
	{
		printf( _("Use -g to set the governor or -f to set the frequency\n") );
	} else if(strcmp(argv[1], "-g") == 0) {
		if(!argv[2])
			printf( _("Pass the governor with -g\n") );
		else
		{
			if(!argv[3])
				printf( _("Pass the core with -c\n") );
			else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf( _("Pass the core with -c\n") );
				else
					set_gov(argv[2], argv[4]);
			} else
				printf( _("Pass the core with -c\n") );
		}
	} else if(strcmp(argv[1], "-f") == 0) {
		if(!argv[2])
		{
			printf( _("Pass the frequency with -f\n") );
		} else {
			if(!argv[3])
			{
				printf( _("Pass the core with -c\n") );
			} else if(strcmp(argv[3], "-c") == 0)
			{
				if(!argv[4])
					printf( _("Pass the core with -c\n") );
				else
					set_freq(argv[2], argv[4]);
			} else {
				printf( _("Pass the core with -c\n") );
			}
		}
	} else {
		printf( _("Use -g to set the governor or -f to set the frequency\n") );
	}
	return 0;
}
