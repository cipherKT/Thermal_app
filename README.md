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
16-bit frame → Bad Pixel Correction → convertTo8bit → Noise Filter → Contrast/Brightness → Polarity → Display
```

## TODO

### FPGA Migration
- [ ] Replace dynamic bad pixel detection with hardware calibration technique (uniform temperature source / shutter-based calibration)
- [ ] Convert bad pixel map file format from `.txt` to binary for faster load and compact storage on embedded target
