#pragma once

#include "IOInterface.h"
#include <limits>

class ConsoleGet : public Get {

  void ClearInput();

public:
  int64_t InputNumber() override;
  std::string InputString() override;
};

class ConsoleShow : public Show {
public:
  void Output(int64_t number) override;
  void Output(const std::string &string) override;
};