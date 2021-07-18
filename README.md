# sck
* [Installation](#installation)
	* [GTK/Qt](#gtkqt)
	* [Polybar](#polybar)
	* [Dmenu](#dmenu)
	* [Emoji support](#emoji-support)
	* [Finalizing](#finalizing)
* [Keybindings](#keybindings)
	* [dwm](#dwm)
	* [st](#st)
	* [tabbed](#tabbed)

![](.github/screenshot.png)

## Installation
Install the following dependencies
```bash
pacman -S xorg-server xorg-xinit xorg-xset xclip \
	feh imwheel maim \
	libxinerama yajl \
	noto-fonts noto-fonts-emoji 

yay -S picom-rounded-corners \
	ttf-fira-code nerd-fonts-symbols
```
To support all polybar modules, the following packages are also required
```bash
pacman -S pulseaudio pulseaudio-alsa pulseaudio-bluetooth \
	bluez-utils networkmanager
```

### GTK/Qt
Kvantum is used to set a style for all Qt apps, it requires `QT_STYLE_OVERRIDE=kvantum` to be loaded into the environment. Both GTK and Qt will be automatically configured with a dark version of *Adapta* when running `./install.bash all|confs`. 
```bash
pacman -S adapta-gtk-theme kvantum-qt5
```

### Polybar
The `monitor` option in `./confs/polybar.ini` needs to be manually modified to match one of the monitor names returned from `polybar --list-monitors`.

A patched version of polybar is required to display the current DWM layout, [polybar-dwm-module](https://github.com/mihirlad55/polybar-dwm-module), this version of polybar can be installed from the [AUR](https://aur.archlinux.org/packages/polybar-dwm-module) 

```bash
yay -S polybar-dwm-module
```

### Dmenu
Note that one may need to delete the cache at `~/.cache/dmenu_run` and potentially logout before dmenu is able to find all binaries in the `$PATH`.

### Emoji support
A patch to `libxft` is required to prevent st and dmenu from crashing when emojis are displayed. On Arch based distributions one can install a patched version of the library, [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR. 
```bash
yay -S libxft-bgra
```
On Gentoo one can resolve this by introducing a [patch](https://wiki.gentoo.org/wiki//etc/portage/patches) into portage for the `libXft` library and (re)installing it
```bash
sudo ./helper/libxft-patch.bash
```

### Finalizing
To build and install each program along with all of the configuration files run
```bash
./install.bash all
```
If no errors occurred it should now be possible to launch the environment with `startx`.

## Keybindings

### dwm
* Quit X: <kbd>Meta</kbd> <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>q</kbd> 
* Cycle between windows: <kbd>Meta</kbd> <kbd>Tab</kbd> or <kbd>Ctrl</kbd> <kbd>q</kbd>
* Close current window: <kbd>Meta</kbd> <kbd>q</kbd>
* Tiled layout: <kbd>Meta</kbd> <kbd>g</kbd>
	* Resize windows horizontally: <kbd>Meta</kbd> <kbd>h</kbd> / <kbd>Meta</kbd> <kbd>l</kbd>
	* Move current window in the stack: <kbd>Meta</kbd> <kbd>j</kbd> / <kbd>Meta</kbd> <kbd>k</kbd>
* Floating layout: <kbd>Meta</kbd> <kbd>f</kbd>
	* Resize windows: <kbd>Meta</kbd> <kbd>Right mouse button</kbd>
	* Move windows: <kbd>Meta</kbd> <kbd>Left mouse button</kbd>
* Monocle layout: <kbd>Meta</kbd> <kbd>m</kbd>
* Fullscreen current window: <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>f</kbd>
* Screenshot (saves to `~/Pictures/Screens` by default): <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>3</kbd>
* Open emoji picker: <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>Space</kbd> 
* Open terminal: <kbd>Meta</kbd> <kbd>Enter</kbd> 
* Open terminal in `tabbed`: <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>Enter</kbd> 
* Open dmenu: <kbd>Meta</kbd> <kbd>Space</kbd> 
* Open browser: <kbd>Meta</kbd> <kbd>b</kbd> 
* Open `pulsemixer`: <kbd>Meta</kbd> <kbd>p</kbd> 
* Save current clipboard contents to `/tmp/local-clip`: <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>s</kbd> 
* Load contents of `/tmp/rem-clip` into clipboard: <kbd>Meta</kbd> <kbd>Shift</kbd> <kbd>l</kbd> 
* The audio keys (mute/unmute etc.) interact with pulseaudio by default, if the project is compiled with `USE_ALSA` defined, commands from `alsa-utils` are used instead

### st
* Scroll: <kbd>Ctrl</kbd> <kbd>j</kbd> / <kbd>Ctrl</kbd> <kbd>k</kbd>
* Zoom: <kbd>Ctrl</kbd> <kbd>+</kbd> / <kbd>Ctrl</kbd> <kbd>-</kbd>
* Reset zoom: <kbd>Ctrl</kbd> <kbd>0</kbd> 
* Copy selection: <kbd>Meta</kbd> <kbd>c</kbd>
* Paste selection: <kbd>Meta</kbd> <kbd>v</kbd>
* Open selection for URLs in the current buffer: <kbd>Meta</kbd> <kbd>o</kbd>

### tabbed
* Open new tab: <kbd>Meta</kbd> <kbd>t</kbd>
* Close tab: <kbd>Meta</kbd> <kbd>w</kbd> 
* Cycle through tabs: <kbd>Ctrl</kbd> <kbd>Tab</kbd> / <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>Tab</kbd> 
* Move current tab: <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>h</kbd> / <kbd>l</kbd>
* Go to tab by index: <kbd>Meta</kbd> <kbd>1</kbd> - <kbd>9</kbd> 

