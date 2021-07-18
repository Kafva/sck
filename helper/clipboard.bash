#!/bin/bash
remClip=/tmp/rem-clip
localClip=/tmp/local-clip

# <Meta> <Shift> <l>
[ "$1" = load ] && [ -f $remClip ] && 
	cat $remClip | tr -d "\n" | xclip -selection clipboard

# <Meta> <Shift> <s>
[ "$1" = save ] && 
	xclip -out -selection clipboard > $localClip
