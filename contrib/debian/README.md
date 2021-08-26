
Debian
====================
This directory contains files used to package ibacoind/ibacoin-qt
for Debian-based Linux systems. If you compile ibacoind/ibacoin-qt yourself, there are some useful files here.

## ibacoin: URI support ##


ibacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ibacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ibacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/ibacoin128.png` to `/usr/share/pixmaps`

ibacoin-qt.protocol (KDE)

