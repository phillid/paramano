/************************************************************************
 * This file is part of trayfreq-archlinux.                             *
 *                                                                      *
 * trayfreq-archlinux is free software; you can redistribute it and/or  *
 * modify it under the terms of the GNU General Public Licence as       *
 * published by the Free Software Foundation; either version 3 of the   *
 * Licence, or (at your option) any later version.                      *
 *                                                                      *
 * trayfreq-archlinux is distributed in the hope that it will be useful,*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public Licence for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public Licence    *
 * along with trayfreq-archlinux. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                      *
 ************************************************************************/


#include "../strings.h"
#include "bat_tray.h"
#include "../common.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static GtkStatusIcon* tray;

int _BAT_NUM;
char CHARGE_VALUE_PATH[512];
char CHARGE_STATE_PATH[512];

/***********************************************************************
 * Return the battery level percentage
 **********************************************************************/
//#define get_bat_percent()	get_int_value_from_file(CHARGE_VALUE_PATH);
int get_bat_percent(){return get_int_value_from_file(CHARGE_VALUE_PATH); }


#define TOOLTIP_TEXT_SIZE 128
gchar tooltip_text[TOOLTIP_TEXT_SIZE];


/***********************************************************************
 * Updates the battery tray tooltip text
 **********************************************************************/
static gboolean update_tooltip(GtkStatusIcon* status_icon,gint x,gint y,gboolean keyboard_mode,GtkTooltip* tooltip,gpointer data)
{
	gchar msg[TOOLTIP_TEXT_SIZE];
	//memset(msg,0,TOOLTIP_TEXT_SIZE);
	switch(get_battery_state())
	{
		case STATE_DISCHARGING:
			sprintf(msg, S_BAT_TRAY_C_BATTERY_DISCHARGING, get_bat_percent());
			break;

		case STATE_CHARGING:
			sprintf(msg, S_BAT_TRAY_C_BATTERY_CHARGING, get_bat_percent());
			break;
		case STATE_CHARGED:
			sprintf(msg, S_BAT_TRAY_C_BATTERY_FULL);
			break;

		default:
			sprintf(msg, S_BAT_TRAY_C_BATTERY_UNKNOWN);
			break;
	}

	gtk_tooltip_set_text(tooltip, msg);

	return TRUE;
}


/***********************************************************************
 * Updates the battery tray icon based upon battery percent
 **********************************************************************/
static gboolean update_icon(gpointer user_data)
{
	gchar* icon_file;
	unsigned int percent = get_bat_percent();
	unsigned int adjusted_percent;
	gchar adjusted_percent_string[4];

	if(percent > 90)
		adjusted_percent=100;
	else if(percent > 70)
		adjusted_percent=80;
	else if(percent > 50)
		adjusted_percent=60;
	else if(percent > 30)
		adjusted_percent=40;
	else if(percent > 10)
		adjusted_percent=20;
	else
		adjusted_percent=0;

	sprintf(adjusted_percent_string, "%i", adjusted_percent);

	switch ( get_battery_state() )
	{
		case STATE_DISCHARGING:
			icon_file = g_strconcat("/usr/share/trayfreq/traybat-", adjusted_percent_string, ".png", NULL);
			break;
		case STATE_CHARGING:
			icon_file = g_strconcat("/usr/share/trayfreq/traybat-", adjusted_percent_string, "-charging.png", NULL);
			break;

		default:
			icon_file = g_strconcat("/usr/share/trayfreq/traybat-charged.png", NULL);
			break;
	}
	gtk_status_icon_set_from_file(tray, icon_file);
	return TRUE;
}




void bat_tray_init()
{
	// Get the battery number, store it for later
	_BAT_NUM = get_bat_num();

	// Set up battery info filenames/paths
	sprintf(CHARGE_VALUE_PATH, "/sys/class/power_supply/BAT%i/capacity", _BAT_NUM);
	sprintf(CHARGE_STATE_PATH, "/sys/class/power_supply/BAT%i/status", _BAT_NUM);
	// NOT USED : sprintf(CURRENT_PATH, "/sys/class/power_supply/BAT%i/charge_now", _BAT_NUM);


	tray = gtk_status_icon_new();
	gchar* icon_file = g_strconcat("/usr/share/trayfreq/traybat-charged.png", NULL);
	gtk_status_icon_set_from_file(tray, icon_file);
	gtk_status_icon_set_has_tooltip (tray, TRUE);
	g_signal_connect(G_OBJECT(tray), "query-tooltip", GTK_SIGNAL_FUNC(update_tooltip), NULL);
	gtk_timeout_add(5000, update_icon, NULL);
}


void bat_tray_show()
{
	gtk_status_icon_set_visible(tray, TRUE);
}

void bat_tray_hide()
{
	gtk_status_icon_set_visible(tray, FALSE);
}


/***********************************************************************
 * Return the battery state
 **********************************************************************/
int get_battery_state()
{
	if (file_has_line(CHARGE_STATE_PATH, "Discharging"))
		return STATE_DISCHARGING;

	if (file_has_line(CHARGE_STATE_PATH, "Full"))
		return STATE_CHARGED;

	if (file_has_line(CHARGE_STATE_PATH, "Charging"))
		return STATE_CHARGING;

	return STATE_UNKNOWN;
}

/***********************************************************************
 * Get the number of the first (who has more than one?) battery
 * Returns -1 if no battery present
 **********************************************************************/
int get_bat_num()
{
	FILE* fd;
	gchar file[40];
	unsigned int i;
	for(i = 0; i < 3; i++)
	{
		sprintf(file, "/sys/class/power_supply/BAT%i/present", i);

		if( (fd = fopen(file, "r")) )
		{
			if (fgetc(fd) == '1')
			{
				fclose(fd);
				return i;
			}
		}
	}
	return -1;
}
