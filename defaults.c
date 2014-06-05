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

#include "defaults.h"

#include <stdio.h>

char* _DEFAULT_GOV;
char* _DEFAULT_FREQ;
char* _DEFAULT_PROG;
char* _DEFAULT_BAT_GOV;
char* _DEFAULT_AC_GOV;
bool  _DEFAULT_SHOW_BATTERY = true;
char _DEFAULT_THEME[2048]; // to do : make dynamic with malloc

void defaults_init()
{
	_DEFAULT_GOV			= NULL;
	_DEFAULT_FREQ			= NULL;
	_DEFAULT_PROG			= NULL;
	_DEFAULT_BAT_GOV		= NULL;
	_DEFAULT_AC_GOV			= NULL;
	_DEFAULT_SHOW_BATTERY	= true;
	sprintf (_DEFAULT_THEME, SHAREDIR"/trayfreq/themes/default");
}
