#ifndef BANK_SYSTEM_CLIENT_VISITOR_H_
#define BANK_SYSTEM_CLIENT_VISITOR_H_


#include "../Bank/Bank.h"
#include "../Builder/Builder.h"
#include "VisitorInterface.h"
#include "Client.h"


class Visitor : public VisitorInterface {

  std::string bank_name_;
  Client client_;
  bool in_;

 public:

  Visitor() : bank_name_(), client_(), in_{false} {}

  bool MakeVisit(std::string bank_name, size_t user_id, size_t password) override {
    Client client = Bank::clients->GetCLient(bank_name, user_id);
    if (client.CheckPassword(password)) {
      if (client.GetStatus() == Status::Blocked) {
        return false;
      }
      client_ = client;
      in_ = true;
    }
    return in_;
  }
  void Exit() override {
    in_ = false;
  }
  bool OpenAccount(Get* in, Show* out, int64_t cred_lim, int64_t bank_fee) override {
    if (in_) {
      Account* account = Builder::BuildAccount(out, in, client_.GetID(), cred_lim, bank_fee);
      if (client_.GetStatus() == Status::Unconfirmed && dynamic_cast<CreditAccount*>(account) != nullptr) {
        return false;
      }
      Bank::accounts->WriteAccount(bank_name_, client_.GetID(), account);
    }
    return in_;
  }
  bool MakeTransaction(size_t cl_id_1, size_t acc_id_1, size_t cl_id_2, size_t acc_id_2, int64_t money) override {
    if (money < 0) {
      return false;
    }
    if (in_) {
      Account* account_1 = Bank::accounts->GetAccount(bank_name_, cl_id_1, acc_id_1);
      Account* account_2 = Bank::accounts->GetAccount(bank_name_, cl_id_2, acc_id_2);
      if (account_1 == nullptr || account_2 == nullptr) { /// mb mistake
        return false;
      }
      if (client_.GetStatus() == Status::Unconfirmed && money > 50'000) { /// просто фича
        return false;
      }
      account_1->Transaction(-money);
      account_2->Transaction(money);
      /// has to add info in txt 'log_transaction.txt'
    }
    return in_;
  }
  void Request() override {
    /// put info into 'request.txt'
  }

};

#endif //BANK_SYSTEM_CLIENT_VISITOR_H_
