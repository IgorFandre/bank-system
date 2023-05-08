#ifndef BANK_SYSTEM_IOSYSTEM_IOIOSTREAM_H_
#define BANK_SYSTEM_IOSYSTEM_IOIOSTREAM_H_

#include <limits>
#include "IOInterface.h"

class ConsoleGet : public Get {

  void ClearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }

 public:

  virtual int64_t InputNumber() override {
    int64_t number;
    std::cin >> number;
    ClearInput();
    return number;
  }
  virtual std::string InputString() override {
    std::string string;
    std::cin >> string;
    ClearInput();
    return string;
  }

};


class ConsoleShow : public Show {
 public:

  virtual void Output(int64_t number) override {
    std::cout << number << std::endl;
  }
  virtual void Output(const std::string& string) override {
    std::cout << string << std::endl;
  }
};


#endif //BANK_SYSTEM_IOSYSTEM_IOIOSTREAM_H_
