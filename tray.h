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

#ifndef TRAY_H
#define TRAY_H

#include <glib.h>

#include "widget_manager.h"
#include "getfreq.h"
#include "getcore.h"
#include "getgov.h"
#include "trayfreq_set_interface.h"
#include "bat_tray.h"
#include "defaults.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>


void     tray_set_defaults();
void     tray_init();
void     tray_set_tooltip(const gchar* msg);
void     tray_update_icon_percent();
void     tray_show();
void     tray_hide();
gboolean tray_visible();
gboolean tray_embedded();

#endif
