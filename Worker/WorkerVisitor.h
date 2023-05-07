#pragma once

#include "../Bank/Bank.h"
#include "../Request/Request.h"
#include "../Logger/Logger.h"
#include "WorkerVisitorInterface.h"
#include "Worker.h"

class WorkerVisitor : public WorkerVisitorInterface {
 public:
  WorkerVisitor();

  bool MakeVisit(const std::string& bank_name, const Worker& worker, const std::string& password) override;
  void Exit(const Date& system_date) override;
  void CheckOldestRequest(std::unique_ptr<Show>& out, const Date& system_date) override;
  bool BlockUser(size_t user_id, std::unique_ptr<DataBaseClients>& clients, const Date& system_date) override;
  bool RestoreUser(size_t user_id, std::unique_ptr<DataBaseClients>& clients, const Date& system_date) override;
  bool CancelTransaction(size_t cl_id_1, size_t acc_id_1, size_t cl_id_2, size_t acc_id_2,
                         const BigInteger& money, std::unique_ptr<DataBaseAccounts>& accounts, const Date& system_date) override;

 private:
  std::string bank_name_;
  Worker worker_;
  bool in_;

};