#!/bin/sh
# The script will recieve all text from the current 'st' window on stdin and will
# prompt a dmenu dialog to open each one
urls=$(grep -aoE "https?://[-a-zA-Z0-9.]+(:[0-9]+)?(/[-a-zA-Z0-9./@$&%?$\#=_~]*)?" | uniq)

function setOpenTool {
	which $1 &> /dev/null && openTool=$1
}

setOpenTool firefox
[ -z "$openTool" ] && setOpenTool firefox-bin
[ -z "$openTool" ] && setOpenTool chromium
[ -z "$openTool" ] && setOpenTool brave
[ -z "$openTool" ] && exit 1 

$openTool $(printf "$urls" | dmenu -i -l 10)
