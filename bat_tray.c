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


#include "bat_tray.h"

#include <gtk/gtk.h>
#include <libintl.h>
#include <stdio.h>
#include "common.h"
#include "defaults.h"


static GtkStatusIcon* tray;

int bat_num; // Shortcoming: we only detect one battery
char *CHARGE_VALUE_PATH, *CHARGE_STATE_PATH;

/***********************************************************************
 * Return the battery level percentage
 **********************************************************************/
int get_bat_percent()
{
	return get_int_value_from_file(CHARGE_VALUE_PATH);
}


/***********************************************************************
 * Updates the battery tray tooltip text
 **********************************************************************/
static gboolean update_tooltip(GtkStatusIcon* status_icon,gint x,gint y,gboolean keyboard_mode,GtkTooltip* tooltip,gpointer data)
{
	char* msg;

	switch(get_battery_state())
	{
		case STATE_DISCHARGING:
			debug("Discharging\n");
			asprintf(&msg, _("Discharging (%d%%)"), get_bat_percent());
			break;

		case STATE_CHARGING:
			debug("Charging\n");
			asprintf(&msg, _("Charging (%d%%)"), get_bat_percent());
			break;

		case STATE_CHARGED:
			debug("Charged\n");
			asprintf(&msg, _("Fully charged") );
			break;

		default:
			debug("Unknown\n");
			asprintf(&msg, _("Unknown status") );
			break;
	}

	debug("Setting tooltip text to '%s'\n",msg);
	gtk_tooltip_set_text(tooltip, msg);

	free(msg);

	return true;
}


/***********************************************************************
 * Updates the battery tray icon based upon battery percent
 **********************************************************************/
gboolean update_icon(gpointer user_data)
{
	char *icon_file;
	unsigned int rounded;

	rounded = 20* (int)((get_bat_percent()+10)/20); // Round percentage to 0, 20, 40, 60, 80 or 100

	debug("Rounded/adjusted percentage: %d\n",rounded);

	switch ( get_battery_state() )
	{
		case STATE_DISCHARGING:
			asprintf(&icon_file,"%s/bat-%d.png",_DEFAULT_THEME,rounded);
			break;

		case STATE_CHARGING:
			asprintf(&icon_file,"%s/bat-%d-charging.png",_DEFAULT_THEME,rounded);
			break;

		default:
			asprintf(&icon_file,"%s/bat-charged.png",_DEFAULT_THEME);
			break;
	}

	debug("Setting tray icon to '%s'\n",icon_file);
	gtk_status_icon_set_from_file(tray, icon_file);

	free(icon_file);

	return true;
}


/***********************************************************************
 * Initialise the tray and related variables
 **********************************************************************/
void bat_tray_init()
{
	char *icon_file;

	// Get the battery number, store it for later
	bat_num = get_bat_num();

	// Set up battery info filenames/paths
	asprintf(&CHARGE_VALUE_PATH, "/sys/class/power_supply/BAT%d/capacity", bat_num);
	asprintf(&CHARGE_STATE_PATH, "/sys/class/power_supply/BAT%d/status", bat_num);

	debug("Spawning new status icon\n");
	tray = gtk_status_icon_new();
	asprintf(&icon_file,"%s/bat-charged.png",_DEFAULT_THEME);
	gtk_status_icon_set_from_file(tray, icon_file);
	free(icon_file);
	gtk_status_icon_set_has_tooltip (tray, TRUE);
	g_signal_connect(G_OBJECT(tray), "query-tooltip", GTK_SIGNAL_FUNC(update_tooltip), NULL);
	g_timeout_add(5000, update_icon, NULL);
}


/***********************************************************************
 * Free memory allocated in bat_tray_init()
 **********************************************************************/
void bat_tray_end()
{
	free(CHARGE_VALUE_PATH);
	free(CHARGE_STATE_PATH);
}


/***********************************************************************
 * Show the battery tray
 **********************************************************************/
void bat_tray_show()
{
	debug("Showing tray\n");
	gtk_status_icon_set_visible(tray, TRUE);
}


/***********************************************************************
 * Hide the battery tray
 **********************************************************************/
void bat_tray_hide()
{
	debug("Hiding tray\n");
	gtk_status_icon_set_visible(tray, FALSE);
}


/***********************************************************************
 * Return the battery state
 **********************************************************************/
int get_battery_state()
{
	if (file_has_line(CHARGE_STATE_PATH, "Discharging"))
	{
		debug("Battery discharging\n");
		return STATE_DISCHARGING;
	}

	if (file_has_line(CHARGE_STATE_PATH, "Full"))
	{
		debug("Battery full\n");
		return STATE_CHARGED;
	}

	if (file_has_line(CHARGE_STATE_PATH, "Charging"))
	{
		debug("Battery charging\n");
		return STATE_CHARGING;	
	}
	debug("Fallthrough: unknown status\n");
	return STATE_UNKNOWN;
}


/***********************************************************************
 * Get the number of the first (who has more than one?) battery
 * Returns -1 if no battery present
 **********************************************************************/
int get_bat_num()
{
	FILE* fd;
	char* file;
	unsigned int i;
	for(i = 0; i < 10; i++)
	{
		asprintf(&file, "/sys/class/power_supply/BAT%d/present", i);
		debug("Attempting to open '%s'\n",file);
		if( (fd = fopen(file, "r")) )
		{
			debug("Found battery %d\n",i);
			if (fgetc(fd) == '1')
			{
				debug("Battery %d is present\n",i);
				fclose(fd);
				free(file);
				return i;
			}
		}
	}
	debug("Fallthrough: couldn't find battery\n");
	free(file);
	return -1;
}
