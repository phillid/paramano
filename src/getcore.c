/************************************************************************
 * This file is part of trayfreq.                                       *
 *                                                                      *
 * trayfreq is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published    *
 * by the Free Software Foundation; either version 3 of the License, or *
 * (at your option) any later version.                                  *
 *                                                                      *
 * trayfreq is distributed in the hope that it will be useful,	        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with trayfreq. If not, see <http://www.gnu.org/licenses/>.     *
 ************************************************************************/

#include "getcore.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int NUMBER_OF_CORES;

static gboolean core_exists(int core)
{
  FILE* fd;
  char path[80];
  char corestr[4];

  sprintf(corestr, "%i", core);

  sprintf(path, "/sys/devices/system/cpu/cpu%s/cpufreq/scaling_cur_freq", corestr);

  if(!(fd = fopen(path, "r")))
    return FALSE;

  return TRUE;
}

void gc_init()
{
  NUMBER_OF_CORES = 0;
  while(core_exists(NUMBER_OF_CORES))
    ++NUMBER_OF_CORES;
}

int gc_number()
{
  return NUMBER_OF_CORES;
}
