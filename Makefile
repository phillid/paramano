all:
	make all --directory=./src/

install:
	install -D data/*.png /usr/share/trayfreq/
	install -D data/trayfreq.config /usr/share/trayfreq/trayfreq.config
	install -D data/trayfreq.desktop /etc/xdg/autostart/trayfreq.desktop

	install -Dm 755 src/trayfreq /usr/bin/trayfreq
	install -Dm 755 src/trayfreq-set /usr/bin/trayfreq-set