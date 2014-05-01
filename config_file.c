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

#include "config_file.h"

gboolean config_open(struct config_file* config_file)
{
	if(config_file->key_file)
	{
		debug("Freeing config_file->keyfile\n");
		g_key_file_free(config_file->key_file);
	}

	debug("Creating new config_file->key_file\n");
	config_file->key_file = g_key_file_new();

	return g_key_file_load_from_file(	config_file->key_file,
										config_file->file_name,
										G_KEY_FILE_NONE, 
										NULL);
}

void config_close(struct config_file* config_file)
{
	debug("Freeing key_file with %s value\n",config_file->key_file == NULL? "NULL":"non-NULL");
	g_key_file_free(config_file->key_file);
}

gchar* config_get_key(struct config_file* config_file, const gchar* group_name, const gchar* key_name)
{
	return g_key_file_get_value(config_file->key_file,
								group_name,
								key_name,
								NULL);
}
