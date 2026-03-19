#include <iostream>
#include <opencv2/opencv.hpp>

#include "frame_io.h"
#include "display.h"
#include "processor.h"

namespace fs = std::filesystem;

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
     // Convert to 8bit
     cv::Mat frame8 = converTo8bit(frame);

     // Added contrast
     cv::Mat contrasted = adjustContrast(frame8, 2.0, 0);

     // Polarity
     cv::Mat polarized = applyPolarity(contrasted,false);

     displayFrames(frame8, "Raw");
     displayFrames(contrasted,"Contrasted");
     displayFrames(polarized,"Polarized");

     if (cv::waitKey(30) == 'q') break;
  }

  cv::destroyAllWindows();
  return 0;
}
