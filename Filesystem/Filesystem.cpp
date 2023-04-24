#include "Filesystem.h"

bool Filesystem::CheckDirectory(const std::string& path) {
  if (!std::filesystem::exists(path)) {
    std::filesystem::create_directories(path);
    return false;
  }
  return true;
}

bool Filesystem::CheckFile(const std::string& path) {
  if (!std::filesystem::exists(path)) {
    std::ofstream f_empty(path);
    return false;
  }
  return true;
}

bool Filesystem::CheckFileForReadingJson(const std::string& path) {
  return Filesystem::CheckFile(path) && !std::filesystem::is_empty(path);
}
