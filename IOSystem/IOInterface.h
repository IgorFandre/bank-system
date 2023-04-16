#pragma once

#include <iostream>

class Get {
 public:

  Get() = default;
  virtual ~Get() = default;

  virtual int64_t InputNumber() = 0;
  virtual std::string InputString() = 0;

};


class Show {
 public:

  Show() = default;
  virtual ~Show() = default;

  virtual void Output(int64_t) = 0;
  virtual void Output(const std::string&) = 0;

};