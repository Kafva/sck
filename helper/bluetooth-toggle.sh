#!/bin/sh
bluetoothctl show | grep -q "Powered: yes" &&
	bluetoothctl power off || bluetoothctl power on
