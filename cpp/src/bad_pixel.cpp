#include "bad_pixel.h"
#include <fstream>
#include <iostream>

std::vector<BadPixel> detectBadPixels(const std::vector<cv::Mat>&frames, float threshold){
    // Checks if the frames are there
    if (frames.empty()) {
        std::cerr << "No frames provided for bad pixel detection" << std::endl;
        return {};
    }

    // Accumate the pixel values of all frames
    cv::Mat accumalated;
    frames[0].convertTo(accumalated, CV_32F);

    for (size_t i = 1; i<frames.size(); i++){
        cv::Mat temp;
        frames[i].convertTo(temp, CV_32F);
        accumalated += temp;
    }
    // Mean
    cv::Mat mean_frame = accumalated / static_cast<float>(frames.size());

    // global mean
    cv::Scalar global_mean = cv::mean(mean_frame);
    cv::Scalar global_stddev;
    cv::meanStdDev(mean_frame, global_mean, global_stddev);

    // pixel == bad if deviation(pixel) > threshhold * stddev from mean
    std::vector<BadPixel> bad_pixels;
    for (int y = 0;y<mean_frame.rows; y++){
        for (int x = 0;x<mean_frame.cols; x++){
            float val = mean_frame.at<float>(y,x);
            if (std::abs(val - global_mean[0]) > threshold * global_stddev[0]){
                bad_pixels.push_back({x,y});
            }
        }
    }

    std::cout<< "Detected " << bad_pixels.size() << " bad pixels" <<std::endl;
    return bad_pixels;
}

cv::Mat correctBadPixels(const cv::Mat &frame, const std::vector<BadPixel> &bad_pixels){
    cv::Mat result = frame.clone();

    for (const auto &bp: bad_pixels){
        int x = bp.x;
        int y = bp.y;

        // Collect neighbors
        std::vector<float> neighbors;
        for (int dy = -1;dy<=1;dy++){
            for (int dx=-1;dx<=1;dx++){
                if (dx == 0 && dy == 0) continue; // skip the bad pixel itself

                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < frame.cols && ny >= 0 && ny < frame.rows){
                    neighbors.push_back(frame.at<uint16_t>(ny,nx));
                }
            }
        }

        // replace bad pixel with mean value of neighbors
        if(!neighbors.empty()){
            float sum = 0;
            for(float v : neighbors) sum += v;
            result.at<uint16_t>(y,x) = static_cast<uint16_t>(sum / neighbors.size());
        }
    }
    return result;
}


void saveBadPixelMap(const std::vector<BadPixel> &bad_pixels, const std::string &filepath){
    std::ofstream file(filepath);
    if (!file.is_open()){
        std::cerr<<"Failed to open file for writing: " << filepath << std::endl;
        return;
    }

    for (const auto &bp : bad_pixels){
        file << bp.x << " "<<bp.y<<"\n";
    }
    std::cout<<"Saved " << bad_pixels.size()<<" bad pixels to "<< filepath << std::endl;
}

std::vector<BadPixel> loadBadPixelMap(const std::string &filepath){
    std::ifstream file(filepath);
    if (!file.is_open()){
        std::cerr << "Bad pixel map not found: " << filepath<< std::endl;
        return {};
    }
    std::vector<BadPixel> bad_pixels;
    int x,y;
    while(file >> x >> y){
        bad_pixels.push_back({x,y});
    }
    std::cout<<"Loaded "<< bad_pixels.size() << " bad pixels from "<< filepath << std::endl;
    return bad_pixels;
}
