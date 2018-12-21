# LightDM Tiny Greeter

A tiny yet customizable GTK3 LightDM Greeter with focus on code and minimalism.

**Screenshots**

![default](https://i.imgur.com/yFMcb4o.png)
![custom1](https://i.imgur.com/YtiGpey.png)

## Installation

```bash
git clone https://github.com/off-world/lightdm-tiny-greeter
cd lightdm-tiny-greeter
make
sudo make install
```

## Configuration

Configuration and customization can be done by editing `config.h`.

  - `user_text`: text when prompting for login
  - `pass_text`: text when prompting for password
  - `session`: session to start
  - `style`: ui styling via [CSS](https://developer.gnome.org/gtk3/stable/chap-css-overview.html)
  - `ui`: ui definition via [XML](https://developer.gnome.org/pygtk/stable/class-gtkbuilder.html)

## Setup

/etc/lightdm/lightdm.conf
```
[Seat:*]
...
greeter-session=lightdm-tiny-greeter
```

## Dependencies

  - `gtk+3` `gtk+3-devel`
  - `glib` `glib-devel`
  - `lightdm` `lightdm-devel`

