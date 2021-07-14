#!/bin/bash
exitErr(){ echo -e "$1" >&2 ; exit 1; }
usage="usage: $(basename $0) -p <primary-color> -b <bg-color> -a <bg-alt-color>"
helpStr=""

while getopts ":hp:b:a:" opt
do
	case $opt in
		h) exitErr "$usage\n-----------\n$helpStr" ;;
		*) exitErr "$usage" ;;
	esac
done

shift $(($OPTIND - 1))

[ -z "$1" ] && exitErr "$usage"

#----------------------------#
