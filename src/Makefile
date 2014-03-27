CC = gcc
DEFS = -DHAVE_CONFIG_H

GLIB_CFLAGS = -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
GLIB_LIBS = -lglib-2.0

#GTK_CFLAGS = -pthread -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/libdrm -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2
GTK_CFLAGS = -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0

#GTK_LIBS = -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype
GTK_LIBS = -lgtk-x11-2.0  -lgobject-2.0

PACKAGE_VERSION = 0.2
VERSION = 0.2


trayfreq_SOURCES = getcore.c getcore.h getfreq.c getfreq.h getgov.c getgov.h tray.c tray.h trayfreq.c utilities.c utilities.h widget_manager.c widget_manager.h trayfreq_set_interface.c trayfreq_set_interface.h config_file.c config_file.h defaults.c defaults.h getbat.c getbat.h bat_tray.c bat_tray.h
#trayfreq_SOURCES = getcore.c getcore.h getfreq.c getfreq.h getgov.c getgov.h tray.c tray.h trayfreq.c utilities.c utilities.h widget_manager.c widget_manager.h config_file.c config_file.h defaults.c defaults.h getbat.c getbat.h bat_tray.c bat_tray.h

trayfreq_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall

trayfreq_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm


trayfreq_set_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall
trayfreq_set_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_set_SOURCES = trayfreq_set.c getfreq.c getcore.c


all: trayfreq trayfreq-set

trayfreq-set:
	$(CC) -o trayfreq-set $(trayfreq_set_SOURCES) $(trayfreq_set_CFLAGS)  $(trayfreq_set_LDFLAGS)

trayfreq:
	$(CC) -o trayfreq $(trayfreq_SOURCES) $(trayfreq_CFLAGS)  $(trayfreq_LDFLAGS)

clean:
	rm trayfreq trayfreq-set
