#include "ros/ros.h"
#include "drive_circle/drive_circle.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "drive_circle_client");
  if (argc != 3)
  {
    ROS_INFO("usage: drive_circle r");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<drive_circle::drive_circle>("drive_circle");
  drive_circle::drive_circle srv;
  srv.request.r = atof(argv[1]);
  srv.request.v = atof(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("drive circle");
  }
  else
  {
    ROS_ERROR("Failed to call service drive_circle");
    return 1;
  }

  return 0;
}