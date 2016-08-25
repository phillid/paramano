#include "paramano_set_interface.h"
#include "common.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void si_gov(char* gov, int core)
{
	char cmd[1024];
	if (getuid() != ROOT_UID)
	{
		sprintf(cmd, SUDO" -n "PARAMANO_SET" -g %s -c %i &",gov,core);
	} else {
		sprintf(cmd, PARAMANO_SET" -g %s -c %i",gov,core);
	}
	info("Running '%s'\n",cmd);
	system(cmd);
}

void si_freq(int freq, int core)
{
	char cmd[1024];
	if (getuid() != ROOT_UID)
	{
		sprintf(cmd, SUDO" -n "PARAMANO_SET" -f %i -c %i &",freq,core);
	} else {
		sprintf(cmd, PARAMANO_SET" -f %i -c %i",freq,core);
	}
	info("Running '%s'\n",cmd);
	system(cmd);
}
