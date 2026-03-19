#pragma once

#include <opencv2/opencv.hpp>
cv::Mat converTo8bit(const cv::Mat &frame);
cv::Mat adjustContrast(const cv::Mat &frame, double alpha, double beta);
