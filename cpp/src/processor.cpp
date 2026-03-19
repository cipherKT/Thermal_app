#include "processor.h"


cv::Mat converTo8bit(const cv::Mat& frame){
    cv::Mat result;
    cv::normalize(frame, result, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    return result;
}
cv::Mat adjustContrast(const cv::Mat& frame, double alpha, double beta){
    cv::Mat result;
    frame.convertTo(result, -1, alpha, beta);
    return result;
}
