#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main(){
  // std::cout<<"OpenCV version: " << CV_VERSION << std::endl;
  std::string dataset_path = "datasets/pedestrian/";

  std::string first_frame = dataset_path + "frame_00091.png";
  cv::Mat frame = cv::imread(first_frame, cv::IMREAD_UNCHANGED);

  if (frame.empty()){
    std::cerr << "Failed to load frame: " << first_frame << std::endl;
    return -1;
  }
  std::cout<< "Frame loaded successfully" << std::endl;
  std::cout<< "Size: " << frame.cols << "x" << frame.rows << std::endl;
  std::cout<< "Channels: " << frame.channels() << std::endl;
  std::cout<< "Type: " << frame.type() << std::endl;

  return 0;
}
