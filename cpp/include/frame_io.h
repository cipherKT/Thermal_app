#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> loadFramePaths(const std::string& dir_path);
