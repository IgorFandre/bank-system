#ifndef BANK_SYSTEM_CLIENT_VISITOR_H_
#define BANK_SYSTEM_CLIENT_VISITOR_H_


#include "../Builder/Builder.h"
#include "VisitorInterface.h"
#include "../DataBases/Interfaces/DataBaseClients.h"
#include "../Worker/Logger.h"


class Visitor : public VisitorInterface {

  std::string bank_name_;
  Client client_;
  bool in_;

 public:

  Visitor() : bank_name_(), client_(), in_{false} {}
  virtual ~Visitor() = default;

  bool MakeVisit(std::string bank_name, size_t user_id, int64_t pas, DataBaseClients* clients) override {
    Client client = clients->GetCLient(bank_name, user_id);
    if (!client.CheckPassword(pas)) {
      return false;
    }
    bank_name_ = bank_name;
    client_ = client;
    in_ = true;
    return in_;
  }
  void ChangePassportData(Get* in, Show* out) override {
    client_.ChangePassport(Builder::BuildPassport(out, in));
  }
  void Exit() override {
    in_ = false;
  }
  bool OpenAccount(Get* in, Show* out, int64_t cred_lim, int64_t bank_fee, DataBaseAccounts* accounts, size_t acc_id) override {
    if (in_) {
      Account* account = Builder::BuildAccount(out, in, acc_id, cred_lim, bank_fee);
      if (client_.GetStatus() == Status::Unconfirmed && dynamic_cast<CreditAccount*>(account) != nullptr) {
        return false;
      }
      accounts->WriteAccount(bank_name_, client_.GetID(), account);
    }
    return in_;
  }
  bool MakeTransaction(size_t cl_id_1, size_t acc_id_1, size_t cl_id_2, size_t acc_id_2, int64_t money, DataBaseAccounts* accounts) override {
    if (money < 0) {
      return false;
    }
    if (in_) {
      Account* account_1 = accounts->GetAccount(bank_name_, cl_id_1, acc_id_1);
      Account* account_2 = accounts->GetAccount(bank_name_, cl_id_2, acc_id_2);
      if (account_1 == nullptr || account_2 == nullptr) { /// mb mistake
        return false;
      }
      if (client_.GetStatus() == Status::Unconfirmed && money > 50'000) { /// просто фича
        return false;
      }
      account_1->Transaction(-money);
      account_2->Transaction(money);
      Logger logger(bank_name_);
      logger << "Transaktion from account 1: " << acc_id_1 << "(user 1: " << cl_id_1 << ") to account 2: " << acc_id_2 << "(user 2: " << cl_id_2 << ")";
    }
    return in_;
  }

  [[nodiscard]] size_t GetID() const {
    return client_.GetID();
  }
  [[nodiscard]] bool CheckPassword(int64_t pass) const { return client_.CheckPassword(pass); }
  [[nodiscard]] Status GetStatus() const { return client_.GetStatus(); }

};

#endif //BANK_SYSTEM_CLIENT_VISITOR_H_
