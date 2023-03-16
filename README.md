# KVH1750_IMU_driver

Writen by LYC, and modified by me.

## Usage
```bash
sudo chmod +777 /dev/ttyUSB0
rosrun kvh1750_driver kvh1750_node
```
- View
In rviz, add imu's topic and change Fixed frame to "imu".

## Attention
Rotation speed: +- 490 degree/s. Larger than this value, no output so that filter failed.
