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

#include "config_file.h"
#include "defaults.h"

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <libintl.h>
#include <string.h>

void config_init()
{
	struct config_file config;
	char *xdg_config_home = NULL;
	char config_home[1024];

	config.key_file = NULL;
	
	/* Default to $HOME/.config/paramano.conf as specified in the XDG
	 * Base Directory Standard :
	 * <http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html>
	 */
	xdg_config_home = getenv("XDG_CONFIG_HOME");

	/* FIXME: unchecked return values from snprintf */
	if (xdg_config_home == NULL)
		snprintf(config_home, sizeof(config_home), "%s/.config", getenv("HOME"));
	else
		strncpy(config_home, xdg_config_home, sizeof(config_home));

	snprintf(config.file_name, sizeof(config.file_name), "%s/paramano.conf", config_home);

	if (access(config.file_name, R_OK) == -1)
		strncpy(config.file_name, PARAMANO_CONF, sizeof(config.file_name)); /* fallback to system-wide */

	if (!config_open(&config))
	{
		g_warning(_("Failed to open config files!\n"));
		return;
	}

	/* Reset defaults to default values */
	defaults_init();

	DEFAULT_GOV			= config_get_key(&config, "governor", "default");
	DEFAULT_FREQ		= config_get_key(&config, "frequency", "default");
	DEFAULT_BAT_GOV		= config_get_key(&config, "battery", "governor");
	DEFAULT_AC_GOV		= config_get_key(&config, "ac", "governor");

	char* temp;
	if ((temp = config_get_key(&config, "battery", "show")))
		DEFAULT_SHOW_BATTERY = ( temp[0] == '1' );

	if ((temp = config_get_key(&config, "extra", "theme")))
		strncpy(DEFAULT_THEME, temp, sizeof(DEFAULT_THEME));

	config_close(&config);
}

gboolean config_open(struct config_file* config_file)
{
	if (config_file->key_file)
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
