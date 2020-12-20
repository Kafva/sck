#!/bin/bash
#≈≈≈≈≈≈≈≈≈≈≈≈≈ Functions ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈#
bar_audio ()
{
	status=$(amixer sget Master | tail -n1 | sed -r "s/.*\[(.*)\]/\1/")
	percent=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")

	[ "$status" = "off" ] && printf "ﱝ " || {
		case "$percent" in
			[0-9]|[1-2][0-9])	printf "奔  " ;;
			[3-5][0-9]) 		printf "墳  " ;; 
			[6-9][0-9]|100) 	printf " " ;; 
		esac
	}
}

bar_wifi ()
{
	ip address | grep -qE 'inet ([0-9]{1,3}\.){3}[0-9]{1,3}.* global' && printf "直" || printf "睊"
}

#≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈#
SEP=' '

while :
do
	xsetroot -name "  $(bar_wifi)   $SEP  $(bar_audio) $SEP $(date +%H:%M)  "
	sleep 1
done
