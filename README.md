# Thermal Imaging Platform

A modular, real-time thermal imaging platform built with C++ and OpenCV.
Designed for Linux desktop first, with future extension to Android, iOS, and FPGA.

## Hardware Target
- Lynred ATTO640D-04W detector (640x480, 12µm pitch)
- ERNEST 6 Seecube Family
- USB3 interface

## Tech Stack
- **Processing:** C++ with OpenCV
- **UI:** Flutter (upcoming)
- **Build:** CMake

## Current Pipeline
```
16-bit frame → BPC → convertTo8bit → AGC → Noise Filter → Contrast → Polarity → Color Map → Overlay → Display
```

## Completed
- [x] Frame loading from folder
- [x] Bad pixel detection and correction
- [x] AGC with histogram percentile clipping
- [x] Noise filtering (Gaussian and Median)
- [x] Contrast and brightness adjustment
- [x] Polarity control (white-hot / black-hot)
- [x] Color mapping (Grey, Hot, Inferno, Plasma, Winter, Jet, Rainbow)
- [x] Overlay system (reticle, grid, FPS, timestamp)
- [x] Recording

## Upcoming
- [ ] NUC (Non-Uniformity Correction)
- [ ] Flutter UI
- [ ] USB streaming
- [ ] Object detection

## TODO

### FPGA Migration
- [ ] Replace dynamic bad pixel detection with hardware calibration technique
- [ ] Convert bad pixel map file format from `.txt` to binary
- [ ] MP4/H264 recording support (requires OpenCV built from source with x264)
