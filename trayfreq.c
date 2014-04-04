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

#include "widget_manager.h"
#include "tray.h"
#include "bat_tray/bat_tray.h"
#include "freq_tray/getfreq.h"
#include "freq_tray/getcore.h"
#include "freq_tray/getgov.h"
#include "config_file.h"
#include "defaults.h"

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

static gboolean SHOW_BATTERY = TRUE;

void config_init()
{
	struct config_file config;
	FILE* fd = NULL;
	gboolean home_config_exists;
	config.key_file = NULL;

	printf("Battery governor: %s",_DEFAULT_BAT_GOV);

	config.file_name = g_strconcat(getenv("HOME"), "/.trayfreq.config", NULL);

	// Check if ~/.trayfreq.config exists
	if( (fd = fopen(config.file_name, "r")) )
	{
		// If file exists, close it, set param to TRUE
		fclose(fd);
		home_config_exists = TRUE;
	} else {
		// If file didn't exist, it's not open (don't close it), free filename var, set param to FALSE
		g_free(config.file_name);
		home_config_exists = FALSE;
    }

	if(!home_config_exists)
		config.file_name = g_strconcat("/usr/share/trayfreq/trayfreq.config", NULL);

	gboolean success = config_open(&config);

	if(!success)
	{
		g_warning("Failed to open config files!\n");
		return;
	}

	gchar * def_prog = config_get_key(&config, "events", "activate");
	gchar * def_gov = config_get_key(&config, "governor", "default");
	gchar * def_freq = config_get_key(&config, "frequency", "default");
	gchar * show_bat = config_get_key(&config, "battery", "show");
	gchar * bat_gov = config_get_key (&config, "battery", "governor");
	gchar * ac_gov = config_get_key (&config, "ac", "governor");

	if(def_prog)
		_DEFAULT_PROG = def_prog;

	if(def_gov)
		_DEFAULT_GOV = def_gov;

	if(def_freq)
		_DEFAULT_FREQ = def_freq;

	if (bat_gov)
		_DEFAULT_BAT_GOV = bat_gov;

	if (ac_gov)
		_DEFAULT_AC_GOV = ac_gov;

	if(show_bat)
	{
		if(g_strcmp0(show_bat, "1") == 0)
			SHOW_BATTERY = TRUE;
		else
			SHOW_BATTERY = FALSE;
	}
	g_free(config.file_name);
	config_close(&config);
}

int main(int argc, char** argv)
{
	//gboolean gtk_init_success = gtk_init_check(&argc, &argv);

	if(!gtk_init_check(&argc, &argv))
	{
		g_error("Cannot initialize gtk: gtk_init_check returned FALSE.\nBailing.");
		return 1;
	}

	config_init();
	gc_init();
	gg_init();
	gf_init();
	tray_init();
	tray_show();

	// Show battery tray only if we're supposed to
	if(SHOW_BATTERY)
	{
		bat_tray_init();
		bat_tray_show();
	}

	gtk_main();
	return 0;
}