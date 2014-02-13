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

#ifndef GETBAT_H
#define GETBAT_H 1

#include <glib.h>

gboolean gb_init();
gint gb_current_capacity();
gint gb_current_rate();
gboolean gb_discharging();
gboolean gb_charged();
gboolean gb_charging();
gint gb_number();
gint gb_max_capacity();
gint gb_warn_capacity();
gint gb_low_capacity();
gint gb_percent();
void gb_discharge_time(gchar* time);
void gb_charge_time(gchar* time);

#endif