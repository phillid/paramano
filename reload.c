/************************************************************************
 * This file is part of paramano.                                       *
 *                                                                      *
 * paramano is free software; you can redistribute it and/or            *
 * modify it under the terms of the GNU General Public License as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * License, or (at your option) any later version.                      *
 *                                                                      *
 * paramano is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with paramano. If not, see                                     *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/

#include "reload.h"
#include "bat_tray.h"
#include "tray.h"
#include "paramano.h"
#include "defaults.h"
#include "common.h"
#include <stdio.h>


/***********************************************************************
 * Catches the USR1 sig. Reloads the configuration files and applies any
 * new changes/config etc
 ************************************************************************/
void reload_config()
{
	debug("Reloading config\n");

	// Reload config
	config_init();

	// Hide battery icon if told to
	_DEFAULT_SHOW_BATTERY? bat_tray_show() : bat_tray_hide();

	// Update governor and frequency defaults
	debug("Re-init freq tray\n");
	tray_set_defaults();
}
