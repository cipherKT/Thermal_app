#include <iostream>
#include <opencv2/opencv.hpp>

#include "frame_io.h"
#include "display.h"

namespace fs = std::filesystem;

// Scans the directory and returns the path of all png files


int main(){
  std::string dataset_path = "datasets/pedestrian/";

  std::vector<fs::path>frame_paths = loadFramePaths(dataset_path);
  if (frame_paths.empty()) return -1;

  for (const auto&filepath: frame_paths){
     cv::Mat frame = cv::imread(filepath.string(), cv::IMREAD_UNCHANGED);

     if (frame.empty()){
         std::cerr<< "Failed to load " << filepath << std::endl;
         continue;
     }

     displayFrames(frame, "Thermal player");

     if (cv::waitKey(30) == 'q') break;
  }

  cv::destroyAllWindows();
  return 0;
}
