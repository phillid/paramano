What?
=====

This is a fork of trayfreq which is intended to work on modern Archlinux systems (it'll probably work on other systems too).


Building
========
Due to KISS, I don't tend to use ./configure scripts for relatively small programs.
Instead, it's up to the user to check they have the right libraries.
The sort of parameters you might pass to a ./configure can instead be passed to make.

Important Note
--------------
Note that any parameters set here will be compiled into the programs.
If you're installing to a temporary directory (e.g. building a package for a package manager) then don't set the prefix to the temporary directory as this will become hard-coded into the programs.
Instead, set this when calling `make install`.

Here's a list:

* BINDIR to override default binary directory (`/usr/bin`) for trayfreq and trayfreq-set
* PREFIX to prepend to BINDIR, LOCALE_DIR etc
* LOCALE_DIR to override default of `/usr/share/locale`
* SUDO to override default sudo program `/usr/bin/sudo`
* MAKE to override default make program `make`
* CC to override default compiler `gcc`
* TRAYFREQ_SET to override default trayfreq-set program of `PREFIX/BINDIR/trayfreq-set`

If you'd like a huge amount of debug information every time you run trayfreq or trayfreq-set, then set DEBUG to something, eg:

	make all DEBUG=yeah


An example build line for a system with binaries in `/usr/bin`:

	make all


Quick (extreme) example for nutty system with binaries at `/exec` and sudo `/exec/sodu`:

	make all BINDIR=/exec SUDO=/exec/sodu


Installation
============
If you're using ArchLinux, just jump over to the AUR, download and unpack the tarball, `cd` to the newly unpacked folder and run `makepkg`.

For all other systems, you'll probably be compiling from source.
In that case, `make install` will install the package, making the assumption that:

* Binaries (trayfreq, trayfreq-set) will go in `/usr/bin`
* Locale directory starts at `/usr/share/locale`
* Your sysconfdir is `/etc` (can't currently be changed)
* You're installing to `/`

In general, a plain `make install` should work if you're installing straight to `/`, i.e. you're not building a package or anything.
If you *are* building a package or installing to a special dir, then you might want something like this:

	make install PREFIX=/path/to/package/temp/dir LOCALE_DIR=/usr/share/locale

This will prefix **all** paths with `/path/to/package/temp/dir` while installing.
LOCALE_DIR has to be overridden due to the stripping of `/usr/` from it when manually setting a prefix.
**Check the command lines as they go past.**
Now's the time to check that everything's going to go in the right place.

----------------------------------

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
