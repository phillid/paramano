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

#include "getcore.h"

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

unsigned int cores;


/***********************************************************************
 * Return true/false if specified core num exists
 **********************************************************************/
bool core_exists(unsigned int core)
{
	char* path;
	int result;
	asprintf(&path, "/sys/devices/system/cpu/cpu%d/cpufreq", core);
	debug("Checking if core %d exists by opening '%s'\n",core,path);
	result = access(path, F_OK);
	free (path);
	return (result != -1); 
}


/***********************************************************************
 * Initialise surrounding variables
 **********************************************************************/
void gc_init()
{
	cores = 0;
	while(core_exists(cores))
		cores++;

	debug("Found %d cores\n",cores);
}


/***********************************************************************
 * Return number of cores
 **********************************************************************/
int gc_number()
{
	return cores;
}
