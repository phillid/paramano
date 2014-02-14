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

#include "bat_tray.h"
#include "utilities.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static GtkStatusIcon* tray;
#define TOOLTIP_TEXT_SIZE 500
gchar tooltip_text[TOOLTIP_TEXT_SIZE];

void bat_tray_set_tooltip(const gchar* msg)
{
	memset(tooltip_text, '\0', TOOLTIP_TEXT_SIZE);
	memmove(tooltip_text, msg, strlen(msg));
}

static gboolean update_tooltip(GtkStatusIcon* status_icon,gint x,gint y,gboolean keyboard_mode,GtkTooltip* tooltip,gpointer data)
{
	gchar msg[500];
	memset(msg, '\0', 500);

	//printf("dis: %i, char: %i, full: %i\n", gb_discharging(), gb_charging(), gb_charged());

	if(gb_discharging())
	{
		gchar time[50];
		memset(time, '\0', 50);
		sprintf(msg, "Discharging (%i%% left)", gb_percent());
	} else if(gb_charging()) {
		gchar time[50];
		memset(time, '\0', 50);
		sprintf(msg, "Charging (%i%%)", gb_percent());
	} else if(gb_charged()) {
		sprintf(msg, "Fully Charged\nAC Plugged In");
	} else {
		sprintf(msg, "Unknown Status");
	}

	bat_tray_set_tooltip(msg);
	gtk_tooltip_set_text(tooltip, tooltip_text);

	return TRUE;
}

void bat_tray_update_icon_percent()
{
	gchar* file;
	int percent = gb_percent();
	int adjusted_percent;
	gchar adjusted_percent_string[4];
	memset(adjusted_percent_string, '\0', 4);

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

	if(gb_discharging())
	{
		file = g_strconcat(util_get_prefix(), "/share/trayfreq/traybat-", adjusted_percent_string, ".png", NULL);
	}
	else if(gb_charging())
	{
		file = g_strconcat(util_get_prefix(), "/share/trayfreq/traybat-", adjusted_percent_string, "-charging.png", NULL);
	}
	else
	{
		file = g_strconcat(util_get_prefix(), "/share/trayfreq/traybat-charged.png", NULL);
	}

	gtk_status_icon_set_from_file(tray, file);
}

static gboolean update_icon(gpointer user_data)
{
	bat_tray_update_icon_percent();
}

void bat_tray_init()
{
	tray = gtk_status_icon_new();
	gchar* icon_file = g_strconcat(util_get_prefix(), "/share/trayfreq/traybat-charged.png", NULL);
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