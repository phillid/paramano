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


#trayfreq_SOURCES = getcore.c getcore.h getfreq.c getfreq.h getgov.c getgov.h tray.c tray.h trayfreq.c utilities.c utilities.h widget_manager.c widget_manager.h trayfreq_set_interface.c trayfreq_set_interface.h config_file.c config_file.h defaults.c defaults.h getbat.c getbat.h bat_tray.c bat_tray.h
trayfreq_SOURCES = getcore.c getcore.h getfreq.c getfreq.h getgov.c getgov.h tray.c tray.h trayfreq.c utilities.c utilities.h widget_manager.c widget_manager.h config_file.c config_file.h defaults.c defaults.h getbat.c getbat.h bat_tray.c bat_tray.h

trayfreq_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS)

trayfreq_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm


trayfreq_set_CFLAGS = $(GTK_CFLAGS) $(GLIB_CFLAGS)
trayfreq_set_LDFLAGS = $(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_set_SOURCES = trayfreq_set.c getfreq.c getcore.c


all:
	$(CC) -o trayfreq-set $(trayfreq_set_SOURCES) $(trayfreq_set_CFLAGS)  $(trayfreq_set_LDFLAGS)
	$(CC) -o trayfreq $(trayfreq_SOURCES) trayfreq_set_interface.c $(trayfreq_CFLAGS)  $(trayfreq_LDFLAGS)


# Tell versions [3.59,3.63) of GNU make to not export all variables otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:














#pkgdatadir = $(datadir)/trayfreq
#pkgincludedir = $(includedir)/trayfreq
#pkglibdir = $(libdir)/trayfreq
#pkglibexecdir = $(libexecdir)/trayfreq
#am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
#install_sh_DATA = $(install_sh) -c -m 644
#install_sh_PROGRAM = $(install_sh) -c
#install_sh_SCRIPT = $(install_sh) -c
#INSTALL_HEADER = $(INSTALL_DATA)
#transform = $(program_transform_name)
#NORMAL_INSTALL = :
#PRE_INSTALL = :
#POST_INSTALL = :
#NORMAL_UNINSTALL = :
#PRE_UNINSTALL = :
#POST_UNINSTALL = :
#bin_PROGRAMS = trayfreq$(EXEEXT) trayfreq-set$(EXEEXT)
#subdir = src
#DIST_COMMON = $(srcdir)/Makefile.am $(srcdir)/Makefile.in \
	#$(srcdir)/config.h.in
#ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
#am__aclocal_m4_deps = $(top_srcdir)/configure.ac
#am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	#$(ACLOCAL_M4)
#mkinstalldirs = $(install_sh) -d
#CONFIG_HEADER = config.h
#CONFIG_CLEAN_FILES =
#CONFIG_CLEAN_VPATH_FILES =
#am__installdirs = "$(DESTDIR)$(bindir)"
#PROGRAMS = $(bin_PROGRAMS)
#am_trayfreq_OBJECTS = trayfreq-getcore.$(OBJEXT) \
	#trayfreq-getfreq.$(OBJEXT) trayfreq-getgov.$(OBJEXT) \
	#trayfreq-tray.$(OBJEXT) trayfreq-trayfreq.$(OBJEXT) \
	#trayfreq-utilities.$(OBJEXT) trayfreq-widget_manager.$(OBJEXT) \
	#trayfreq-trayfreq_set_interface.$(OBJEXT) \
	#trayfreq-config_file.$(OBJEXT) trayfreq-defaults.$(OBJEXT) \
	#trayfreq-getbat.$(OBJEXT) trayfreq-bat_tray.$(OBJEXT)
#trayfreq_OBJECTS = $(am_trayfreq_OBJECTS)
#trayfreq_LDADD = $(LDADD)
#trayfreq_LINK = $(CCLD) $(trayfreq_CFLAGS) $(CFLAGS) \
	#$(trayfreq_LDFLAGS) $(LDFLAGS) -o $@
#am_trayfreq_set_OBJECTS = trayfreq_set-trayfreq_set.$(OBJEXT) \
	#trayfreq_set-getfreq.$(OBJEXT) trayfreq_set-getcore.$(OBJEXT)
#trayfreq_set_OBJECTS = $(am_trayfreq_set_OBJECTS)
#trayfreq_set_LDADD = $(LDADD)
#trayfreq_set_LINK = $(CCLD) $(trayfreq_set_CFLAGS) $(CFLAGS) \
	#$(trayfreq_set_LDFLAGS) $(LDFLAGS) -o $@
