# Tabsize: 4

MAKE = make
CC = gcc
INSTALL_PATH=/

GLIB_CFLAGS	=	-I/usr/include/glib-2.0 \
				-I/usr/lib/glib-2.0/include
GLIB_LIBS	=	-lglib-2.0

GTK_CFLAGS	=	-I/usr/include/gtk-2.0 \
				-I/usr/lib/gtk-2.0/include \
				-I/usr/include/pango-1.0 \
				-I/usr/include/cairo \
				-I/usr/include/gdk-pixbuf-2.0 \
				-I/usr/include/atk-1.0

GTK_LIBS	=	-lgtk-x11-2.0 \
				-lgobject-2.0


trayfreq_CFLAGS			=	$(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall -D_=gettext
trayfreq_LDFLAGS		=	$(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_SOURCES		=	freq_tray/getcore.c \
							freq_tray/getfreq.c \
							freq_tray/getgov.c \
							tray.c \
							trayfreq.c \
							widget_manager.c \
							trayfreq_set/trayfreq_set_interface.c \
							config_file.c \
							defaults.c \
							bat_tray/bat_tray.c \
							common.c

trayfreq_set_CFLAGS		=	$(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall -D_=gettext
trayfreq_set_LDFLAGS	=	$(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_set_SOURCES	=	trayfreq_set/trayfreq_set.c \
							freq_tray/getfreq.c \
							freq_tray/getcore.c


########################################################################
# Make entire suite
all: trayfreq trayfreq-set
########################################################################

########################################################################
# Make trayfreq-set program for setting governors
trayfreq-set:
	$(CC) -o trayfreq-set $(trayfreq_set_SOURCES) $(trayfreq_set_CFLAGS)  $(trayfreq_set_LDFLAGS)
########################################################################


########################################################################
# Make main trayfreq system tray program
trayfreq:
	$(CC) -o trayfreq $(trayfreq_SOURCES) $(trayfreq_CFLAGS)  $(trayfreq_LDFLAGS)
########################################################################


########################################################################
# Remove generated files
clean:
	rm -f trayfreq trayfreq-set
########################################################################


########################################################################
# Install entire suite
install:
	mkdir -p $(INSTALL_PATH)/usr/share/trayfreq/
	cp data/*.png $(INSTALL_PATH)/usr/share/trayfreq/
	install -D data/trayfreq.config $(INSTALL_PATH)/usr/share/trayfreq/trayfreq.config
	install -D data/trayfreq.desktop $(INSTALL_PATH)/etc/xdg/autostart/trayfreq.desktop
	install -Dm 755 trayfreq $(INSTALL_PATH)/usr/bin/trayfreq
	install -Dm 755 trayfreq-set $(INSTALL_PATH)/usr/bin/trayfreq-set
	ln -s /usr/share/licenses/common/GLPv3/license.txt $(INSTALL_PATH)/usr/share/trayfreq/LICENCE
########################################################################
