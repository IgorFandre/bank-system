#ifndef BANK_SYSTEM_CLIENT_VISITORINTERFACE_H_
#define BANK_SYSTEM_CLIENT_VISITORINTERFACE_H_


#include <iostream>
#include "../Bank/Bank.h"
#include "../IOSystem/IOInterface.h"

class VisitorInterface {

 public:

  virtual bool MakeVisit(std::string bank_name, size_t user_id, size_t password) = 0;
  virtual void Exit() = 0;
  virtual bool OpenAccount(Get* in, Show* out, int64_t cred_lim, int64_t bank_fee) = 0;
  virtual bool MakeTransaction(size_t cl_id_1, size_t acc_id_1, size_t cl_id_2, size_t acc_id_2, int64_t money) = 0;
  virtual void Request() = 0;

};


#endif //BANK_SYSTEM_CLIENT_VISITORINTERFACE_H_
