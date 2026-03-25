#pragma once

#include <opencv2/opencv.hpp>
#include <string>

enum class ReticleStyle {
    SIMPLE_CROSSHAIR,
    CIRCLE_CROSSHAIR,
    DOT,
    CORNER_BRACKETS,
    TACTICAL
};

enum class CrosshairStyle {
    FULL_LINE,
    BROKEN,
    TICK_MARKS
};

struct OverlayConfig{
    bool show_reticle = true;
    bool show_grid = false;
    bool show_fps = true;
    bool show_timestamp = false;
    ReticleStyle reticle_style = ReticleStyle::SIMPLE_CROSSHAIR;
    CrosshairStyle crosshair_style = CrosshairStyle::FULL_LINE;
    cv::Scalar color = cv::Scalar(0,255,0);
    int thickness = 1;
};

void drawOverlay(cv::Mat &frame, const OverlayConfig &config, double fps = 0.0);
