bin_PROGRAMS = trayfreq trayfreq-set


trayfreq_SOURCES = getcore.c getcore.h getfreq.c getfreq.h getgov.c	\
getgov.h tray.c tray.h trayfreq.c utilities.c utilities.h		\
widget_manager.c widget_manager.h trayfreq_set_interface.c		\
trayfreq_set_interface.h config_file.c config_file.h defaults.c		\
defaults.h getbat.c getbat.h bat_tray.c bat_tray.h
trayfreq_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS)
trayfreq_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm

trayfreq_set_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS)
trayfreq_set_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_set_SOURCES = trayfreq_set.c getfreq.c getcore.c


install-exec-hook:
if SET_SUID
	chmod -f 4755 ${DESTDIR}${prefix}/bin/trayfreq-set
endif
