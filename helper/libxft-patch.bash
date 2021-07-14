#!/bin/bash
# See https://forums.gentoo.org/viewtopic-t-1110484-start-0.html
# 	curl https://gitlab.freedesktop.org/mawww/libxft/-/commit/7808631e7a9a605d5fe7a1077129c658d9ec47fc.diff > 
#		helper/libxft-bgra.patch

[ $(whoami) != root ] && { echo "Run as root"; exit 1 ; }

PROJECT_ROOT=$(realpath $0 | sed "s@/helper/$(basename $0)@@")

mkdir -p /etc/portage/patches/x11-libs/libXft 
cp $PROJECT_ROOT/helper/libxft-bgra.patch /etc/portage/patches/x11-libs/libXft &&
emerge --quiet-build -a x11-libs/libXft
