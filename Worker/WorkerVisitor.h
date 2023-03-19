#ifndef BANK_SYSTEM_WORKER_WORKERVISITOR_H_
#define BANK_SYSTEM_WORKER_WORKERVISITOR_H_


#include "../Bank/Bank.h"
#include "WorkerVisitorInterface.h"
#include "Worker.h"

class WorkerVisitor : public WorkerVisitorInterface {

  std::string bank_name_;
  Worker worker_;
  bool in_;

 public:

  WorkerVisitor() = default;

  bool MakeVisit(const std::string& bank_name, const Worker& worker, size_t password) override {
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
    /// Open file 'requests.txt' and print last request, then delete it from the file
  }
  void BlockUser(const std::string& bank_name, size_t user_id) override {
    Client client = Bank::clients->GetCLient(bank_name, user_id);
    client.ChangeStatus(true);
    Bank::clients->WriteClient(bank_name, client);
  }
  bool RestoreUser(const std::string& bank_name, size_t user_id) override {
    Client client = Bank::clients->GetCLient(bank_name, user_id);
    client.ChangeStatus();
    Bank::clients->WriteClient(bank_name, client);
  }
  virtual bool CancelTransaction(const std::string& bank_name, size_t send_user_id, size_t get_user_id, int64_t money_transaction) {
    /// just read the 'log.txt' and delete if found
  }



};


#endif //BANK_SYSTEM_WORKER_WORKERVISITOR_H_
