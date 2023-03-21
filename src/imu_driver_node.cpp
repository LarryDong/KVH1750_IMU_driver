
#include <iostream>
#include <string>
#include "KVH1750.h"
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

using namespace std;


#define Gravity (9.8065f)
#define PI (3.1415926f)
#define DEG2RAD (PI/180.0f)

sensor_msgs::Imu toRosMsg(const my_imu::Imu_Data & rawdata){
    sensor_msgs::Imu imu_data;
    imu_data.header.stamp = ros::Time::now();
    imu_data.header.frame_id = "imu";
    imu_data.header.seq = rawdata.sequence_num;
    double scale = 1.0f;
    imu_data.angular_velocity.x = rawdata.gyro[0] * DEG2RAD;
    imu_data.angular_velocity.y = rawdata.gyro[1] * DEG2RAD;
    imu_data.angular_velocity.z = rawdata.gyro[2] * DEG2RAD;
    imu_data.linear_acceleration.x = rawdata.acc[0] * Gravity;
    imu_data.linear_acceleration.y = rawdata.acc[1] * Gravity;
    imu_data.linear_acceleration.z = rawdata.acc[2] * Gravity;
    return imu_data;
}


void IMU_Callback(sensor_msgs::Imu imu){
    ROS_INFO("IMU callback");
}

int main(int argc, char **argv){

    ros::init(argc, argv, "imu_driver");
    ros::NodeHandle nh("~");
    ROS_INFO("IMU serial communication start...");

    string usb_port("/dev/ttyUSB0");
    string imu_topic("/kvh/imu");
    // string gyro_unit("rad");          // "rad" or "degree". always "rad/s"
    int print_counter(100);
    
    ros::param::get("~usb_port", usb_port);
    ros::param::get("~print_counter", print_counter);
    // ros::param::get("~gyro_unit", gyro_unit);

    ROS_INFO("-----------------------------------------");
    ROS_INFO_STREAM("-- Open port: " << usb_port);
    ROS_INFO_STREAM("-- Imu topic: " << imu_topic);
    ROS_INFO_STREAM("-- Gryo mode: " << "rad/s");
    ROS_INFO_STREAM("-- Output per: " << print_counter);
    ROS_INFO("-----------------------------------------");


    ros::Publisher pub = nh.advertise<sensor_msgs::Imu>(imu_topic, 10);
    my_imu::imu_1750 imu(usb_port);         // open ttyUSBx. Make sure to 'sudo chmod 777 /dev/ttyUSBx'

    int counter = 0;
    my_imu::Imu_Data raw_data;
    sensor_msgs::Imu imu_data;
    while(1){
        if(imu.get_data(raw_data)){
            imu_data = toRosMsg(raw_data);
            pub.publish(imu_data);
            if(counter++ == print_counter){
                counter = 0;
                auto acc = imu_data.linear_acceleration;
                auto gyro = imu_data.angular_velocity;
                cout << "Acc: " << acc.x << ", " << acc.y << ", " << acc.z << ",\t Gyro(rad): " << gyro.x << ", " << gyro.y << ", " << gyro.z << endl;
            }
            ros::spinOnce();
        }
        else{
            ROS_WARN("Cannot get IMU data. Maybe acc or gyro moves too fase!");         // due to too large acc or w.
        }
    }
    return 0;
}
