#include "ros/ros.h"
#include "drive_circle/drive_circle.h"
#include "geometry_msgs/Twist.h"

bool drive(drive_circle::drive_circle::Request &req,
         drive_circle::drive_circle::Response &res)
{ 
  ros::NodeHandle node;

  ROS_INFO("request: radius=%2.2f, vel=%2.2f", req.r, req.v);

  ros::Publisher turtle_vel =
       node.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);
  geometry_msgs::Twist vel_msg;
  ros::Rate rate(10.0);
  int count = 0;
  while (node.ok() && count < 50) {
    count++;
    vel_msg.angular.z = req.v/req.r;
    vel_msg.linear.x = req.v;

    turtle_vel.publish(vel_msg);
    rate.sleep();
  }
  
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "drive_circle_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("drive_circle", drive);
  ROS_INFO("Ready to ride...");
  ros::spin();

  return 0;
}