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

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <stdbool.h> /* boolean types */
#include <stdlib.h> /* NULL */

char* DEFAULT_GOV;
char* DEFAULT_FREQ;
char* DEFAULT_PROG;
char* DEFAULT_BAT_GOV;
char* DEFAULT_AC_GOV;
bool  DEFAULT_SHOW_BATTERY;
char* DEFAULT_THEME;


void defaults_init();

#endif /* ifndef DEFAULTS_H */
