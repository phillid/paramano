# Tabsize: 4

MAKE = make
CC = gcc
PREFIX=/usr
BINDIR=$(PREFIX)/bin
SHAREDIR=$(PREFIX)/share
LOCALEDIR=$(SHAREDIR)/locale/

SUDO=/usr/bin/sudo
TRAYFREQ_SET=$(BINDIR)/trayfreq-set
TRAYFREQ_CONF=/etc/trayfreq.conf

ifdef DEBUG
 EXTRA_CFLAGS+=-DDEBUG
endif

EXTRA_CFLAGS+=	-DPREFIX=\"$(PREFIX)\" \
				-DBINDIR=\"$(BINDIR)\" \
				-DSUDO=\"$(SUDO)\" \
				-DTRAYFREQ_SET=\"$(TRAYFREQ_SET)\" \
				-DLOCALEDIR=\"$(LOCALEDIR)\" \
				-DSHAREDIR=\"$(SHAREDIR)\"


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
all: trayfreq trayfreq-set lang trayfreq.conf
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
# Prepare template config file
trayfreq.conf:
	sed	-e 's:SHAREDIR:$(SHAREDIR):g' \
		-e 's:TRAYFREQ_CONF:$(TRAYFREQ_CONF):g' \
		trayfreq.conf.src > trayfreq.conf
########################################################################
	

########################################################################
# Remove generated files
clean:
	rm -f trayfreq trayfreq-set *.o lc/*.mo trayfreq.conf
########################################################################


########################################################################
# Install entire suite
install:
	install -Dm 755 themes $(DESTDIR)/$(SHAREDIR)/trayfreq/themes

	install -Dm 644 lc/fr.mo $(DESTDIR)/$(LOCALEDIR)/fr/LC_MESSAGES/trayfreq.mo

	install -Dm 644 trayfreq.conf $(DESTDIR)/etc/trayfreq.conf
	install -Dm 644 trayfreq.desktop $(DESTDIR)/etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 trayfreq $(DESTDIR)/$(BINDIR)/trayfreq
	install -Dm 755 trayfreq-set $(DESTDIR)/$(BINDIR)/trayfreq-set

	ln -s ../licenses/common/GLPv3/license.txt $(DESTDIR)/$(SHAREDIR)/trayfreq/LICENCE
	ln -s ../../../etc/trayfreq.conf $(DESTDIR)/$(SHAREDIR)/trayfreq/trayfreq.conf
########################################################################
