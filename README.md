# LightDM Tiny Greeter

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/2dbb11ae343f46e79a8f577a74670f10)](https://www.codacy.com/app/off-world/lightdm-tiny-greeter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=off-world/lightdm-tiny-greeter&amp;utm_campaign=Badge_Grade)

A tiny yet customizable GTK3 LightDM Greeter with focus on code and minimalism.

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

| Variable  | Meaning                                                                                 |
|-----------|-----------------------------------------------------------------------------------------|
| user_text | text when prompting for login                                                           |
| pass_text | text when prompting for password                                                        |
| session   | session to start (name of a desktop-entry located in /usr/share/xsessions)              |
| style     | UI styling via [CSS](https://developer.gnome.org/gtk3/stable/chap-css-overview.html)    |
| ui        | UI definition via [XML](https://developer.gnome.org/pygtk/stable/class-gtkbuilder.html) |

## Setup

/etc/lightdm/lightdm.conf
```config
[Seat:*]
...
greeter-session=lightdm-tiny-greeter
```

## Dependencies

-   `gtk+3` `gtk+3-devel`
-   `glib` `glib-devel`
-   `lightdm` `lightdm-devel`
