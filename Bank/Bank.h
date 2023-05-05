#pragma once

#include "../DataBases/Interfaces/DataBaseAccounts.h"
#include "../DataBases/Interfaces/DataBaseClients.h"
#include "../Worker/Worker.h"

class Bank {
 public:
  Bank() = default;
  Bank(std::string&& bank_name, int64_t cred_lim = 0, int64_t bank_fee = 0,
       int dep_per = 0, size_t acc_id = 0, size_t cl_id = 0, size_t w_id = 0);

  Bank(const Bank& bank) = default;
  Bank& operator=(const Bank& bank) = default;

  [[nodiscard]] inline std::string GetName() const { return bank_name_; }
  [[nodiscard]] inline int64_t GetCreditLimit() const { return credit_limit_; }
  [[nodiscard]] inline int64_t GetBankFee() const { return bank_fee_; }
  [[nodiscard]] inline int GetDepositPercent() const { return deposit_percent_; }

  size_t GetAccountID();
  size_t GetClientID();
  size_t GetWorkerID();

  [[nodiscard]] inline size_t GetAccountID_CONST() const { return account_id_; }
  [[nodiscard]] inline size_t GetClientID_CONST() const { return client_id_; }
  [[nodiscard]] inline size_t GetWorkerID_CONST() const { return worker_id_; }

 private:
  std::string bank_name_;

  int64_t credit_limit_;
  int64_t bank_fee_;
  int deposit_percent_;

  size_t account_id_;
  size_t client_id_;
  size_t worker_id_;

};