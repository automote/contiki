modprobe ftdi_sio vendor=0x403 product=0xa6d1
modprobe ftdi_sio
echo 0403 a6d1 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
ls /dev/ttyUSB0 && ls /dev/ttyUSB1
