#ifndef BANK_SYSTEM_WORKER_LOGGER_H_
#define BANK_SYSTEM_WORKER_LOGGER_H_


#include <iostream>

class Logger {

  std::string file_name_;

 public:

  enum class Operation {
    MakeVisit,
    Exit,
    CheckOldestRequest,
    BlockUser,
    RestoreUser,
    CancelTransaction
  };

  Logger(const std::string& bank_name_)
        : file_name_{"logger_" + bank_name_ + ".txt"}
  {}

  friend Logger& operator<<(Logger& logger, const std::string& str) {
    /////
    return logger;
  }
  friend Logger& operator<<(Logger& logger, int64_t num) {
    /////
    return logger;
  }

  friend Logger& operator<<(Logger& logger, size_t num) {
    /////
    return logger;
  }

};


#endif //BANK_SYSTEM_WORKER_LOGGER_H_
