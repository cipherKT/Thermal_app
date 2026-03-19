#include "display.h"

void displayFrames(const cv::Mat &frame, const std::string &window_name){
    cv::imshow(window_name, frame);
}
