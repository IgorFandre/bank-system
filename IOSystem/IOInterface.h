#ifndef BANK_SYSTEM_IOSYSTEM_IOINTERFACE_H_
#define BANK_SYSTEM_IOSYSTEM_IOINTERFACE_H_


#include <iostream>

class Get {
 public:

  virtual int64_t InputNumber() = 0;
  virtual std::string InputString() = 0;

};


class Show {
 public:

  virtual void Output(int64_t) = 0;
  virtual void Output(const std::string&) = 0;

};


#endif //BANK_SYSTEM_IOSYSTEM_IOINTERFACE_H_
