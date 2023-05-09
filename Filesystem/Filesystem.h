#pragma once

#include <filesystem>
#include <fstream>

class Filesystem {
public:
  static bool CheckDirectory(const std::string &path);
  static bool CheckFile(const std::string &path);
  static bool CheckFileForReadingJson(const std::string &path);
};