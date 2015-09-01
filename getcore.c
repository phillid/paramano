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
	while(core_exists(cores))
		cores++;
}


/***********************************************************************
 * Return number of cores
 **********************************************************************/
unsigned int gc_number()
{
	return cores;
}
