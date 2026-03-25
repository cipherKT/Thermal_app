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


cv::Mat applyAGC(const cv::Mat &frame, float clip_percentile){
    int hist_size = 256;
    float range[] = {0,256};
    const float* hist_range = {range};
    cv::Mat hist;
    cv::calcHist(&frame, 1, 0, cv::Mat(), hist, 1 , &hist_size, &hist_range);

    int total_pixels = frame.rows * frame.cols;
    int clip_count = static_cast<int>(total_pixels * clip_percentile / 100.0f);

    int lower = 0;
    int count = 0;
    for (int i = 0; i <hist_size; i++){
        count += static_cast<int>(hist.at<float>(i));
        if (count >= clip_count){
            lower = i;
            break;
        }
    }

    int upper = hist_size - 1;
    count = 0;
    for (int i = hist_size - 1;i>=0; i--){
        count += static_cast<int>(hist.at<float>(i));
        if (count >= clip_count){
            upper = i;
            break;
        }
    }

    cv::Mat result;
    frame.convertTo(result, CV_8UC1, 255.0 / (upper - lower), -lower * 255.0 / (upper-lower));
    cv::threshold(result, result, 255, 255, cv::THRESH_TRUNC);

    return result;
}
