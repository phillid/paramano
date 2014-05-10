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

#ifndef BAT_TRAY_H
#define BAT_TRAY_H

#define STATE_CHARGING		0
#define STATE_DISCHARGING	1
#define STATE_CHARGED		2
#define STATE_FULL			STATE_CHARGED
#define STATE_UNKNOWN		3

void bat_tray_init();
void bat_tray_show();
void bat_tray_hide();
int  get_battery_state();
int  get_bat_num();

#endif /* ifndef BAT_TRAY_H */
