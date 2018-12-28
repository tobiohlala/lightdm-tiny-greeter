# LightDM Tiny Greeter

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/2dbb11ae343f46e79a8f577a74670f10)](https://www.codacy.com/app/off-world/lightdm-tiny-greeter?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=off-world/lightdm-tiny-greeter&amp;utm_campaign=Badge_Grade)

A tiny yet customizable GTK3 LightDM Greeter with focus on code and minimalism.

![default](https://i.imgur.com/yFMcb4o.png)

## Installation

```bash
git clone https://github.com/off-world/lightdm-tiny-greeter
cd lightdm-tiny-greeter
make
sudo make install
```

## Configuration

All configuration and customization goes into `config.h` prior compilation.

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

-   `glib` `libglib-2.0`
-   `gtk3` `libgtk-3 (>= 3.22)`
-   `lightdm` `liblightdm-gobject-1 (>= 1.19.1)`

## Showcase

![screenshot1](https://i.imgur.com/YtiGpey.png)  
[#1](https://gist.github.com/off-world/573ea3b79829fb31ce7b27c337e62926)

![screenshot2](https://i.imgur.com/TxCElXF.png)  
[#2](https://gist.github.com/off-world/fd4c5b183dc6e0e4d3ada95131969a45)

![screenshot3](https://i.imgur.com/Ay56rA3.png)  
[#3](https://gist.github.com/off-world/ad853fb1faca2c6c67b332ff3d3a7a21)

![screenshot4](https://i.imgur.com/Ci9RJ0y.png)  
[#4](https://gist.github.com/alaughlin/f7eac0c88d2939428dcd2ffb67353f1a)
