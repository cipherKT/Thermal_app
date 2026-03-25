#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "frame_io.h"
#include "display.h"
#include "processor.h"
#include "bad_pixel.h"
#include "overlay.h"
#include "recorder.h"

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

  // overlay config
  OverlayConfig overlay_config;
  overlay_config.show_reticle = true;
  overlay_config.show_grid = true;
  overlay_config.show_fps = true;
  overlay_config.show_timestamp = true;
  overlay_config.reticle_style = ReticleStyle::TACTICAL;
  overlay_config.color = cv::Scalar(0,255,0);

  // recorder
  Recorder recorder("output.avi", 30.0, cv::Size(512,512));

  // display loop
  for (const auto&filepath: frame_paths){
     cv::Mat frame = cv::imread(filepath.string(), cv::IMREAD_UNCHANGED);

     if (frame.empty()){
         std::cerr<< "Failed to load " << filepath << std::endl;
         continue;
     }

     auto loop_start = std::chrono::high_resolution_clock::now();

     cv::Mat corrected = correctBadPixels(frame, bad_pixels);
     cv::Mat corrected_8bit = converTo8bit(corrected);
     cv::Mat colored = applycolormapping(corrected_8bit, ColorMap::RAINBOW);

     auto loop_end = std::chrono::high_resolution_clock::now();
     double elapsed = std::chrono::duration<double, std::milli>(loop_end - loop_start).count();
     double fps = 1000.0 / elapsed;

     drawOverlay(colored,overlay_config, fps);

     if (recorder.isRecording()){
         recorder.writeFrame(colored);
     }

     displayFrames(corrected_8bit, "Raw");
     displayFrames(colored,"processed");

     int key = cv::waitKey(30);
     if (key == 'q') break;
     if (key == 'r'){
         if (recorder.isRecording()){
             recorder.stop();
         }
         else {
             recorder.start();
         }
     }
  }

  cv::destroyAllWindows();
  return 0;
}
