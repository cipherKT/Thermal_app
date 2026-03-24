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
cv::Mat applyGaussianFilter(const cv::Mat &frame, int kernel_size){ // Kernel size should be odd number
    if (kernel_size % 2 != 1){
        std::cerr<< "Kernel size needs to be odd, got: " << kernel_size << std::endl;
        return cv::Mat();
    }
    cv::Mat result;
    cv::GaussianBlur(frame, result, cv::Size(kernel_size, kernel_size), 0);
    return result;
}
cv::Mat applyMedianFilter(const cv::Mat &frame, int kernel_size){
    if (kernel_size % 2 != 1){
        std::cerr<< "Kernel size needs to be odd, got: " << kernel_size << std::endl;
        return cv::Mat();
    }   cv::Mat result;
    cv::medianBlur(frame, result, kernel_size);
    return result;
}
