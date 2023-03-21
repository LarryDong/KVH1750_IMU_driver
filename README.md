# KVH1750_IMU_driver

KVH1750's USB driver. (Using RS232->USB).  
Writen by LYC, and modified by me.  

## Usage
```bash
sudo bash serialport_modify.bash
roslaunch kvh1750_driver kvh1750.launch
```
Modify the `serial_port`, and other params in launch.

- View
In rviz, add imu's topic and change Fixed frame to "imu".

## Attention
- Rotation speed: +- 490 degree/s. Larger than this value, no output so that filter failed.  
- The `boost::asio::serial_port` read maybe very slow (about to 30ms@100Hz). So the serial port's `latency_timer` should be changed to 1. See `serialport_modify.bash` for command.
