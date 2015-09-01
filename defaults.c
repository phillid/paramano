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

void defaults_init()
{
	DEFAULT_GOV				= NULL;
	DEFAULT_FREQ			= NULL;
	DEFAULT_PROG			= NULL;
	DEFAULT_BAT_GOV			= NULL;
	DEFAULT_AC_GOV			= NULL;
	DEFAULT_SHOW_BATTERY	= true;
	asprintf(&DEFAULT_THEME, SHAREDIR"/paramano/themes/default");
}
