#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image_raw", 1);
  
  // open camera at /dev/video0
  cv::VideoCapture cap(0); 
  
  // Check if video device can be opened with the given index
  if(!cap.isOpened()) 
  {
	  ROS_ERROR_STREAM("Camera failed to open");
	  return -1;
  }
  ROS_INFO_STREAM("Camera opening");
  
  // set frame size and fps
  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  cap.set(CV_CAP_PROP_FPS,10);
  ROS_INFO_STREAM("Setting video width " << 640);
  ROS_INFO_STREAM("Setting video height " << 480);
  ROS_INFO_STREAM("Setting video fps " << 10);
  
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if(!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}

