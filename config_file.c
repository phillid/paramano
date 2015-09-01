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

#include "paramano.h"

gboolean config_open(struct config_file* config_file)
{
	if(config_file->key_file)
		g_key_file_free(config_file->key_file);

	config_file->key_file = g_key_file_new();
	gboolean success = g_key_file_load_from_file(
										config_file->key_file,
										config_file->file_name,
										G_KEY_FILE_NONE,
										NULL);
	return success;
}

void config_close(struct config_file* config_file)
{
	g_key_file_free(config_file->key_file);
}

gchar* config_get_key(struct config_file* config_file, const gchar* group_name, const gchar* key_name)
{
	return g_key_file_get_value(config_file->key_file,
								group_name,
								key_name,
								NULL);
}
