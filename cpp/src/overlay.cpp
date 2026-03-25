#include "overlay.h"
#include <chrono>
#include <iomanip>
#include <sstream>

static void drawReticle(cv::Mat& frame, const OverlayConfig& config) {
    int cx = frame.cols / 2;
    int cy = frame.rows / 2;
    int size = 20;
    cv::Scalar color = config.color;
    int thickness = config.thickness;

    switch (config.reticle_style) {
        case ReticleStyle::SIMPLE_CROSSHAIR:
            cv::line(frame, {cx - size, cy}, {cx + size, cy}, color, thickness);
            cv::line(frame, {cx, cy - size}, {cx, cy + size}, color, thickness);
            break;

        case ReticleStyle::CIRCLE_CROSSHAIR:
            cv::circle(frame, {cx, cy}, size, color, thickness);
            cv::line(frame, {cx - size*2, cy}, {cx + size*2, cy}, color, thickness);
            cv::line(frame, {cx, cy - size*2}, {cx, cy + size*2}, color, thickness);
            break;

        case ReticleStyle::DOT:
            cv::circle(frame, {cx, cy}, 3, color, -1); // -1 means filled
            break;

        case ReticleStyle::CORNER_BRACKETS:
            // Top-left
            cv::line(frame, {cx - size, cy - size}, {cx - size/2, cy - size}, color, thickness);
            cv::line(frame, {cx - size, cy - size}, {cx - size, cy - size/2}, color, thickness);
            // Top-right
            cv::line(frame, {cx + size, cy - size}, {cx + size/2, cy - size}, color, thickness);
            cv::line(frame, {cx + size, cy - size}, {cx + size, cy - size/2}, color, thickness);
            // Bottom-left
            cv::line(frame, {cx - size, cy + size}, {cx - size/2, cy + size}, color, thickness);
            cv::line(frame, {cx - size, cy + size}, {cx - size, cy + size/2}, color, thickness);
            // Bottom-right
            cv::line(frame, {cx + size, cy + size}, {cx + size/2, cy + size}, color, thickness);
            cv::line(frame, {cx + size, cy + size}, {cx + size, cy + size/2}, color, thickness);
            break;

        case ReticleStyle::TACTICAL:
            cv::circle(frame, {cx, cy}, size, color, thickness);
            // Lines with gap at circle
            cv::line(frame, {cx - size*2, cy}, {cx - size, cy}, color, thickness);
            cv::line(frame, {cx + size, cy}, {cx + size*2, cy}, color, thickness);
            cv::line(frame, {cx, cy - size*2}, {cx, cy - size}, color, thickness);
            cv::line(frame, {cx, cy + size}, {cx, cy + size*2}, color, thickness);
            break;
    }
}

static void drawGrid(cv::Mat& frame, const OverlayConfig& config) {
    int rows = 3;
    int cols = 3;
    int row_step = frame.rows / rows;
    int col_step = frame.cols / cols;

    for (int i = 1; i < rows; i++) {
        cv::line(frame, {0, i * row_step}, {frame.cols, i * row_step}, config.color, config.thickness);
    }
    for (int i = 1; i < cols; i++) {
        cv::line(frame, {i * col_step, 0}, {i * col_step, frame.rows}, config.color, config.thickness);
    }
}

static void drawFPS(cv::Mat& frame, double fps, const OverlayConfig& config) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << "FPS: " << fps;
    cv::putText(frame, oss.str(), {10, 20}, cv::FONT_HERSHEY_SIMPLEX, 0.5, config.color, config.thickness);
}

static void drawTimestamp(cv::Mat& frame, const OverlayConfig& config) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    cv::putText(frame, oss.str(), {10, frame.rows - 10}, cv::FONT_HERSHEY_SIMPLEX, 0.5, config.color, config.thickness);
}

void drawOverlay(cv::Mat& frame, const OverlayConfig& config, double fps) {
    if (config.show_reticle)   drawReticle(frame, config);
    if (config.show_grid)      drawGrid(frame, config);
    if (config.show_fps)       drawFPS(frame, fps, config);
    if (config.show_timestamp) drawTimestamp(frame, config);
}
