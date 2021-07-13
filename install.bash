#!/bin/bash
exitErr(){ echo -e "$1" >&2 ; exit 1; }
usage="usage: $(basename $0) [-h] <dmenu|st|dwm|all>"
helpStr="Build and install the specified program(s)"

while getopts ":h" opt
do
	case $opt in
		h) exitErr "$usage\n-----------\n$helpStr" ;;
		*) exitErr "$usage" ;;
	esac
done

shift $(($OPTIND - 1))

echo "$1" | grep -qE "^dwm|dmenu|st|all$" || exitErr "$usage"
echo "$1" | grep -qE "^dwm|all$" &&
	pgrep dwm > /dev/null && exitErr "Quit dwm before installation"

makeCmd(){
	make -C $1 clean
	sudo make -C $1 install
}

case $1 in 
	all) 
		makeCmd dwm
		makeCmd dmenu
		makeCmd st
		;;
	*) makeCmd $1
		;;
esac

