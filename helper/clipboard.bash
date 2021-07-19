#!/bin/bash
remClip=/tmp/rem-clip
localClip=/tmp/local-clip

# <Super> <Shift> <l>
[ "$1" = load ] && [ -f $remClip ] && 
	cat $remClip | tr -d "\n" | xclip -selection clipboard

# <Super> <Shift> <s>
[ "$1" = save ] && 
	xclip -out -selection clipboard > $localClip
