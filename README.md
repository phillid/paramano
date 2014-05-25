What?
=====

This is a fork of trayfreq, intended to work on modern Linux systems.
The original trayfreq wasn't compatible with Archlinux, due to the migration away from a `/proc/acpi` directory.
I forked the project and got it working again.

If you're using ArchLinux, just jump over to the [AUR page for this software](https://aur.archlinux.org/packages/trayfreq-archlinux) and install it that way.

Despite the software's name, it should work on other distros as well.


Runtime Dependencies
--------------------

* gtk3
* sudo

Building
========
Due to KISS, I don't tend to use ./configure scripts for relatively small programs.
Instead, it's up to the user to check they have the right libraries.
The sort of parameters you might pass to a ./configure can instead be passed to make.

Here's a list:

* BINDIR to override default binary directory (`/usr/bin`) for trayfreq and trayfreq-set
* PREFIX to prefix all paths with something
* LOCALE_DIR to override default of `/usr/share/locale`
* SUDO to override default sudo program `/usr/bin/sudo`
* MAKE to override default make program `make`
* CC to override default compiler `gcc`
* TRAYFREQ_SET to override default trayfreq-set program of `PREFIX/BINDIR/trayfreq-set`
* DESTDIR (only for `make install` -- see below)

If you'd like a huge amount of debug information on the tty every time you run trayfreq or trayfreq-set, then set DEBUG to something, eg:

	make all DEBUG=yeah


Extreme example for nutty system with binaries at `/exec` and sudo `/exec/sodu`:

	make all BINDIR=/exec SUDO=/exec/sodu


Installation
============
A plain `make install` should work if you're installing straight to `/`, i.e. you're not building a package or anything.
If you *are* building a package or installing to a special dir, then you might want something like this:

	make install DESTDIR=/path/to/package/temp/dir

This will prefix **all** paths with `/path/to/package/temp/dir` while installing.

Autostarting
------------
`make install` will copy a .desktop file to /etc/xdg/autostart, meaning that all xdg-compliant window managers should start it automatically when Bob logs in.
Bob's WM starts these programs as root, thus he is fully able to change the governor.

Alice uses a non-xdg-compliant WM (e.g. dwm)  so trayfreq is run as the user `alice`.
She doesn't have permission to write to the files under `/sys/` so trayfreq can't change the governor.
Alice needs to make trayfreq run `trayfreq-set` through sudo.
This can be done in the configuration file.
Then, she also needs to give herself passwordless permission to run `trayfreq-set` through sudo:


    # ... (/etc/sudoers
	alice ALL = NOPASSWD: /usr/bin/trayfreq-set
	# ...

Simple.
