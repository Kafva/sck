#!/bin/sh
#	Get MAC addresses: `system_profiler SPBluetoothDataType`
#	Airpods: 18:81:0E:C8:64:20
pro_controller="E0:F6:B5:66:6E:9D"
beoplay_h5="00:09:A7:0D:F5:F4"

function addDeviceIfConnected(){
	bluetoothctl info $1 | grep -q "Connected: yes" && output="${output} $2" 
}

if $(bluetoothctl show | grep -q "Powered: yes"); then
	output=""
	addDeviceIfConnected $beoplay_h5 " " 
	addDeviceIfConnected $pro_controller " " 
	printf "$output"
else
	printf ""
fi
