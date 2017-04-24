include config.mk

.PHONY: all lang paramano-extra clean strip install


all: paramano paramano-set lang paramano-extra


# main paramano system tray program
paramano:	bat_tray.o \
			common.o \
			config_file.o \
			defaults.o \
			getcore.o \
			getfreq.o \
			getgov.o \
			paramano.o \
			tray.o \
			paramano_set_interface.o


# paramano-set governor/frequency setting utility
paramano-set: \
			paramano_set.o \
			common.o \
			getcore.o \
			getfreq.o \
			getgov.o
	$(CC) -o $@ $^ $(LDFLAGS)


#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS) $(DEFS)


# Make language file(s)
lang:
	msgfmt -c -o lc/fr.mo lc/fr.po


# Prepare template config file
paramano-extra:
	for file in paramano.conf paramano.desktop ; do \
		sed	-e 's:SHAREDIR:$(SHAREDIR):g' \
			-e 's:PARAMANO_CONF:$(PARAMANO_CONF):g'  \
			-e 's:PARAMANO:$(PARAMANO):g' \
			$$file.src > $$file ; \
	done


# Strip all symbols from binaries
strip:
	strip -s paramano paramano-set


# Remove generated files
clean:
	rm -f paramano paramano-set *.o lc/*.mo paramano.conf paramano.desktop


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
