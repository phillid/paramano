# Directories
PREFIX=/usr
BINDIR=$(PREFIX)/bin
SYSCONFDIR=/etc
SHAREDIR=$(PREFIX)/share
LOCALEDIR=$(SHAREDIR)/locale

# External program/support programs
SUDO=$(BINDIR)/sudo
PARAMANO_SET=$(BINDIR)/paramano-set

# Misc
PARAMANO=$(BINDIR)/paramano
PARAMANO_CONF=$(SYSCONFDIR)/paramano.conf
ROOT_UID=0


DEFS +=		-DPREFIX=\"$(PREFIX)\" \
			-DBINDIR=\"$(BINDIR)\" \
			-DSUDO=\"$(SUDO)\" \
			-DPARAMANO_SET=\"$(PARAMANO_SET)\" \
			-DPARAMANO_CONF=\"$(PARAMANO_CONF)\" \
			-DLOCALEDIR=\"$(LOCALEDIR)\" \
			-DSHAREDIR=\"$(SHAREDIR)\" \
			-DROOT_UID=$(ROOT_UID) \
			-D_GNU_SOURCE


DEPS =		bat_tray.h \
			common.h \
			config_file.h \
			defaults.h \
			getcore.h \
			getfreq.h \
			getgov.h \
			paramano.h \
			reload.h \
			tray.h \
			paramano_set_interface.h

CFLAGS	=	-I/usr/include/gtk-2.0 \
			-I/usr/lib/gtk-2.0/include \
			-I/usr/include/pango-1.0 \
			-I/usr/include/cairo \
			-I/usr/include/gdk-pixbuf-2.0 \
			-I/usr/include/atk-1.0 \
			-I/usr/include/glib-2.0 \
			-I/usr/lib/glib-2.0/include \
			-Wall \
			-Wclobbered \
			-Wempty-body \
			-Wignored-qualifiers \
			-Wmissing-field-initializers \
			-Wmissing-parameter-type \
			-Woverride-init \
			-Wsign-compare \
			-Wtype-limits \
			-Wuninitialized \
			-Wunused-but-set-parameter \
			-Wdouble-promotion \
			-Werror \
			-D_=gettext

LDFLAGS	=	-lgtk-3 \
			-lgobject-2.0 \
			-lglib-2.0



########################################################################
# Phony targets
.PHONY: all debug lang paramano-extra clean strip install
########################################################################


########################################################################
# Make entire suite
all: paramano paramano-set lang paramano-extra
########################################################################


########################################################################
# Make entire suite, with a huge amount of debug messages compiled-in
# Seriously, don't use this feature unless you're actually having a
# bug. It'll flood your system journal with repetitive, boring drivel
debug:
	make all CFLAGS="$(CFLAGS) -DDEBUG"
########################################################################


########################################################################
# Make main paramano system tray program
paramano:	bat_tray.o \
			common.o \
			config_file.o \
			defaults.o \
			getcore.o \
			getfreq.o \
			getgov.o \
			reload.o \
			paramano.o \
			tray.o \
			paramano_set_interface.o
	$(CC) -o $@ $^ $(LDFLAGS)
########################################################################


########################################################################
# Make paramano-set utility
paramano-set: \
			paramano_set.o \
			common.o \
			getcore.o \
			getfreq.o \
			getgov.o
	$(CC) -o $@ $? $(LDFLAGS)
########################################################################


########################################################################
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEFS)
########################################################################


########################################################################
# Make language file(s)
lang:
	msgfmt -c -o lc/fr.mo lc/fr.po
########################################################################


########################################################################
# Prepare template config file
paramano-extra:
	for file in paramano.conf paramano.desktop ; do \
		sed	-e 's:SHAREDIR:$(SHAREDIR):g' \
			-e 's:PARAMANO_CONF:$(PARAMANO_CONF):g'  \
			-e 's:PARAMANO:$(PARAMANO):g' \
			$$file.src > $$file ; \
	done
########################################################################


########################################################################
# Strip all symbols from binaries
strip:
	strip -s paramano paramano-set
########################################################################


########################################################################
# Remove generated files
clean:
	rm -f paramano paramano-set *.o lc/*.mo paramano.conf paramano.desktop
########################################################################


########################################################################
# Install entire suite
install:
	mkdir -p "$(DESTDIR)/$(SHAREDIR)/paramano/"
	cp -r themes "$(DESTDIR)/$(SHAREDIR)/paramano/"

	install -Dm 644 lc/fr.mo "$(DESTDIR)/$(LOCALEDIR)/fr/LC_MESSAGES/paramano.mo"

	install -Dm 644 paramano.conf "$(DESTDIR)/$(PARAMANO_CONF)"
	install -Dm 644 paramano.desktop "$(DESTDIR)/etc/xdg/autostart/paramano.desktop"

	install -Dm 755 paramano "$(DESTDIR)/$(PARAMANO)"
	install -Dm 755 paramano-set "$(DESTDIR)/$(PARAMANO_SET)"

	# These provide some compatability with trayfreq
	ln -s paramano "$$(dirname $(DESTDIR)/$(PARAMANO))/trayfreq"
	ln -s paramano-set "$$(dirname $(DESTDIR)/$(PARAMANO))/trayfreq-set"
########################################################################

