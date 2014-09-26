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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libintl.h>
#include <locale.h>

#include "getfreq.h"
#include "getcore.h"
#include "common.h"

#define FILE_PATH_STRING_SIZE 100

#define ARG_CORE	0x1
#define ARG_GOV		0x2
#define ARG_FREQ	0x4
typedef struct  {
	char present;
	char *core;
	char *governor;
	char *frequency;
} argument_summary;

char write_str_to_file(const char *file, const char *data, const char *core)
{
	FILE *fd;
	char file_path[FILE_PATH_STRING_SIZE];

	// Prepare file path
	memset(file_path, '\0', sizeof(file_path));
	sprintf(file_path, "/sys/devices/system/cpu/cpu%d/cpufreq/%s", atoi(core), file );

	// Try to open file and write data to it
	if ( (fd = fopen(file_path, "w")) != NULL )
	{
		debug("Writing '%s' to '%s'\n",data,file_path);
		fprintf(fd, data);
		fclose(fd);
		return 1;
	}

	// Fallthrough: File couldn't be opened for writing
	fprintf(stderr, _("FAILED: Couldn't open %s for writing\n") , file_path);
	return 0;
}


#define set_freq_max(freq,core)		write_str_to_file("scaling_max_freq",freq,core)
#define set_freq_min(freq,core)		write_str_to_file("scaling_min_freq",freq,core)
#define set_speed(freq,core)		write_str_to_file("scaling_setspeed",freq,core)
#define set_gov(gov,core)			write_str_to_file("scaling_governor",gov,core)

void get_argument_summary(int argc, char **argv, argument_summary *argsum)
{
	int arg;

	// Check for -{c,g,f} xyz
	for ( arg = 1; arg < argc-1; arg+=2 )
	{
		// Can't have empty argument
		if ( strlen(argv[arg+1]) != 0 )
		{
			if ( strcmp(argv[arg], "-c") == 0 )
			{
				// Found -c with an arg
				debug("Found -c with arg '%s'\n",argv[arg+1]);
				argsum->present |= ARG_CORE;
				argsum->core = (char*)(argv[arg+1]);
				continue;
			}

			if ( strcmp(argv[arg], "-f") == 0 )
			{
				// Found -f with an arg
				debug("Found -f with arg '%s'\n",argv[arg+1]);
				argsum->present |= ARG_FREQ;
				argsum->frequency = (char*)(argv[arg+1]);
				continue;
			}

			if ( strcmp(argv[arg], "-g") == 0 )
			{
				// Found -g with an arg
				debug("Found -g with arg '%s'\n",argv[arg+1]);
				argsum->present |= ARG_GOV;
				argsum->governor = (char*)(argv[arg+1]);
				//continue;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL,"");
	bindtextdomain("paramano",LOCALEDIR);
	textdomain("paramano");

	debug("Set gettext up\n");

	gc_init();
	gf_init();

	argument_summary args;
	memset(&args, 0, sizeof(args));

	// If unusual number of args, give up now
	if (argc == 5)
	{

		debug ("Checking UID\n");
		if (getuid() != 0)
			fprintf(stderr,"Warning: running as UID %d, not 0\n",getuid() );

		get_argument_summary(argc, argv, &args);

		debug("Correct number of command line arguments\n");
		debug("-c: %s  -g: %s  -f: %s\n",	(args.present | ARG_CORE )? "Yes":"No",
											(args.present | ARG_GOV  )? "Yes":"No",
											(args.present | ARG_FREQ )? "Yes":"No" );
		debug("Core: %s\n",args.core);
		debug("Gov : %s\n",args.governor);
		debug("Freq: %s\n",args.frequency);

		if ( args.present == ( ARG_CORE | ARG_GOV ) )
		{
			debug("Changing governor\n");
			return set_gov(args.governor , args.core);
		}

		if ( args.present == ( ARG_CORE | ARG_FREQ ) )
		{
			debug("Changing frequency\n");
			return set_gov("userspace", args.core) | set_speed(args.frequency, args.core);
		}
	}
	// Fall through to here if no valid argument combination
	debug("Fell through, showing command usage\n");
	fprintf(stderr, _("%s {-f frequency|-g governor} -c core\n"), argv[0] );
	return 1;
}
