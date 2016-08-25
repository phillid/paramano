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
#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

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
