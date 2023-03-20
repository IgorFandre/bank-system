#ifndef BANK_SYSTEM_WORKER_WORKERVISITOR_H_
#define BANK_SYSTEM_WORKER_WORKERVISITOR_H_


#include "../Bank/Bank.h"
#include "../Request/Request.h"
#include "Logger.h"
#include "WorkerVisitorInterface.h"
#include "Worker.h"

class WorkerVisitor : public WorkerVisitorInterface {

  std::string bank_name_;
  Worker worker_;
  bool in_;

 public:

  //WorkerVisitor() = default;

  bool MakeVisit(const std::string& bank_name, const Worker& worker, int64_t password) override {
    if (worker.CheckPassword(password)) {
      worker_ = worker;
      in_ = true;
    }
    return in_;
  }
  void Exit() override {
    in_ = false;
  }
  void CheckOldestRequest(Show* out) override {
    Request last = Request::ReadLastRequest(bank_name_);
    out->Output(static_cast<int64_t>(last.user_id));
    out->Output(last.text);
  }
  bool BlockUser(const std::string& bank_name, size_t user_id, DataBaseClients* clients) override {
    Client client = clients->GetCLient(bank_name, user_id);
    if (client == Client()) {
      return false;
    }
    client.ChangeStatus(true);
    clients->WriteClient(bank_name, client);
    return true;
  }
  bool RestoreUser(const std::string& bank_name, size_t user_id, DataBaseClients* clients) override {
    Client client = clients->GetCLient(bank_name, user_id);
    if (client == Client()) {
      return false;
    }
    client.ChangeStatus();
    clients->WriteClient(bank_name, client);
    return true;
  }
  bool CancelTransaction(const std::string& bank_name, size_t send_user_id, size_t get_user_id, int64_t money_transaction) override {
    /// just read the 'log.txt' and delete if found
    return false;
  }



};


#endif //BANK_SYSTEM_WORKER_WORKERVISITOR_H_
