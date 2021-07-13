# sck
Fork of dwm including a polybar configuration based on [polybar-dwm-module](https://github.com/mihirlad55/polybar-dwm-module) and the following patches

* dwm-actualfullscreen-20191112-cb3f58a.diff
* dwm-anybar-20200905-bb2e722.diff
* dwm-focusadjacenttag-6.0.diff
* dwm-ipc-20201106-f04cac6.diff
* dwm-pertag-6.2.diff
* dwm-push-20201112-61bb8b2.diff

with some additional fixes, for example, *focusadjacenttag* does not work out of the box with *pertag*. 

The paths referenced in `dwm/config.h` for `launch.sh` and scripts under `~/linsc` need to be modified upon installation and the polybar configurations under `dwm/polybar` needs to be moved into `~/.config/polybar`. Changes based on the particular environment such as monitor, font size etc. can be tweaked in `polybar/config.ini`. 

![](.github/screenshot.png)

## Installation

* Dependencies
	- Noto color emoji
	- firacode
	- DWM-polybar
	- `maim`
* Patching method for polybar
* Tabbed could be nice
* Dmenu setup
* libxft-bgra https://forums.gentoo.org/viewtopic-t-1110484-start-0.html
* rounded corners https://github.com/igor37/dwm-rounded-corners/blob/master/dwm-rounded-gaps-fullscreen.diff 

## Dmenu
Note that one may need to delete the cache at `~/.cache/dmenu_run` and potentiallly logout before dmenu is able to find all binariies in the `$PATH`.

## Emoji support
A patch to `libxft` is required to prevent st and dmenu from crashing when emojis are displayed. On Arch based distributions one can install a patched version of the library, [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR. On Gentoo we can resolve this by introducing a [patch](https://wiki.gentoo.org/wiki//etc/portage/patches) into portage for the `libXft` library and (re)installing it
```bash
sudo ./scripts/libxft-patch.bash
```
