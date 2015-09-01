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


#include "paramano.h"

#define set_freq_max(freq, core)	write_str_to_file("scaling_max_freq", freq, core)
#define set_freq_min(freq, core)	write_str_to_file("scaling_min_freq", freq, core)
#define set_speed(freq, core)		write_str_to_file("scaling_setspeed", freq, core)
#define set_gov(gov, core)			write_str_to_file("scaling_governor", gov, core)

void die_syntax(const char *prefix);
char write_str_to_file(const char *file, const char *data, int core);

int main(int argc, char *argv[])
{
	char c = 0;
	int core = -1;
	char *frequency = NULL;
	char *governor = NULL;

	setlocale(LC_ALL, "");
	bindtextdomain("paramano", LOCALEDIR);
	textdomain("paramano");

	if (getuid() != 0)
		fprintf(stderr, "Warning: running as UID %d, not 0\n", getuid());

	while ((c = getopt(argc, argv, "c:f:g:")) != -1)
	{
		switch (c)
		{
			case 'c':
				core = atoi(optarg);
				break;
			case 'f':
				frequency = optarg;
				break;
			case 'g':
				governor = optarg;
				break;
			default:
				die_syntax(argv[0]);
				break;
		}
	}

	if (core < 0 ||
	   (governor == NULL && frequency == NULL) ||
	   (governor != NULL && frequency != NULL))
		die_syntax(argv[0]);

	if (governor != NULL)
		return set_gov(governor, core);

	if (frequency != NULL)
		return set_gov("userspace", core) | set_speed(frequency, core);

	return 1;
}

void die_syntax(const char *prefix)
{
	fprintf(stderr, _("%s {-f frequency|-g governor} -c core\n"), prefix);
	exit(1);
}

char write_str_to_file(const char *file, const char *data, int core)
{
	FILE *fd = NULL;
	char file_path[1024];

	/* Prepare file path */
	snprintf(file_path, sizeof(file_path), "/sys/devices/system/cpu/cpu%d/cpufreq/%s", core, file);

	/* Try to open file and write data to it */
	if ( (fd = fopen(file_path, "w")) != NULL )
	{
		fputs(data, fd);
		fclose(fd);
		return 1;
	}

	/* Fallthrough: File couldn't be opened for writing */
	fprintf(stderr, _("FAILED: Couldn't open %s for writing\n") , file_path);
	return 0;
}


