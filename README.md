# LightDM Tiny Greeter

a minimalists Greeter

![](https://i.imgur.com/yhZokfM.png))

# Description

A Tiny GTK3 LightDM Greeter with focus on code and minimalism.

## Installation

```bash
git clone https://github.com/off-world/lightdm-tiny-greeter
cd lightdm-tiny-greeter
make
sudo make install
```

To use the greeter set `greeter-session=lightdm-tiny-greeter` in `/etc/lightdm/lightdm.conf`.

## Configuration

Configuration and customization can be done by editing `config.h`.

- `user_text`: text when prompting for login
- `pass_text`: text when prompting for password
- `session`: session to start
- `style`: ui styling via [CSS](https://developer.gnome.org/gtk3/stable/chap-css-overview.html)
- `ui`: ui definition via [XML](https://developer.gnome.org/pygtk/stable/class-gtkbuilder.html)

## Dependencies

Build Dependencies

- `gtk+3-devel`
- `liblightdm-gobject`

Runtime Dependencies

- `gtk+3`
- `lightdm`

