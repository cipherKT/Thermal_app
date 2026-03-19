#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// Scans the directory and returns the path of all png files
std::vector<fs::path> loadFramePaths(const std::string &dir_path){
    // Returns error
    if (!fs::exists(dir_path)){
        std::cerr<< "Dataset not found: "<< dir_path<< std::endl;
        return {};
    }


    // Store path of frames in vector
    std::vector<fs::path> frame_files;
    for (const auto &entry : fs::directory_iterator(dir_path)){
        if (entry.path().extension() == ".png"){
            frame_files.push_back(entry.path());
        }
    }


    // Sort frames lexographically
    std::sort(frame_files.begin(), frame_files.end());
    std::cout<< "Found " << frame_files.size() << " frames" << std::endl;

    // Returns sorted vector containing frame paths
    return frame_files;
}

//Converts 16-bit thermal frames to 8-bit and displays it
void displayFrames(const cv::Mat& frame, const std::string& window_name){
    cv::Mat display;
    cv::normalize(frame, display, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::imshow(window_name, display);
}

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

     if (cv::waitKey(60) == 'q') break;
  }

  cv::destroyAllWindows();
  return 0;
}
