#include "paramano.h"
#include "getcore.h"
#include "getgov.h"
#include "getfreq.h"
#include "tray.h"
#include "bat_tray.h"
#include "defaults.h"
#include "config_file.h"
#include "common.h"

#include <gtk/gtk.h>
#include <unistd.h>     // getuid, getgid
#include <stdio.h>      // printf, FILE, fopen, etc
#include <stdlib.h>     // free etc
#include <stdbool.h>    // boolean types
#include <string.h>     // strlen
#include <libintl.h>    // gettext
#include <locale.h>     // LC_ALL etc


/***********************************************************************
 * Main
 **********************************************************************/
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	bindtextdomain("paramano",LOCALEDIR);
	textdomain("paramano");

	if (!gtk_init_check(&argc, &argv))
	{
		g_error( _("GTK Error: gtk_init_check returned FALSE.\nBailing.") );
		return 1;
	}

	config_init();
	gc_init();
	gg_init();
	gf_init();
	tray_init();
	tray_show();

	/* Show battery tray only if we're supposed to */
	if (DEFAULT_SHOW_BATTERY)
	{
		bat_tray_init();
		bat_tray_show();
	}

	gtk_main();
	return 0;
}
