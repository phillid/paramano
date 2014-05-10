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

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "bool.h" /* boolean types */
#include <stdlib.h> /* NULL */

char* _DEFAULT_GOV;
char* _DEFAULT_FREQ;
char* _DEFAULT_PROG;
char* _DEFAULT_BAT_GOV;
char* _DEFAULT_AC_GOV;
bool  _DEFAULT_SHOW_BATTERY;
bool  _DEFAULT_USE_SUDO;


void defaults_init();

#endif /* ifndef DEFAULTS_H */
