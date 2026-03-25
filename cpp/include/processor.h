#pragma once

#include <opencv2/opencv.hpp>
cv::Mat converTo8bit(const cv::Mat &frame);
cv::Mat adjustContrast(const cv::Mat &frame, double alpha, double beta);
cv::Mat applyPolarity(const cv::Mat &frame, bool white_hot);
cv::Mat applyGaussianFilter(const cv::Mat &frame, int kernel_size);
cv::Mat applyMedianFilter(const cv::Mat &frame, int kernel_size);
cv::Mat applyAGC(const cv::Mat &frame, float clip_percentile);
