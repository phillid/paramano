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

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "debug.h"
#include <glib.h>

struct config_file
{
	GKeyFile* key_file;
	gchar* file_name;
};

gboolean config_open(struct config_file* config_file);
void     config_close(struct config_file* config_file);
gchar*   config_get_key(struct config_file* config_file, const gchar* group_name, const gchar* key_name);

#endif /* ifndef CONFIG_FILE_H */
