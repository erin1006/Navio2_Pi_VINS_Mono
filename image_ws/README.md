# Image processing component of this project

image_pub node: Publish /dev/video0 to /camera/image_raw 

Change your parameters in image_pub.cpp here:
  // open camera at /dev/video0
  cv::VideoCapture cap(0); 
  // set frame size and fps
  cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
  cap.set(CV_CAP_PROP_FPS,10);
  
image_sub node: Display the image stream via image_viewer

// ToDos: image_proc and features detection...  image processing will be done here
