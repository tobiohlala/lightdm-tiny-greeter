PREFIX = /usr
CC = gcc
RM = rm -f

CFLAGS = -std=c99 -pedantic -Wall -O2
PKGS = `pkg-config --libs --cflags gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`
LIBS = `pkg-config --libs gtk+-3.0 liblightdm-gobject-1 gmodule-export-2.0`

TARGET = lightdm-tiny-greeter

.PHONY: clean all install uninstall


all: $(TARGET)

$(TARGET): lightdm-tiny-greeter.o
	$(CC) -o $@ $^ $(LIBS)

lightdm-tiny-greeter.o: lightdm-tiny-greeter.c config.h
	$(CC) $(CFLAGS) -c $^ $(PKGS)

install:
	$(shell mkdir -p /usr/share/xgreeters)
	cp lightdm-tiny-greeter.desktop /usr/share/xgreeters/lightdm-tiny-greeter.desktop
	cp lightdm-tiny-greeter $(PREFIX)/bin/lightdm-tiny-greeter

uninstall:
	$(RM) /usr/share/xgreeters/lightdm-tiny-greeter.desktop
	$(RM) $(PREFIX)/bin/lightdm-tiny-greeter

clean:
	$(RM) *.o
