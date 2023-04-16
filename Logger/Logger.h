#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "../Filesystem/Filesystem.h"

class Logger {

 private:

  std::string working_file_;

 public:

  enum class OperationType {
    WorkerOperation = 0,
    Transaction,
    OpenAccount
  };

  Logger(const std::string& bank, OperationType op);
  ~Logger() = default;

  void AddLog(const std::string& log);

};