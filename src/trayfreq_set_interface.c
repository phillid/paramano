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

#include "trayfreq_set_interface.h"
#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>

void si_gov(char* gov, int core)
{
  char corestr[4];
  sprintf(corestr, "%i", core);

  gchar* cmd = g_strconcat(util_get_prefix(), "/bin/trayfreq-set -g ", gov, " -c ", corestr,  NULL);
  system(cmd);
  g_free(cmd);
}

void si_freq(int freq, int core)
{
  char corestr[4];
  sprintf(corestr, "%i", core);

  char freqstr[13];
  sprintf(freqstr, "%i", freq);

  gchar* cmd = g_strconcat(util_get_prefix(), "/bin/trayfreq-set -f ", freqstr, " -c ", corestr,  NULL);
  system(cmd);
  g_free(cmd);
}
