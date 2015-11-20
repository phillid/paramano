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


#include "bat_tray.h"
#include "common.h"
#include "defaults.h"

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <libintl.h>

static GtkStatusIcon* tray;
static char tooltip_text[1024];
static int bat_num; // Shortcoming: we only detect one battery
static char CHARGE_VALUE_PATH[1024];
static char CHARGE_STATE_PATH[1024];

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
long get_bat_seconds_left()
{
	int now = 0;
	int full = 0;
	int rate = 0;

	/* FIXME this now/full/rate logic has probably earned its own function.
	 * Not because of DRY, but just for readability's sake perhaps */

	/* Kernel battery info is reported in one of two formats:
	 *   - charge units
	 *   - energy units
	 * Charge Units      | Energy Units
	 * ------------------+---------------
	 * charge_now (µAh)  | energy_now (µWh)
	 * charge_full (µAh) | energy_full (µWh)
	 * current_now (µA)  | power_now (µW)
	 *
	 * Simple arithmetic produces the desired time value (time to fill, time
	 * to empty).
	 *
	 * If a valid (non-negative) value from energy_now is received, we assume
	 * all values are in energy units and proceed from there. If an invalid
	 * value is received, we assume all values are in charge units etc.
	 */

	/* Attempt to read current ENERGY level */
	now = get_int_value_from_filef(POWERDIR"BAT%d/energy_now", bat_num);

	/* FIXME battery's full charge/energy is only required when charging */
	/* Energy units or charge units */
	if (now >= 0)
	{
		full = get_int_value_from_filef(POWERDIR"BAT%d/energy_full", bat_num);
		rate = get_int_value_from_filef(POWERDIR"BAT%d/power_now", bat_num);
	} else {
		full = get_int_value_from_filef(POWERDIR"BAT%d/charge_full", bat_num);
		now = get_int_value_from_filef(POWERDIR"BAT%d/charge_now", bat_num);
		rate = get_int_value_from_filef(POWERDIR"BAT%d/current_now", bat_num);
	}


	/* Note the '<=' for rate (we divide by rate) */
	if (full < 0 || now < 0 || rate <= 0)
		return -1;

	switch (get_battery_state())
	{
		case STATE_CHARGING:
			return (3600*(long long)(full - now))/rate;
			break;
		case STATE_DISCHARGING:
			return (3600*(long long)now)/rate;
			break;
		default:
			return -1;
	}
}


/***********************************************************************
 * Shows/updates the battery tray tooltip
 **********************************************************************/
static gboolean show_tooltip(GtkStatusIcon* status_icon, gint x, gint y, gboolean keyboard_mode, GtkTooltip* tooltip, gpointer data)
{
	gtk_tooltip_set_text(tooltip, tooltip_text);
	return true;
}

/***********************************************************************
 * Updates the battery tray tooltip's cached text
 **********************************************************************/
static void update_tooltip_cache()
{
	char msg[512];
	char time_left[64];
	int seconds_left = get_bat_seconds_left();

	if (seconds_left < 0)
		snprintf(time_left, sizeof(time_left), _("Unknown time left"));
	else
		snprintf(time_left, sizeof(time_left), _("%02d:%02d left"), (int)(seconds_left/3600), (int)((seconds_left%3600)/60));

	switch (get_battery_state())
	{
		case STATE_DISCHARGING:
			snprintf(msg, sizeof(msg), _("Discharging (%d%%)\n%s"), get_bat_percent(), time_left);
			break;

		case STATE_CHARGING:
			snprintf(msg, sizeof(msg), _("Charging (%d%%)\n%s"), get_bat_percent(), time_left);
			break;

		case STATE_CHARGED:
			snprintf(msg, sizeof(msg), _("Fully charged") );
			break;

		default:
			snprintf(msg, sizeof(msg), _("Unknown status") );
			break;
	}
	strncpy(tooltip_text, msg, sizeof(tooltip_text));
	tooltip_text[sizeof(tooltip_text)-1] = '\0';
}


/***********************************************************************
 * Updates the battery tray icon based upon battery percent
 * Also updates the cached tooltip text
 **********************************************************************/
static gboolean update()
{
	char icon_file[1024];
	unsigned int rounded = 0;

	/* Round percentage to 0, 20, 40, 60, 80 or 100 */
	rounded = 20 * (int)((get_bat_percent() + 10) / 20);

	switch (get_battery_state())
	{
		case STATE_DISCHARGING:
			snprintf(icon_file, sizeof(icon_file), "%s/bat-%d.png", DEFAULT_THEME, rounded);
			break;

		case STATE_CHARGING:
			snprintf(icon_file, sizeof(icon_file), "%s/bat-%d-charging.png", DEFAULT_THEME, rounded);
			break;

		default:
			snprintf(icon_file, sizeof(icon_file), "%s/bat-charged.png", DEFAULT_THEME);
			break;
	}

	update_tooltip_cache();
	gtk_status_icon_set_from_file(tray, icon_file);
	return true;
}


/***********************************************************************
 * Initialise the tray and related variables
 **********************************************************************/
void bat_tray_init()
{
	char icon_file[1024];

	/* Get the battery number, store it for later */
	bat_num = get_bat_num();

	/* Set up battery info filenames/paths */
	snprintf(CHARGE_VALUE_PATH, sizeof(CHARGE_STATE_PATH), "/sys/class/power_supply/BAT%d/capacity", bat_num);
	snprintf(CHARGE_STATE_PATH, sizeof(CHARGE_STATE_PATH), "/sys/class/power_supply/BAT%d/status", bat_num);

	tray = gtk_status_icon_new();
	snprintf(icon_file, sizeof(icon_file), "%s/bat-charged.png", DEFAULT_THEME);
	gtk_status_icon_set_from_file(tray, icon_file);
	gtk_status_icon_set_has_tooltip (tray, TRUE);
	g_signal_connect(G_OBJECT(tray), "query-tooltip", GTK_SIGNAL_FUNC(show_tooltip), NULL);
	g_timeout_add(120000, update, NULL);

	/* Force useful cached tooltip text, force meaningful icon */
	update();
}


/***********************************************************************
 * Show the battery tray
 **********************************************************************/
void bat_tray_show()
{
	gtk_status_icon_set_visible(tray, TRUE);
}


/***********************************************************************
 * Hide the battery tray
 **********************************************************************/
void bat_tray_hide()
{
	gtk_status_icon_set_visible(tray, FALSE);
}


/***********************************************************************
 * Return the battery state
 **********************************************************************/
int get_battery_state()
{
	char state[1024];
	FILE* fd = NULL;

	if (!(fd = fopen(CHARGE_STATE_PATH, "r")))
		return STATE_UNKNOWN;

	if (!fgets(state, sizeof(state), fd))
	{
		fclose(fd);
		return STATE_UNKNOWN;
	}

	fclose(fd);

	chomp(state);

	if (strcmp(state, "Discharging") == 0)
		return STATE_DISCHARGING;

	if (strcmp(state, "Full") == 0)
		return STATE_CHARGED;

	if (strcmp(state, "Charging") == 0)
		return STATE_CHARGING;

	return STATE_UNKNOWN;
}


/***********************************************************************
 * Get the number of the first (who has more than one?) battery
 * Returns -1 if no battery present
 **********************************************************************/
int get_bat_num()
{
	FILE* fd = NULL;
	char filename[1024];
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		snprintf(filename, sizeof(filename), "/sys/class/power_supply/BAT%d/present", i);
		if ((fd = fopen(filename, "r")))
		{
			if (fgetc(fd) == '1')
			{
				fclose(fd);
				return i;
			}
			fclose(fd);
		}
	}
	return -1;
}
