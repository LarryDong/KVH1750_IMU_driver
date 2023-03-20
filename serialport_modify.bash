
# change the serial port of ttyUSB0.

port='ttyUSB0'
echo "Change: ${port}"

sudo chmod 777 /dev/$port
sudo sh -c "echo 1 > /sys/bus/usb-serial/devices/$port/latency_timer"
echo "Change latency_timer' to: "
cat /sys/bus/usb-serial/devices/$port/latency_timer

