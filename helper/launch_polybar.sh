#!/usr/bin/env sh

killall -q polybar

# Wait until the processes have been shut down
while pgrep -u $UID -x polybar >/dev/null; do sleep 1; done

# Launch the main bar with the [-r] flag for automatic
# updates when the config is changed
polybar -r main -c ~/.config/polybar/config.ini &