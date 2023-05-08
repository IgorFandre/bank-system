#ifndef BANK_SYSTEM_REQUEST_REQUEST_H_
#define BANK_SYSTEM_REQUEST_REQUEST_H_


#include <iostream>

struct Request {
  std::string bank_name;
  size_t user_id;
  std::string text;

  void WriteRequest() {
    /// write request to file
  }

  static Request ReadLastRequest(const std::string& bank_name) {
    /// return last request from the file and delete it
    return {};
  }
};



#endif //BANK_SYSTEM_REQUEST_REQUEST_H_
