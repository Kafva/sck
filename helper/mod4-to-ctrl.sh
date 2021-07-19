#!/bin/sh
# $1 -- Key to press
# Reload with `xbindkeys --poll-rc`
# NOTE only seems to work properly in firefox
browser_regex="WM_CLASS.*(firefox(-bin)?|chromium(-bin)?|brave(-bin)?)"
window_id=$(xdotool getactivewindow)
logPath=/tmp/xbindkeys.log

if $(echo $(xprop -id $window_id) | grep -qE "$browser_regex"); then
	# Inside a web browser translate it to Ctrl+[...]
	echo "Remapping mod4-$1 -> ctrl: $window_id" >> $logPath
	xdotool key --window $window_id --clearmodifiers ctrl+$1
else
	# When Super+[1-9] is invoked outside a web browser, pass it on as is
	echo "Skipping mod4-$1 remap: $window_id (not a browser)" >> $logPath
	xdotool key --window $window_id --clearmodifiers super+$1
fi
