# Tabsize: 4

MAKE = make
CC = gcc
PREFIX=/usr
BINDIR=$(PREFIX)/bin
SUDO=/usr/bin/sudo
TRAYFREQ_SET=$(BINDIR)/trayfreq-set
LOCALE_DIR=$(PREFIX)/share/locale/

ifdef DEBUG
 EXTRA_CFLAGS+=-DDEBUG
endif

EXTRA_CFLAGS+=	-DPREFIX=\"$(PREFIX)\" \
				-DBINDIR=\"$(BINDIR)\" \
				-DSUDO=\"$(SUDO)\" \
				-DTRAYFREQ_SET=\"$(TRAYFREQ_SET)\" \
				-DLOCALE_DIR=\"$(LOCALE_DIR)\"


DEPS = 	bat_tray.h \
		bool.h \
		common.h \
		config_file.h \
		debug.h \
		defaults.h \
		getcore.h \
		getfreq.h \
		getgov.h \
		reload.h \
		trayfreq.h \
		tray.h \
		trayfreq_set_interface.h 


trayfreq_CFLAGS			=	-I/usr/include/gtk-2.0 \
							-I/usr/lib/gtk-2.0/include \
							-I/usr/include/pango-1.0 \
							-I/usr/include/cairo \
							-I/usr/include/gdk-pixbuf-2.0 \
							-I/usr/include/atk-1.0 \
							-I/usr/include/glib-2.0 \
							-I/usr/lib/glib-2.0/include \
							-Wall \
							-D_=gettext

trayfreq_LDFLAGS		=	-lgtk-3 \
							-lgobject-2.0 \
							-lglib-2.0

trayfreq_SOURCES		=	freq_tray/getcore.c \
							freq_tray/getfreq.c \
							freq_tray/getgov.c \
							tray.c \
							trayfreq.c \
							trayfreq_set/trayfreq_set_interface.c \
							config_file.c \
							defaults.c \
							bat_tray/bat_tray.c \
							common.c \
							reload.c

trayfreq_set_CFLAGS		=	-Wall \
							-D_=gettext

trayfreq_set_LDFLAGS	=	-lglib-2.0

trayfreq_set_SOURCES	=	trayfreq_set/trayfreq_set.c \
							freq_tray/getfreq.c \
							freq_tray/getcore.c


########################################################################
# Make entire suite
all: trayfreq trayfreq-set lang
########################################################################


########################################################################
# Make main trayfreq system tray program
trayfreq:	bat_tray.o \
			common.o \
			config_file.o \
			defaults.o \
			getcore.o \
			getfreq.o \
			getgov.o \
			reload.o \
			trayfreq.o \
			tray.o \
			trayfreq_set_interface.o
	$(CC) -o $@ $? $(trayfreq_LDFLAGS)

########################################################################
# Make trayfreq-set utility
trayfreq-set: \
			trayfreq_set.o \
			getcore.o \
			getfreq.o \
			getgov.o

	$(CC) -o $@ $? $(trayfreq_set_LDFLAGS)
########################################################################



########################################################################
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(trayfreq_CFLAGS) $(EXTRA_CFLAGS)
########################################################################



########################################################################
# Make language file(s)
lang:
	msgfmt -c -o lc/fr.mo lc/fr.po
########################################################################


########################################################################
# Remove generated files
clean:
	rm -f trayfreq trayfreq-set *.o lc/*.mo
########################################################################


########################################################################
# Install entire suite
install:
	#mkdir -p $(PREFIX)/usr/share/trayfreq/
	#mkdir -p $(PREFIX)/$(LOCALE_DIR)/fr/LC_MESSAGES/
	#mkdir -p $(PREFIX)/etc/xdg/autostart/

	cp data/*.png $(PREFIX)/usr/share/trayfreq/
	cp lc/fr.mo $(PREFIX)$(LOCALE_DIR)/fr/LC_MESSAGES/trayfreq.mo

	install -Dm 644 data/trayfreq.conf $(PREFIX)/etc/trayfreq.conf
	install -Dm 644 data/trayfreq.desktop $(PREFIX)/etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 trayfreq $(PREFIX)/$(BINDIR)/trayfreq
	install -Dm 755 trayfreq-set $(PREFIX)/$(BINDIR)/trayfreq-set

	ln -s ../licenses/common/GLPv3/license.txt $(PREFIX)/usr/share/trayfreq/LICENCE
	ln -s ../../../etc/trayfreq.conf $(PREFIX)/usr/share/trayfreq/trayfreq.conf
########################################################################
