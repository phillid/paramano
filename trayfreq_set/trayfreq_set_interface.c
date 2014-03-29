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

#include "trayfreq_set_interface.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void si_gov(char* gov, int core)
{
	char corestr[4];
	sprintf(corestr, "%i", core);

	char* cmd = g_strconcat("/usr/bin/trayfreq-set -g ", gov, " -c ", corestr,  NULL);
	system(cmd);
	g_free(cmd);
}

void si_freq(int freq, int core)
{
	char corestr[4];
	char freqstr[13];

	sprintf(corestr, "%i", core);
	sprintf(freqstr, "%i", freq);

	char* cmd = g_strconcat("/usr/bin/trayfreq-set -f ", freqstr, " -c ", corestr,  NULL);
	system(cmd);
	g_free(cmd);
}