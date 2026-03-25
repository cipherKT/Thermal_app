#include <iostream>
#include <opencv2/opencv.hpp>

#include "frame_io.h"
#include "display.h"
#include "processor.h"
#include "bad_pixel.h"

namespace fs = std::filesystem;

int main(){
  std::string dataset_path = "datasets/pedestrian/";
  std::string bpc_map_path = "bpc_map.txt";

  std::vector<fs::path>frame_paths = loadFramePaths(dataset_path);
  if (frame_paths.empty()) return -1;

  // Bad pixels
  std::vector<BadPixel> bad_pixels = loadBadPixelMap(bpc_map_path);

  if (bad_pixels.empty()) {
      std::cout<< "No bad pixel map found, detecting from first 30 frames..." << std::endl;

      std::vector<cv::Mat>  calibration_frames;
      for (int i = 0; i< 30 && i <(int)frame_paths.size(); i++){
          cv::Mat f = cv::imread(frame_paths[i].string(), cv::IMREAD_UNCHANGED);
          if (!f.empty()) calibration_frames.push_back(f);
      }
      bad_pixels = detectBadPixels(calibration_frames, 3.0f);
      saveBadPixelMap(bad_pixels,bpc_map_path);
  }


  // display loop
  for (const auto&filepath: frame_paths){
     cv::Mat frame = cv::imread(filepath.string(), cv::IMREAD_UNCHANGED);

     if (frame.empty()){
         std::cerr<< "Failed to load " << filepath << std::endl;
         continue;
     }

     cv::Mat corrected = correctBadPixels(frame, bad_pixels);
     cv::Mat corrected_8bit = converTo8bit(corrected);
     cv::Mat contrasted = adjustContrast(corrected_8bit,2.0,0);
     cv::Mat polarized = applyPolarity(contrasted,false);

     displayFrames(corrected_8bit, "Raw");
     displayFrames(polarized,"Processed");

     if (cv::waitKey(30) == 'q') break;
  }

  cv::destroyAllWindows();
  return 0;
}
