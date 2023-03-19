#ifndef BANK_SYSTEM_WORKER_WORKERVISITORINTERFACE_H_
#define BANK_SYSTEM_WORKER_WORKERVISITORINTERFACE_H_


#include <iostream>

#include "../IOSystem/IOInterface.h"
#include "Worker.h"

class WorkerVisitorInterface {

 public:

  virtual bool MakeVisit(const std::string& bank_name, const Worker& worker, size_t password) = 0;
  virtual void Exit() = 0;
  virtual void CheckOldestRequest(Show* out) = 0;
  virtual void BlockUser(const std::string& bank_name, size_t user_id) = 0;
  virtual bool RestoreUser(const std::string& bank_name, size_t user_id) = 0;
  virtual bool CancelTransaction(const std::string& bank_name, size_t send_user_id, size_t get_user_id, int64_t money_transaction) = 0;

};


#endif //BANK_SYSTEM_WORKER_WORKERVISITORINTERFACE_H_
