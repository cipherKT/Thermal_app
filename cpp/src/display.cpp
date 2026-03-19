#include "display.h"

void displayFrames(const cv::Mat &frame, const std::string &window_name){
    cv::Mat display;
    cv::normalize(frame, display, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    cv::imshow(window_name, display);
}
