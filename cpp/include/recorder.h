#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Recorder {
public:
    Recorder (const std::string& output_path, double fps, cv::Size frame_size);
    ~Recorder();

    void start();
    void stop();
    void writeFrame(const cv::Mat &frame);
    bool isRecording() const;

private:
    cv::VideoWriter writer_;
    std::string output_path_;
    double fps_;
    cv::Size frame_size_;
    bool is_recording_;
};
