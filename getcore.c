#include "getcore.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static unsigned int cores;

/***********************************************************************
 * Return true/false if specified core num exists
 **********************************************************************/
bool core_exists(unsigned int core)
{
	char path[1024];
	int result;
	snprintf(path, sizeof(path), "/sys/devices/system/cpu/cpu%d/cpufreq", core);
	result = access(path, F_OK);
	return (result != -1);
}


/***********************************************************************
 * Initialise surrounding variables
 **********************************************************************/
void gc_init()
{
	cores = 0;
	while (core_exists(cores))
		cores++;
}


/***********************************************************************
 * Return number of cores
 **********************************************************************/
unsigned int gc_number()
{
	return cores;
}
