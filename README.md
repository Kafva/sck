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

## dwm

### Controls
* Open dmenu: <kbd>Meta</kbd> <kbd>Space</kbd> 
* Cycle between windows: <kbd>Meta</kbd> <kbd>Tab</kbd> or <kbd>Ctrl</kbd> <kbd>q</kbd>
* Close current window: <kbd>Meta</kbd> <kbd>q</kbd>
* Fullscreen current window: <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>f</kbd>
* Tiled layout: <kbd>Meta</kbd> <kbd>g</kbd>
    	* Resize windows horizontally: <kbd>Meta</kbd> <kbd>h</kbd> / <kbd>Meta</kbd> <kbd>l</kbd>
	* Move current window in the stack: <kbd>Meta</kbd> <kbd>j</kbd> / <kbd>Meta</kbd> <kbd>k</kbd>
* Floating layout: <kbd>Meta</kbd> <kbd>f</kbd>
	* Resize windows: <kbd>Meta</kbd> <kbd>Right mouse button</kbd>
	* Move windows: <kbd>Meta</kbd> <kbd>Left mouse button</kbd>
* Monocle layout: <kbd>Meta</kbd> <kbd>m</kbd>
* Screenshot (saves to `~/Pictures/Screens` by default): <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>3</kbd>
* Open emoji picker: <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>Space</kbd> 

## st

### Controls
* Scroll: <kbd>Ctrl</kbd> <kbd>j</kbd> / <kbd>Ctrl</kbd> <kbd>k</kbd>
* Zoom: <kbd>Ctrl</kbd> <kbd>+</kbd> / <kbd>Ctrl</kbd> <kbd>-</kbd>
* Reset zoom: <kbd>Ctrl</kbd> <kbd>0</kbd> 
* Copy selection: <kbd>Meta</kbd> <kbd>c</kbd>
* Paste selection: <kbd>Meta</kbd> <kbd>v</kbd>
* Open selection for URLs in the current buffer: <kbd>Meta</kbd> <kbd>o</kbd>


## Installation
The following fonts need to be installed
* Noto
* Nerd fonts
* Firacode

* Use picom-aur for rounded cornerns
* Dependencies
	- DWM-polybar
	- `maim`
* Patching method for polybar

## Dmenu
Note that one may need to delete the cache at `~/.cache/dmenu_run` and potentiallly logout before dmenu is able to find all binariies in the `$PATH`.

## Emoji support
A patch to `libxft` is required to prevent st and dmenu from crashing when emojis are displayed. On Arch based distributions one can install a patched version of the library, [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR. On Gentoo we can resolve this by introducing a [patch](https://wiki.gentoo.org/wiki//etc/portage/patches) into portage for the `libXft` library and (re)installing it
```bash
sudo ./helper/libxft-patch.bash
```
