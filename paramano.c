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


/***********************************************************************
 * Main
 **********************************************************************/
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	bindtextdomain("paramano",LOCALEDIR);
	textdomain("paramano");

	if (!gtk_init_check(&argc, &argv))
	{
		g_error( _("GTK Error: gtk_init_check returned FALSE.\nBailing.") );
		return 1;
	}

	config_init();
	gc_init();
	gg_init();
	gf_init();
	tray_init();
	tray_show();

	/* Show battery tray only if we're supposed to */
	if (DEFAULT_SHOW_BATTERY)
	{
		bat_tray_init();
		bat_tray_show();
	}

	gtk_main();
	return 0;
}


/***********************************************************************
 * Load config
 **********************************************************************/
void config_init()
{
	struct config_file config;
	FILE* fd = NULL;
	bool home_config_exists = false;

	config.key_file = NULL;
	config.file_name = g_strconcat(getenv("HOME"), "/.paramano.conf", NULL);


	/* Check if ~/.paramano.conf exists */
	if( (fd = fopen(config.file_name, "r")) )
	{
		/* If file exists, close it, set param to true */
		fclose(fd);
		home_config_exists = true;
	} else {
		/* If file didn't exist, it's not open (don't close it), free filename var, set param to false */
		g_free(config.file_name);
		home_config_exists = false;
	}

	if(!home_config_exists)
		config.file_name = g_strconcat(PARAMANO_CONF, NULL);

	gboolean success = config_open(&config);
	if(!success)
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

	info("UID: %d   GID: %d\n", getuid(), getgid());

	if ((temp = config_get_key(&config, "extra", "theme")))
		snprintf(DEFAULT_THEME, sizeof(DEFAULT_THEME), "%s", temp);

//	g_free(config.file_name);
	config_close(&config);
}

