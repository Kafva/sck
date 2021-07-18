#!/bin/bash
exitErr(){ echo -e "$1" >&2 ; exit 1; }
usage="usage: $(basename $0) [-h] <dmenu|st|dwm|tabbed|confs|all>"
helpStr="Build and install the specified program(s). The 'confs' option will produce symlinks for config files under ./conf."

while getopts ":h" opt
do
	case $opt in
		h) exitErr "$usage\n-----------\n$helpStr" ;;
		*) exitErr "$usage" ;;
	esac
done

shift $(($OPTIND - 1))

echo "$1" | grep -qE "^dwm|dmenu|st|tabbed|confs|all$" || exitErr "$usage"
echo "$1" | grep -qE "^dwm|all$" &&
	pgrep dwm > /dev/null && exitErr "Quit dwm before installation"

makeCmd(){
	make -C $1 clean
	sudo make -C $1 install
}

linkConfs(){
	project=$(dirname $(realpath $0))

	# Symlink dotfiles
	rm -rf ~/.config/Kvantum 2> /dev/null
	mkdir -p ~/.config/polybar
	mkdir -p ~/.config/gtk-3.0
	ln -sf $project/conf/Kvantum ~/.config/Kvantum
	ln -sf $project/conf/gtk-3.0.ini ~/.config/gtk-3.0/settings.ini
	ln -sf $project/conf/polybar.ini ~/.config/polybar/config.ini
	ln -sf $project/conf/picom.conf ~/.config/picom.conf # Transparancy and rounded corners
	ln -sf $project/conf/xinitrc ~/.xinitrc 	# Commands to run upon calling `startx`
	ln -sf $project/conf/Xresources ~/.Xresources 	# Defaullt settings for X
	ln -sf $project/conf/imwheelrc ~/.imwheelrc 	# Custom scroll speed for applications
}

case $1 in 
	all) 
		makeCmd dwm
		makeCmd dmenu
		makeCmd st
		makeCmd tabbed

		linkConfs
		;;
	confs)
		linkConfs
		;;
	*) makeCmd $1
		;;
esac

