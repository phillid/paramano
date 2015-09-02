What?
=====
This is a fork of trayfreq. It provides two icons in your system tray; one for your battery and one for your CPU.
Hover the mouse over each for information, or right click the CPU to switch governors and frequencies.
Simple.


Installation
------------
For ArchLinux: [Paramano on AUR](https://aur.archlinux.org/packages/paramano/).

For other distros, you'll likely want to install Paramano using your package manager, creating a package if one doesn't exist in your distro's repositories.

In most case a simple workflow like "make && make install" is all that is needed.


Dependencies
------------

* gtk3
* sudo


Building
========
Due to KISS, I don't tend to use ./configure scripts for relatively small programs.
The sort of parameters you might pass to a ./configure can instead be passed to make.

Here's a list:

* BINDIR to override default binary directory (`/usr/bin`) for paramano and paramano-set
* PREFIX to prefix all paths with something
* SHAREDIR to override default of `/usr/share/`
* LOCALEDIR to override default of `SHAREDIR/locale`
* SUDO to override default sudo program `BINDIR/sudo`
* MAKE to override default make program `make`
* CC to override default compiler `gcc`
* PARAMANO_SET to override default paramano-set program of `BINDIR/paramano-set`
* DEBUG can be set to anything to build a huge amount of debug output stuff into parmano and parmano-set
* DESTDIR (only for `make install`)


FAQ
===
Changing the governor/frequency doesn't work!
---------------------------------------------
You need root permissions to change the governor or frequency.
Paramano will detect if it's not being run as root, and attempt to use sudo to elevate any calls to `paramano-set` to root.
However, this requires passwordless sudo access to `paramano-set`.
Here is an example for the user `alice`:

    # ... (/etc/sudoers)
	alice ALL = NOPASSWD: /usr/bin/paramano-set
	# ...

You might like to make a group if you have numerous users who you wish to grant this permission.
