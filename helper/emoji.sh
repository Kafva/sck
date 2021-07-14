#!/bin/sh
cat $(realpath "$0" | sed "s/$(basename $0)//")/emojis.txt | 
	dmenu -i -l 10 | awk '{print $1}' | tr -d '\n' | xclip -selection clipboard
