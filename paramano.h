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

#ifndef PARAMANO_H
#define PARAMANO_H

#define POWERDIR "/sys/class/power_supply/"

#include <gtk/gtk.h>
#include <unistd.h>		// getuid, getgid
#include <stdio.h>		// printf, FILE, fopen, etc
#include <stdlib.h>		// free etc
#include <stdbool.h>	// boolean types
#include <string.h>		// strlen
#include <libintl.h>	// gettext
#include <locale.h>		// LC_ALL etc

#include "tray.h"
#include "bat_tray.h"
#include "getfreq.h"
#include "getcore.h"
#include "getgov.h"
#include "config_file.h"
#include "defaults.h"
#include "common.h"
#include "paramano_set_interface.h"

void config_init();

#endif
