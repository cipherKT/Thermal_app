#include "processor.h"
#include <tuple>


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
cv::Mat applyPolarity(const cv::Mat &frame, bool white_hot){
    if (white_hot) return frame;
    cv::Mat result;
    cv::bitwise_not(frame, result);
    return result;
}
