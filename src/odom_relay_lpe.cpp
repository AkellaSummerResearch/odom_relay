
// ROS
#include "ros/ros.h"
#include "mavros/mavros_uas.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <eigen_conversions/eigen_msg.h>

ros::Publisher pose_pub;
ros::Publisher odom_pub;

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
  geometry_msgs::PoseStamped pose,pose1;
  pose = *msg;
  pose1 = *msg;
  Eigen::Affine3d tr;
  tf::poseMsgToEigen(pose1.pose, tr);
  tr = mavros::UAS::transform_orientation_baselink_aircraft(Eigen::Quaterniond(tr.rotation()));
  tf::poseEigenToMsg(tr, pose1.pose);
  pose.pose.orientation = pose1.pose.orientation;
  //pose.header = msg->header;
  pose.header.frame_id = "fcu";
  //pose.pose.position = msg->pose.pose.position;
  //pose.pose.orientation = msg->pose.pose.orientation;
  pose_pub.publish(pose);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  nav_msgs::Odometry odom;
  odom = *msg;
  //pose.header = msg->header;
  odom.header.frame_id = "fcu";
  odom.child_frame_id = "fcu";
  //pose.pose.position = msg->pose.pose.position;
  //pose.pose.orientation = msg->pose.pose.orientation;
  odom_pub.publish(odom);
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "odom_relay_lpe");
  ros::NodeHandle n;

  ros::Subscriber sub_pose = n.subscribe("/vislam/pose", 5, poseCallback);
  pose_pub = n.advertise<geometry_msgs::PoseStamped>("Frodo/mavros/vision_pose/pose", 5);
  ros::Subscriber sub_odom = n.subscribe("/vislam/odometry", 5, odomCallback);
  odom_pub = n.advertise<nav_msgs::Odometry>("Frodo/mavros/vision_pose/odom", 5);
  
  ros::spin();

  return 0;
} 
