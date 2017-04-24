# Directories
PREFIX=/usr
BINDIR=$(PREFIX)/bin
SYSCONFDIR=/etc
SHAREDIR=$(PREFIX)/share
LOCALEDIR=$(SHAREDIR)/locale
POWER_DIR="/sys/class/power_supply/"

# External program/support programs
SUDO=$(BINDIR)/sudo
PARAMANO_SET=$(BINDIR)/paramano-set

# Misc
PARAMANO=$(BINDIR)/paramano
PARAMANO_CONF=$(SYSCONFDIR)/paramano.conf
ROOT_UID=0


DEFS +=    -DPREFIX=\"$(PREFIX)\" \
           -DBINDIR=\"$(BINDIR)\" \
           -DSUDO=\"$(SUDO)\" \
           -DPARAMANO_SET=\"$(PARAMANO_SET)\" \
           -DPARAMANO_CONF=\"$(PARAMANO_CONF)\" \
           -DLOCALEDIR=\"$(LOCALEDIR)\" \
           -DSHAREDIR=\"$(SHAREDIR)\" \
           -DPOWERDIR=\"$(POWER_DIR)\" \
           -DROOT_UID=$(ROOT_UID) \
           -D_GNU_SOURCE


DEPS +=    bat_tray.h \
           common.h \
           config_file.h \
           defaults.h \
           getcore.h \
           getfreq.h \
           getgov.h \
           paramano.h \
           tray.h \
           paramano_set_interface.h

CFLAGS +=  -I/usr/include/gtk-2.0 \
           -I/usr/lib/gtk-2.0/include \
           -I/usr/include/pango-1.0 \
           -I/usr/include/cairo \
           -I/usr/include/gdk-pixbuf-2.0 \
           -I/usr/include/atk-1.0 \
           -I/usr/include/glib-2.0 \
           -I/usr/lib/glib-2.0/include \
           -Wall \
           -D_=gettext \
           $(DEFS)

LDFLAGS += -lgtk-x11-2.0 \
           -lgobject-2.0 \
           -lglib-2.0
