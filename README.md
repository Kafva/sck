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
pacman -S xorg-server xorg-xinit xorg-xset xclip xdotool xbindkeys \
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
Kvantum is used to set a style for all Qt apps, it requires `QT_STYLE_OVERRIDE=kvantum` to be configured in `/etc/enviroment` or `~/.zshrc` etc. Both GTK and Qt will be automatically configured with a dark version of *Adapta* when running `./install.bash all|confs`. 
```bash
pacman -S adapta-gtk-theme kvantum-qt5
```

### Polybar
A patched version of polybar is required to display the current DWM layout, [polybar-dwm-module](https://github.com/mihirlad55/polybar-dwm-module), this version of polybar can be installed from the [AUR](https://aur.archlinux.org/packages/polybar-dwm-module) 
```bash
yay -S polybar-dwm-module
```

* The `monitor` option in `./confs/polybar.ini` needs to be manually modified to match one of the monitor names returned from `polybar --list-monitors`
* An ALSA sink listed from `pacmd list-sinks` needs to be manually set for the `sink` attribute of the pulseaudio module
* The `./helper/bluetooth.sh` script needs to be modified with new MAC addresses to display connected devices

### Dmenu
Note that one may need to delete the cache at `~/.cache/dmenu_run` and potentially logout before dmenu is able to find all binaries in your `$PATH`.

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
Note that `xbindkey` is used to rebind the modifier used in web browsers to manage tabs from <kbd>Ctrl</kbd> to <kbd>Super</kbd>, e.g. new tabs are opened with <kbd>Super</kbd> <kbd>t</kbd>. 

### dwm
* Cycle between windows: <kbd>Super</kbd> <kbd>Tab</kbd> or <kbd>Ctrl</kbd> <kbd>q</kbd>
* Move to next/previous tag: <kbd>Super</kbd> <kbd>&leftarrow</kbd> / <kbd>&rightarrow</kbd>
* Move to tag by index (*§* is used in place of 6): <kbd>Ctrl</kbd> <kbd>1</kbd> - <kbd>5</kbd>
* Move current window to next/previous tag: <kbd>Ctrl</kbd> <kbd>Shift</kbd>  <kbd>&leftarrow</kbd> / <kbd>&rightarrow</kbd>
* Close current window: <kbd>Super</kbd> <kbd>q</kbd>
* Tiled layout: <kbd>Super</kbd> <kbd>g</kbd>
	* Resize windows horizontally: <kbd>Super</kbd> <kbd>h</kbd> / <kbd>Super</kbd> <kbd>l</kbd>
	* Move current window in the stack: <kbd>Super</kbd> <kbd>j</kbd> / <kbd>Super</kbd> <kbd>k</kbd>
* Floating layout: <kbd>Super</kbd> <kbd>f</kbd>
	* Resize windows: <kbd>Super</kbd> <kbd>Right mouse button</kbd>
	* Move windows: <kbd>Super</kbd> <kbd>Left mouse button</kbd>
* Monocle layout: <kbd>Super</kbd> <kbd>m</kbd>
* Fullscreen current window: <kbd>Super</kbd> <kbd>Shift</kbd> <kbd>f</kbd>
* Screenshot (saves to `~/Pictures/Screens` by default): <kbd>Super</kbd> <kbd>Shift</kbd> <kbd>3</kbd>
* Open emoji picker: <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>Space</kbd> 
* Open terminal: <kbd>Super</kbd> <kbd>Enter</kbd> 
* Open terminal in `tabbed`: <kbd>Super</kbd> <kbd>Shift</kbd> <kbd>Enter</kbd> 
* Open dmenu: <kbd>Super</kbd> <kbd>Space</kbd> 
* Open browser: <kbd>Super</kbd> <kbd>b</kbd> 
* Open `pulsemixer`: <kbd>Super</kbd> <kbd>p</kbd> 
* Save current clipboard contents to `/tmp/local-clip`: <kbd>Super</kbd> <kbd>Shift</kbd> <kbd>s</kbd> 
* Load contents of `/tmp/rem-clip` into clipboard: <kbd>Super</kbd> <kbd>Shift</kbd> <kbd>l</kbd> 
* The audio keys (mute/unmute etc.) interact with pulseaudio by default, if the project is compiled with `USE_ALSA` defined, commands from `alsa-utils` are used instead. Note that polybar is configured to only use pulseaudio.
* Quit X: <kbd>Super</kbd> <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>q</kbd> 

### st
* Scroll: <kbd>Ctrl</kbd> <kbd>j</kbd> / <kbd>Ctrl</kbd> <kbd>k</kbd>
* Zoom: <kbd>Ctrl</kbd> <kbd>+</kbd> / <kbd>Ctrl</kbd> <kbd>-</kbd>
* Reset zoom: <kbd>Ctrl</kbd> <kbd>0</kbd> 
* Copy selection: <kbd>Super</kbd> <kbd>c</kbd>
* Paste selection: <kbd>Super</kbd> <kbd>v</kbd>
* Open selection for URLs in the current buffer: <kbd>Super</kbd> <kbd>o</kbd>

### tabbed
* Open new tab: <kbd>Super</kbd> <kbd>t</kbd>
* Close tab: <kbd>Super</kbd> <kbd>w</kbd> 
* Cycle through tabs: <kbd>Ctrl</kbd> <kbd>Tab</kbd> / <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>Tab</kbd> 
* Move current tab: <kbd>Ctrl</kbd> <kbd>Shift</kbd> <kbd>h</kbd> / <kbd>l</kbd>
* Go to tab by index: <kbd>Super</kbd> <kbd>1</kbd> - <kbd>9</kbd> 
