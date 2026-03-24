#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

struct BadPixel {
    int x;
    int y;
};

std::vector<BadPixel> detectBadPixels(const std::vector<cv::Mat>& frames, float threshold);
cv::Mat correctBadPixels(const cv::Mat& frame, const std::vector<BadPixel>& bad_pixels);
void saveBadPixelMap(const std::vector<BadPixel>& bad_pixels, const std::string& filepath);
std::vector<BadPixel> loadBadPixelMap(const std::string& filepath);
