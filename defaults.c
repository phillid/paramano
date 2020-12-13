#include "defaults.h"

#include <stddef.h>
#include <stdio.h>

char* DEFAULT_GOV;
char* DEFAULT_FREQ;
char* DEFAULT_PROG;
char* DEFAULT_BAT_GOV;
char* DEFAULT_AC_GOV;
bool  DEFAULT_SHOW_BATTERY;
char  DEFAULT_THEME[1024];

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
