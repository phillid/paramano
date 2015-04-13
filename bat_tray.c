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
 * Return number of seconds until battery is fully charged/discharged
 **********************************************************************/
int get_bat_seconds_left()
{
	int charge_now, charge_full, current_now;
	char* file;

	// Read current current value
	asprintf(&file, POWERDIR"BAT%d/current_now",bat_num);
	current_now = get_int_value_from_file(file);
	free(file);

	// Return -1 if zero current (infinite charge time)
	if (current_now == 0)
		return -1;

	asprintf(&file, POWERDIR"BAT%d/charge_now",bat_num);
	charge_now = get_int_value_from_file(file);
	free(file);

	if (charge_now == -1 || current_now == -1)
	{
		return -1;
	}

	switch(get_battery_state())
	{
		case STATE_CHARGING:
			// We need to know full charge to calculate this one
			asprintf(&file, POWERDIR"BAT%d/charge_full",bat_num);
			charge_full = get_int_value_from_file(file);
			free(file);

			return (3600*(charge_full - charge_now))/current_now;
			break;
		case STATE_DISCHARGING:
			return (3600*charge_now)/current_now;
			break;
		default:
			return -1;
	}
}


/***********************************************************************
 * Updates the battery tray tooltip text
 **********************************************************************/
static gboolean update_tooltip(GtkStatusIcon* status_icon,gint x,gint y,gboolean keyboard_mode,GtkTooltip* tooltip,gpointer data)
{
	char* msg;
	int seconds_left = get_bat_seconds_left();

	char* time_left;

	if (seconds_left == -1)
	{
		asprintf(&time_left, _("Unknown time left"));
	} else {
		asprintf(&time_left, _("%02d:%02d:%02d left"), (int)(seconds_left/3600), (int)((seconds_left%3600)/60), seconds_left%60);
	}

	switch(get_battery_state())
	{
		case STATE_DISCHARGING:
			debug("Discharging\n");
			asprintf(&msg, _("Discharging (%d%%)\n%s"), get_bat_percent(), time_left);
			break;

		case STATE_CHARGING:
			debug("Charging\n");
			asprintf(&msg, _("Charging (%d%%)\n%s"), get_bat_percent(), time_left);
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

	free(time_left);
	free(msg);

	return true;
}


/***********************************************************************
 * Updates the battery tray icon based upon battery percent
 **********************************************************************/
static gboolean update_icon(gpointer user_data)
{
	char *icon_file;
	unsigned int rounded;

	rounded = 20* (int)((get_bat_percent()+10)/20); // Round percentage to 0, 20, 40, 60, 80 or 100

	debug("Rounded/adjusted percentage: %d\n",rounded);

	switch ( get_battery_state() )
	{
		case STATE_DISCHARGING:
			asprintf(&icon_file,"%s/bat-%d.png",DEFAULT_THEME,rounded);
			break;

		case STATE_CHARGING:
			asprintf(&icon_file,"%s/bat-%d-charging.png",DEFAULT_THEME,rounded);
			break;

		default:
			asprintf(&icon_file,"%s/bat-charged.png",DEFAULT_THEME);
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
	asprintf(&icon_file,"%s/bat-charged.png",DEFAULT_THEME);
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
		if( (fd = check_for_file(file)) )
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
