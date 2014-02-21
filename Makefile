INSTALL_PATH=/

all:
	make all --directory=./src/

clean:
	make clean --directory=./src/

install:
	mkdir -p $(INSTALL_PATH)/usr/share/trayfreq/
	cp data/*.png $(INSTALL_PATH)/usr/share/trayfreq/
	install -D data/trayfreq.config $(INSTALL_PATH)/usr/share/trayfreq/trayfreq.config
	install -D data/trayfreq.desktop $(INSTALL_PATH)/etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 src/trayfreq $(INSTALL_PATH)/usr/bin/trayfreq
	install -Dm 755 src/trayfreq-set $(INSTALL_PATH)/usr/bin/trayfreq-set
