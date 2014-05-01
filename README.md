What?
=====

This is a fork of trayfreq which is intended to work on modern Archlinux systems (it'll probably work on other systems too).



Installation
============
The basic installation's standard:

make install

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
