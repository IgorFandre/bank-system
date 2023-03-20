#ifndef BANK_SYSTEM_BANK_BANK_H_
#define BANK_SYSTEM_BANK_BANK_H_



#include "../DataBases/Interfaces/DataBaseAccounts.h"
#include "../DataBases/Interfaces/DataBaseClients.h"
#include "../Worker/Worker.h"


class Bank {

  std::string bank_name_;

  std::vector<Worker> workers_;

  int64_t credit_limit_;
  int64_t bank_fee_;
  int deposit_percent_;

  size_t account_id_;
  size_t client_id_;

  DataBaseAccounts* accounts;
  DataBaseClients* clients;

 public:

  Bank() = default;

  Bank(const std::string& bank_name, int64_t cred_lim = 0, int64_t bank_fee = 0, int depo_per = 0)
        : bank_name_{bank_name}, credit_limit_{cred_lim}, bank_fee_{bank_fee},
          deposit_percent_{depo_per}, account_id_{0}, client_id_{0}
  {}

  Bank(const Bank& bank) = default;
  Bank& operator=(const Bank& bank) = default;

  [[nodiscard]] std::string GetName() const { return bank_name_; }
  [[nodiscard]] int64_t GetCreditLimit() const { return credit_limit_; }
  [[nodiscard]] int64_t GetBankFee() const { return bank_fee_; }
  [[nodiscard]] int GetDepositPercent() const { return deposit_percent_; }

  size_t GetAccountID() { return ++account_id_; }
  size_t GetClientID() { return ++client_id_; }
  Worker* GetWorker(size_t id) {
    for (auto it = workers_.begin(); it != workers_.end(); ++it) {
      if ((*it).GetId() == id) {
        return &(*it);
      }
    }
    return nullptr;
  }

};


#endif //BANK_SYSTEM_BANK_BANK_H_
