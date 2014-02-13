INSTALL_PATH=/

all:
	make all --directory=./src/

install:
	install -D data/*.png $(INSTALL_PATH)/usr/share/trayfreq/
	install -D data/trayfreq.config $(INSTALL_PATH)/usr/share/trayfreq/trayfreq.config
	install -D data/trayfreq.desktop $(INSTALL_PATH)/etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 src/trayfreq $(INSTALL_PATH)/usr/bin/trayfreq
	install -Dm 755 src/trayfreq-set $(INSTALL_PATH)/usr/bin/trayfreq-set
