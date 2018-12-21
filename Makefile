PREFIX = /usr/local

PACKAGE = `pkg-config --libs --cflags gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`
LIBS = `pkg-config --libs gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`
CFLAGS = -std=c99 -pedantic -Wall -O2 -g
CC = gcc


all: clean build

build: lightdm-tiny-greeter.o
	$(CC) $(LIBS) lightdm-tiny-greeter.o -o lightdm-tiny-greeter

.PHONY: install
install:
	$(shell mkdir -p /usr/share/xgreeters)
	cp lightdm-tiny-greeter.desktop /usr/share/xgreeters/lightdm-tiny-greeter.desktop
	cp lightdm-tiny-greeter $(PREFIX)/bin/lightdm-tiny-greeter

.PHONY: uninstall
uninstall:
	rm /usr/share/xgreeters/lightdm-tiny-greeter.desktop
	rm $(PREFIX)/bin/lightdm-tiny-greeter

lightdm-tiny-greeter.o: lightdm-tiny-greeter.c config.h
	$(CC) $(CFLAGS) -c $< -o $@ $(PACKAGE)

.PHONY: clean
clean:
	$(RM) *.o

