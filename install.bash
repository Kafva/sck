#!/bin/bash
exitErr(){ echo -e "$1" >&2 ; exit 1; }
usage="usage: $(basename $0) [-msd]"
helpStr="\t-m dmenu\n\t-s st\n\t-d dwm"

while getopts ":hmsd" opt
do
	case $opt in
		h) exitErr "$usage\n$helpStr" ;;
		[msd]) flag=${flag}${opt} ;;
		*) exitErr "$usage\n$helpStr" ;;
	esac
done

shift $(($OPTIND - 1))

[ -z "$flag" ] && exitErr "$usage\n$helpStr"

#----------------------------#

exec_path=~/bin


[ "$flag" = m ] && {

make -C dmenu clean && make -C dmenu &&
	cp dmenu/dmenu $exec_path/
	cp dmenu/dmenu_* $exec_path/
} 

printf "$flag" | grep -q 's' && make -C st clean && make -C st && cp st/st $exec_path/
printf "$flag" | grep -q 'd' && make -C dwm clean && make -C dwm && cp dwm/dwm $exec_path/
