#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../Filesystem/Filesystem.h"

class Logger {
public:
  enum class OperationType { WorkerOperation = 0, Transaction, OpenAccount };

  Logger(const std::string &bank, OperationType op);
  ~Logger() = default;

  [[nodiscard]] inline std::string GetWorkingFile() const {
    return working_file_;
  }

  void AddLog(const std::string &log);

private:
  std::string working_file_;
};