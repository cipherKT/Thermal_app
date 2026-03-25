#include "recorder.h"
#include <iostream>

Recorder::Recorder(const std::string &output_path, double fps, cv::Size frame_size)
    : output_path_(output_path), fps_(fps), frame_size_(frame_size), is_recording_(false){
}

Recorder::~Recorder() {
    if (is_recording_){
        stop();
    }
}

void Recorder::start(){
    if (is_recording_){
        std::cout << "Already recoring" << std::endl;
        return ;
    }

    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    writer_.open(output_path_, fourcc, fps_, frame_size_, true);
    if (!writer_.isOpened()) {
        std::cerr<< "Failed to open video wirter: "<< output_path_ << std::endl;
        return;
    }

    is_recording_ = true;
    std::cout<<"Recording started: "<< output_path_ << std::endl;
}

void Recorder::stop(){
    if (!is_recording_) return;
    writer_.release();
    is_recording_ = false;
    std::cout<<"Recording stopped: "<< output_path_ << std::endl;
}
void Recorder::writeFrame(const cv::Mat &frame){
    if(!is_recording_) return;
    writer_.write(frame);
}

bool Recorder::isRecording() const {
    return is_recording_;
}
