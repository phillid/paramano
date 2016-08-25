#include "defaults.h"

#include <stddef.h>
#include <stdio.h>

void defaults_init()
{
	DEFAULT_GOV				= NULL;
	DEFAULT_FREQ			= NULL;
	DEFAULT_PROG			= NULL;
	DEFAULT_BAT_GOV			= NULL;
	DEFAULT_AC_GOV			= NULL;
	DEFAULT_SHOW_BATTERY	= true;
	snprintf(DEFAULT_THEME, sizeof(DEFAULT_THEME), SHAREDIR"/paramano/themes/default");
}
