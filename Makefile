# Tabsize: 4

# Build utils
MAKE = make
CC = gcc

# Directories
PREFIX=/usr
BINDIR=$(PREFIX)/bin
SYSCONFDIR=/etc
SHAREDIR=$(PREFIX)/share
LOCALEDIR=$(SHAREDIR)/locale

# External program/support programs
SUDO=$(BINDIR)/sudo
TRAYFREQ_SET=$(BINDIR)/trayfreq-set

# Misc
TRAYFREQ_CONF=$(SYSCONFDIR)/trayfreq.conf
ROOT_UID=0


ifdef DEBUG
 EXTRA_CFLAGS+=-DDEBUG
endif

EXTRA_CFLAGS+=	-DPREFIX=\"$(PREFIX)\" \
				-DBINDIR=\"$(BINDIR)\" \
				-DSUDO=\"$(SUDO)\" \
				-DTRAYFREQ_SET=\"$(TRAYFREQ_SET)\" \
				-DLOCALEDIR=\"$(LOCALEDIR)\" \
				-DSHAREDIR=\"$(SHAREDIR)\" \
				-DROOT_UID=$(ROOT_UID)


DEPS = 	bat_tray.h \
		bool.h \
		common.h \
		config_file.h \
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

trayfreq_set_CFLAGS		=	-Wall \
							-D_=gettext

trayfreq_set_LDFLAGS	=	-lglib-2.0

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
# Strip all symbols from binaries
strip:
	strip -s trayfreq trayfreq-set
	
########################################################################
	

########################################################################
# Remove generated files
clean:
	rm -f trayfreq trayfreq-set *.o lc/*.mo trayfreq.conf
########################################################################


########################################################################
# Install entire suite
install:
	mkdir -p $(DESTDIR)/$(SHAREDIR)/trayfreq/
	cp -r themes $(DESTDIR)/$(SHAREDIR)/trayfreq/

	install -Dm 644 lc/fr.mo $(DESTDIR)/$(LOCALEDIR)/fr/LC_MESSAGES/trayfreq.mo

	install -Dm 644 trayfreq.conf $(DESTDIR)/etc/trayfreq.conf
	install -Dm 644 trayfreq.desktop $(DESTDIR)/etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 trayfreq $(DESTDIR)/$(BINDIR)/trayfreq
	install -Dm 755 trayfreq-set $(DESTDIR)/$(BINDIR)/trayfreq-set

	ln -s ../licenses/common/GLPv3/license.txt $(DESTDIR)/$(SHAREDIR)/trayfreq/LICENCE
	ln -s ../../../etc/trayfreq.conf $(DESTDIR)/$(SHAREDIR)/trayfreq/trayfreq.conf
########################################################################
