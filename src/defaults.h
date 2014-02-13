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

#ifndef DEFAULTS_H
#define DEFAULTS_H 1

#include <glib.h>

gchar* def_get_gov();
gchar* def_get_freq();
gchar* def_get_prog();
gchar* def_get_bat_gov();
gchar* def_get_ac_gov();
void def_set_gov(gchar* gov);
void def_set_freq(gchar* freq);
void def_set_prog(gchar* prog);
void def_set_bat_gov(gchar* bat_gov);
void def_set_ac_gov(gchar* ac_gov);

#endif
