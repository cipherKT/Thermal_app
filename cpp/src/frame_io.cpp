#include "frame_io.h"
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<fs::path> loadFramePaths(const std::string &dir_path){
    if(!fs::exists(dir_path)){
        std::cerr << "Dataset path not found: "<< dir_path<< std::endl;
        return {};
    }

    std::vector<fs::path> frame_files;
    for (const auto& entry : fs::directory_iterator(dir_path)){
        if(entry.path().extension() == ".png"){
            frame_files.push_back(entry.path());
        }
    }
    std::sort(frame_files.begin(), frame_files.end());
    std::cout << "Found " << frame_files.size() << " frames" << std::endl;
    return frame_files;
}
