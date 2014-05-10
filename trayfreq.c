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

#include "trayfreq.h"

void config_init()
{
	struct config_file config;
	FILE* fd = NULL;
	gboolean home_config_exists;
	config.key_file = NULL;

	config.file_name = g_strconcat(getenv("HOME"), "/.trayfreq.conf", NULL);


	// Check if ~/.trayfreq.config exists
	if( (fd = fopen(config.file_name, "r")) )
	{
		// If file exists, close it, set param to TRUE
		debug("Found '%s'\n",config.file_name);
		fclose(fd);
		home_config_exists = TRUE;
	} else {
		// If file didn't exist, it's not open (don't close it), free filename var, set param to FALSE
		debug("Didn't find '%s'\n",config.file_name);
		g_free(config.file_name);
		home_config_exists = FALSE;
    }

	if(!home_config_exists)
		config.file_name = g_strconcat("/usr/share/trayfreq/trayfreq.conf", NULL);

	gboolean success = config_open(&config);
	if(!success)
	{
		debug("Couldn't open '%s' for reading\n",config.file_name);
		g_warning(_("Failed to open config files!\n"));
		return;
	}

	// Reset defaults to default values
	defaults_init();

	_DEFAULT_GOV		= config_get_key(&config, "governor", "default");
	_DEFAULT_FREQ		= config_get_key(&config, "frequency", "default");
	_DEFAULT_BAT_GOV	= config_get_key(&config, "battery", "governor");
	_DEFAULT_AC_GOV		= config_get_key(&config, "ac", "governor");

	char* temp = config_get_key(&config, "battery", "show");
	if (temp)
		_DEFAULT_SHOW_BATTERY = ( temp[0] == '1' );
	
	temp = config_get_key(&config, "extra", "sudo");
	if (temp)
	{
		_DEFAULT_USE_SUDO = ( temp[0] == '1' );
		debug("woo\n");
	}
	

	debug("%s sudo\n",_DEFAULT_USE_SUDO? "Using" : "Not using");

	g_free(config.file_name);
	config_close(&config);
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	bindtextdomain("trayfreq","/usr/share/locale");
	textdomain("trayfreq");
	debug("Set gettext up\n");

	if(!gtk_init_check(&argc, &argv))
	{
		debug("Couldn't start gtk\n");
		g_error( _("GTK Error: gtk_init_check returned FALSE.\nBailing.") );
		return 1;
	}

	struct sigaction sig_act;
	sig_act.sa_handler = reload_config;
	sig_act.sa_flags = 0;
	sigemptyset(&sig_act.sa_mask);

	if (sigaction(SIGUSR1, &sig_act, NULL) == -1)
	{
		debug("WARN: Couldn't set sigaction for SIGUSR1\n");
	}
	config_init();
	gc_init();
	gg_init();
	gf_init();
	tray_init();
	tray_show();

	// Show battery tray only if we're supposed to
	if(_DEFAULT_SHOW_BATTERY)
	{
		debug("Showing battery info this time around\n");
		bat_tray_init();
		bat_tray_show();
	}

	debug("Passing control to Gtk\n");

	gtk_main();
	debug("Exiting main()\n");
	return 0;
}
