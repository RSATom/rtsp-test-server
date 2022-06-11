#pragma once

#include <string>
#include <deque>

std::deque<std::string> ConfigDirs();
std::string FullPath(const std::string& configDir, const std::string& path);
