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

#include "widget_manager.h"
#include "tray.h"
#include "bat_tray.h"
#include "getfreq.h"
#include "getcore.h"
#include "getbat.h"
#include "utilities.h"
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
	gboolean home_config_exists = TRUE;
	config.key_file = NULL;

	gchar* home = getenv("HOME");
	config.file_name = g_strconcat(home, "/.trayfreq.config", NULL);
	FILE* fd = fopen(config.file_name, "r");
	if(!fd)
	{
		g_free(config.file_name);
		home_config_exists = FALSE;
	} else {
		fclose(fd);
    }

	if(!home_config_exists)
		config.file_name = g_strconcat(util_get_prefix(), "/share/trayfreq/trayfreq.config", NULL);

	gboolean success = config_open(&config);

	if(!success)
	{
		g_warning("Unsuccessful opening configuration files");
		return;
	}

	gchar * def_prog = config_get_key(&config, "events", "activate");
	gchar * def_gov = config_get_key(&config, "governor", "default");
	gchar * def_freq = config_get_key(&config, "frequency", "default");
	gchar * show_bat = config_get_key(&config, "battery", "show");
	gchar * bat_gov = config_get_key (&config, "battery", "governor");
	gchar * ac_gov = config_get_key (&config, "ac", "governor");

	if(def_prog)
		def_set_prog(def_prog);

	if(def_gov)
		def_set_gov(def_gov);

	if(def_freq)
		def_set_freq(def_freq);

	if (bat_gov)
		def_set_bat_gov (bat_gov);

	if (ac_gov)
		def_set_ac_gov (ac_gov);

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
	gboolean gtk_init_success = gtk_init_check(&argc, &argv);

	if(!gtk_init_success)
	{
		g_error("I was unable to initialize gtk.  gtk_init_check returned FALSE.");
	}

	config_init();
	gc_init();
	gg_init();
	gf_init();
	tray_init();
	tray_show();

	if(gb_init() && SHOW_BATTERY)
	{
		bat_tray_init();
		bat_tray_show();
	}

	gtk_main();
	return 0;
}


