#pragma once

#include <fstream>
#include <filesystem>

class Filesystem {
 public:

  static bool CheckDirectory(const std::string& path);
  static bool CheckFile(const std::string& path);
  static bool CheckFileForReadingJson(const std::string& path);

};