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
