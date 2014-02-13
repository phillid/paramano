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

GList* wm_widgets;

void wm_add_widget(GtkWidget* widget)
{
	wm_widgets = g_list_prepend(wm_widgets, widget);
}

void wm_show_widgets()
{
	GList* curr = g_list_last(wm_widgets);
	while(curr)
	{
		gtk_widget_show(curr->data);
		curr = g_list_previous(curr);
	}
}
