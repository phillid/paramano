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

#include "utilities.h"

gint util_compare_gdouble(gdouble a, gdouble b)
{
	gdouble diff = a - b;
	if(diff < .0001)
	return 0;
	else if(diff > 0)
		return 1;
	else
		return -1;
}

const gchar* util_get_prefix()
{
	if(g_strcmp0(PREFIX, "NONE") == 0)
		return "/usr/local";
	else
		return PREFIX;
}
