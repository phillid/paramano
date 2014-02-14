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

#include "defaults.h"

gchar* default_gov = NULL;
gchar* default_freq = NULL;
gchar* default_prog = NULL;
gchar* default_bat_gov = NULL;
gchar* default_ac_gov = NULL;

gchar* def_get_gov()
{
	return default_gov;
}

gchar* def_get_freq()
{
	return default_freq;
}

gchar* def_get_prog()
{
	return default_prog;
}

gchar* def_get_bat_gov()
{
	return default_bat_gov;
}

gchar* def_get_ac_gov()
{
	return default_ac_gov;
}

void def_set_gov(gchar* gov)
{
	default_gov = g_strdup(gov);
}

void def_set_freq(gchar* freq)
{
	default_freq = g_strdup(freq);
}

void def_set_prog(gchar* prog)
{
	default_prog = g_strdup(prog);
}

void def_set_bat_gov(gchar* bat_gov)
{
	default_bat_gov = bat_gov;
}

void def_set_ac_gov(gchar* ac_gov)
{
	default_ac_gov = ac_gov;
}