#include "getgov.h"
#include "getcore.h"
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <glib.h>

/* [CORE][GOVERNOR NUMBER] */
static char governors[999][50][13];
static int total_governors;

/***********************************************************************
 * Grab all available governors
 **********************************************************************/
void gg_init()
{
	char gov_string[500];
	unsigned int i = 0;
	total_governors = 0;

	for (i = 0; i < 1/*gc_number()*/; i++)
	{
		memset(gov_string, '\0', sizeof(gov_string) );
		gg_available(i, gov_string, sizeof(gov_string) );

		char* curr = gov_string;
		char* end_of_curr = g_strstr_len(curr, strlen(curr), " ");
		while (end_of_curr)
		{
			memset(governors[i][total_governors], '\0', 13); /* FIXME magic */
			memmove(governors[i][total_governors], curr, end_of_curr - curr);

			curr = end_of_curr+1;
			end_of_curr = g_strstr_len(curr, strlen(curr), " ");
			total_governors++;
		}
	}
}


/***********************************************************************
 * Populate out with current governor for core
 **********************************************************************/
bool gg_current(int core, char* out, int size)
{
	FILE* fd = NULL;
	char path[1024];

	snprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_governor", core);

	if (!(fd = fopen(path, "r")))
		return false;

	fgets(out, size, fd);
	fclose(fd);
	chomp(out);
	return true;
}


/***********************************************************************
 * Populate `out` with number of available cores
 **********************************************************************/
bool gg_available(int core, char* out, int size)
{
	FILE *fd = NULL;
	char path[1024];

	snprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_available_governors", core);

	if (!(fd = fopen(path, "r")))
		return false;

	fgets(out, size, fd);
	fclose(fd);
	return true;
}


/***********************************************************************
 * Return pointer to name of gov
 **********************************************************************/
char* gg_gov(int core, int index)
{
	return governors[core][index];
}

/***********************************************************************
 * Return total number of governors
 **********************************************************************/
unsigned int gg_number()
{
	return total_governors;
}
