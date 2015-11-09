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

#include "tray.h"
#include "getcore.h"
#include "getfreq.h"
#include "getgov.h"
#include "bat_tray.h"
#include "defaults.h"
#include "paramano_set_interface.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <gtk/gtk.h>

static GtkStatusIcon* tray;
static char tooltip_text[1024];
static GtkWidget* menu;
static GSList* menu_items;
static GtkWidget* checked_menu_item;


/***********************************************************************
 * Handler for when freq is chosen
 **********************************************************************/
static void freq_menu_item_toggled(GtkCheckMenuItem* item, gpointer data)
{
	if (gtk_check_menu_item_get_active(item))
	{
		checked_menu_item = GTK_WIDGET(item);
		gint freq = GPOINTER_TO_INT(data);
		unsigned int i = 0;
		for (i = 0; i < gc_number(); i++)
			si_freq(freq, i);
	}
}


/***********************************************************************
 * Handler for when governor is chosen
 **********************************************************************/
static void gov_menu_item_toggled(GtkCheckMenuItem* item, gpointer data)
{
	if (gtk_check_menu_item_get_active(item))
	{
		checked_menu_item = GTK_WIDGET(item);
		char* gov = (char*)data;
		unsigned int i = 0;
		for (i = 0; i < gc_number(); i++)
			si_gov(gov, i);
	}
}

/***********************************************************************
 * Destroy a menu item
 **********************************************************************/
static void remove_menu_item(GtkWidget* menu_item, gpointer data)
{
	gtk_widget_destroy(menu_item);
}


/***********************************************************************
 * Remove all items in menu
 **********************************************************************/
static void tray_clear_menu()
{
	GtkContainer* cont = GTK_CONTAINER(menu);
	gtk_container_foreach(cont, remove_menu_item, NULL);
	menu_items = NULL;
}


/***********************************************************************
 * Create new instance of gtk_tray_new for gov/freq tray
 **********************************************************************/
static void tray_init_menu()
{
	menu = gtk_menu_new();
}

/***********************************************************************
 * Populate gtk menu object with all the entries
 **********************************************************************/
static void tray_generate_menu()
{
	tray_clear_menu();
	gg_init();

	char label[1024];
	unsigned int i = 0;

	char current_governor[20];
	memset(current_governor, '\0', sizeof(current_governor) );
	gg_current(0, current_governor, sizeof(current_governor) );

	gint current_frequency = gf_current(0);

	/* Add available frequencies */
	for (i = 0; i < gf_number(); i++)
	{
		gf_get_frequency_label(label, sizeof(label), gf_freqi(0, i));

		GtkWidget* item = gtk_radio_menu_item_new_with_label(menu_items, label);

		menu_items = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM (item));

		if (g_strcmp0(current_governor, "userspace") == 0 && gf_freqi(0, i) == current_frequency)
			gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);

		g_signal_connect(G_OBJECT(item), "toggled", GTK_SIGNAL_FUNC(freq_menu_item_toggled), GINT_TO_POINTER(gf_freqi(0, i)));

		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	}

	/* Add a seperator */
	GtkWidget* seperator = gtk_separator_menu_item_new();
	gtk_menu_append(menu, seperator);

	/* Add available governors */
	for (i = 0; i < gg_number(); i++)
	{
		if (g_strcmp0(gg_gov(0, i), "userspace") == 0)
			continue;

		GtkWidget* item = gtk_radio_menu_item_new_with_label(menu_items, gg_gov(0, i));
		menu_items = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM (item));

		if (g_strcmp0(gg_gov(0, i), current_governor) == 0)
			gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);

		g_signal_connect(G_OBJECT(item), "toggled", GTK_SIGNAL_FUNC(gov_menu_item_toggled), gg_gov(0, i));

		gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
	}
	gtk_widget_show_all(menu);
}

/***********************************************************************
 * Tell gtk what the tooltip message should be
 **********************************************************************/
static gboolean show_tooltip(GtkStatusIcon* status_icon, gint x, gint y, gboolean keyboard_mode,GtkTooltip* tooltip, gpointer data)
{
	gtk_tooltip_set_text(tooltip, tooltip_text);
	return true;
}


/***********************************************************************
 * Work out what the tooltip message would be now, store it away
 **********************************************************************/
static void update_tooltip_cache()
{
	char msg[10240], label[1024];
	char current_governor[20]; /* FIXME magic */
	unsigned int i = 0;
	unsigned int offset = 0;

	memset(current_governor, '\0', sizeof(current_governor) );

	gg_current(0, current_governor, sizeof(current_governor) );

	offset = snprintf(msg, sizeof(msg), _("Governor: %s\n"), current_governor);

	for (i = 0; i < gc_number(); i++)
	{
		gf_get_frequency_label(label, sizeof(label), gf_current(i));
		offset += snprintf(msg+offset, sizeof(msg)-offset, _("CPU%d: %s%s"), i, label, i == gc_number()-1 ? "" : "\n");
	}

	strncpy(tooltip_text, msg, sizeof(tooltip_text));
	tooltip_text[sizeof(tooltip_text)-1] = '\0';
}


/***********************************************************************
 * Handler for spawning the popup/context menu
 **********************************************************************/
static void popup_menu(GtkStatusIcon* statuc_icon,guint button,guint activate_time,gpointer data)
{
	tray_generate_menu();
	gtk_menu_popup(GTK_MENU(menu),NULL,NULL,gtk_status_icon_position_menu,tray,button,activate_time);
}


/**********************************************************************
 * Set icon based on current freq/governor
 **********************************************************************/
static void update_icon()
{
	char file[1024];
	int max_frequency = gf_freqi(0, 0);
	int adjusted_percent, percent;

	/* If max_frequency is 0, we don't want to divide by it,
	 * so give up, call it a day, and have a simple icon */
	if (max_frequency == 0)
	{
		adjusted_percent = 0;
	} else {
		/* Percentages need to be {25,50,75,100}. Round to one of these numbers.
		 * TO DO: round/truncate instead of lots of ifs */
		percent = (gf_current(0) * 100)/max_frequency;
		if (percent == 100) {
			adjusted_percent = 100;
		} else if (percent >= 65.5) {
			adjusted_percent = 75;
		} else if (percent >= 37.5) {
			adjusted_percent = 50;
		} else if (percent >= 12.5) {
			adjusted_percent = 25;
		} else {
			adjusted_percent = 0;
		}
	}

	snprintf(file, sizeof(file), "%s/cpu-%d.png", DEFAULT_THEME,adjusted_percent);
	gtk_status_icon_set_from_file(tray, file);
}


/***********************************************************************
 * Update the freq/gov tray icon
 * Also updates the cached tooltip text
 **********************************************************************/
static gboolean update()
{
	unsigned int i;
	switch ( get_battery_state() )
	{
		case STATE_DISCHARGING:
			if (DEFAULT_BAT_GOV)
			{
				for (i = 0; i < gc_number(); i++)
					si_gov(DEFAULT_BAT_GOV, i);
			}
			break;

		case STATE_CHARGING:
		case STATE_FULL:
			if (DEFAULT_AC_GOV)
			{
				for (i = 0; i < gc_number(); i++)
					si_gov(DEFAULT_AC_GOV, i);
			}

			break;
	}

	update_tooltip_cache();
	update_icon();
	return true;
}


/***********************************************************************
 * Apply default gov/freq for current situation
 **********************************************************************/
void tray_set_defaults()
{
	unsigned int i = 0;
	if (DEFAULT_GOV)
	{
		for (i = 0; i < gc_number(); i++)
			si_gov(DEFAULT_GOV, i);

	} else {
		for (i = 0; i < gc_number(); i++)
			si_gov("ondemand", i);
	}

	if (DEFAULT_FREQ)
	{
		for (i = 0; i < gc_number(); i++)
			si_freq(atoi(DEFAULT_FREQ), i);
	}

}


/***********************************************************************
 * Start the tray icon thingy
 **********************************************************************/
void tray_init()
{
	tray_set_defaults();
	tray = gtk_status_icon_new();
	char* icon_file = g_strconcat(DEFAULT_THEME, "/cpu-0.png", NULL);

	/* Force something useful to be in the cached tooltip text */
	update_tooltip_cache();

	gtk_status_icon_set_from_file(tray, icon_file);
	gtk_status_icon_set_has_tooltip(tray, TRUE);

	g_signal_connect(G_OBJECT(tray), "query-tooltip", GTK_SIGNAL_FUNC(show_tooltip), NULL);
	g_signal_connect(G_OBJECT(tray), "popup-menu", GTK_SIGNAL_FUNC(popup_menu), NULL);

	g_timeout_add(1000, update, NULL);

	/* Force meaningful tooltip cached text and force meaningful icon */
	update();

	tray_init_menu();
}


/***********************************************************************
 * Show the tray
 **********************************************************************/
void tray_show()
{
	gtk_status_icon_set_visible(tray, TRUE);
}

/***********************************************************************
 * Hide the tray
 **********************************************************************/
void tray_hide()
{
	gtk_status_icon_set_visible(tray, FALSE);
}


/***********************************************************************
 * Return bool for visiblity of tray
 **********************************************************************/
bool tray_visible()
{
	return gtk_status_icon_get_visible(tray);
}

/***********************************************************************
 * Return bool for embeddedness of tray
 **********************************************************************/
bool tray_embedded()
{
	return gtk_status_icon_is_embedded(tray);
}
