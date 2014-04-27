Installation
============
The basic installation's standard:

make install

----------------------------------

Autostarting
------------
`make install` will copy a .desktop file over to /etc/xdg/autostart, meaning that all xdg-compliant window managers should start it automatically when you log in.
As far as I am aware, they start trayfreq as root, thus it is fully able to change the governor.

Personally, I use a non-xdg-compliant WM (dwm) so trayfreq needs to be run with sudo in my xinitrc.
To avoid having to enter my password each time the xinitrc is run, I added this rule to my `/etc/sudoers`:

    # ... (/etc/sudoers
	david ALL = NOPASSWD: /usr/bin/trayfreq
	# ...

Simple.
