#pragma once

#include <iostream>

#include "../IOSystem/IOInterface.h"
#include "Worker.h"

class WorkerVisitorInterface {
 public:
  WorkerVisitorInterface() = default;
  virtual ~WorkerVisitorInterface() = default;

  virtual bool MakeVisit(const std::string& bank_name, const Worker& worker, const std::string& password) = 0;
  virtual void Exit(const Date& system_date) = 0;
  virtual void CheckOldestRequest(std::unique_ptr<Show>& out, const Date& system_date) = 0;
  virtual bool BlockUser(size_t user_id, std::unique_ptr<DataBaseClients>& clients, const Date& system_date) = 0;
  virtual bool RestoreUser(size_t user_id, std::unique_ptr<DataBaseClients>& clients, const Date& system_date) = 0;
  virtual bool CancelTransaction(size_t cl_id_1, size_t acc_id_1, size_t cl_id_2, size_t acc_id_2, const BigInteger& money,
                                 std::unique_ptr<DataBaseAccounts>& accounts, const Date& system_date) = 0;

};