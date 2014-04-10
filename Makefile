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


trayfreq_CFLAGS			=	$(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall
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

trayfreq_set_CFLAGS		=	$(GTK_CFLAGS) $(GLIB_CFLAGS) -Wall
trayfreq_set_LDFLAGS	=	$(GTK_LIBS) $(GLIB_LIBS) -lm
trayfreq_set_SOURCES	=	trayfreq_set/trayfreq_set.c \
							freq_tray/getfreq.c \
							freq_tray/getcore.c


########################################################################
# Make entire suite
all: trayfreq-en trayfreq-fr trayfreq-set-en trayfreq-set-fr
########################################################################

########################################################################
# Make trayfreq-set program for setting governors
trayfreq-set-en:
	$(CC) -o trayfreq-set-en $(trayfreq_set_SOURCES) $(trayfreq_set_CFLAGS)  $(trayfreq_set_LDFLAGS)

trayfreq-set-fr:
	$(CC) -o trayfreq-set-fr $(trayfreq_set_SOURCES) $(trayfreq_set_CFLAGS)  $(trayfreq_set_LDFLAGS) -DLANG_FR
########################################################################


########################################################################
# Make main trayfreq system tray program
trayfreq-en:
	$(CC) -o trayfreq-en $(trayfreq_SOURCES) $(trayfreq_CFLAGS)  $(trayfreq_LDFLAGS)

trayfreq-fr:
	$(CC) -o trayfreq-fr $(trayfreq_SOURCES) $(trayfreq_CFLAGS)  $(trayfreq_LDFLAGS) -DLANG_FR
########################################################################


########################################################################
# Remove generated files
clean:
	rm -f trayfreq-en trayfreq-set-en trayfreq-fr trayfreq-set-fr
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
########################################################################
