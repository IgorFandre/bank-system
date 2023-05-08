#ifndef BANK_SYSTEM_DATABASES_VECTORDBACCOUNTS_H_
#define BANK_SYSTEM_DATABASES_VECTORDBACCOUNTS_H_


#include <unordered_map>
#include <vector>

#include "DataBaseAccounts.h"

class VectorDBAccounts : public DataBaseAccounts {

 public:

  VectorDBAccounts() = default;

  VectorDBAccounts(const VectorDBAccounts&) = delete;
  void operator=(const VectorDBAccounts&) = delete;

  void WriteAccount(const std::string& bank_name, size_t user_id, Account* account) override {
    accounts_[bank_name][user_id].push_back(account);
  }
  void WriteAccounts(const std::string& bank_name, size_t user_id, const std::vector<Account*>& accounts) override {
    for (auto account : accounts) {
      accounts_[bank_name][user_id].push_back(account);
    }
  }
  void DeleteClientAccounts(const std::string& bank_name, size_t user_id) override {
    if (accounts_.contains(bank_name) && accounts_[bank_name].contains(user_id)) {
      accounts_[bank_name].erase(user_id);
    }
  }
  Account* GetAccount(const std::string& bank_name, size_t user_id, size_t account_id) override {
    if (!accounts_.contains(bank_name) || !accounts_[bank_name].contains(user_id)) {
      return nullptr;
    }
    for (auto account : accounts_[bank_name][user_id]) {
      if (account->GetAccountId() == account_id) {
        return account;
      }
    }
    return nullptr;
  }
  std::vector<Account*> GetUserAccounts(const std::string& bank_name, size_t user_id) override {
    if (accounts_[bank_name].contains(user_id)) {
      return accounts_[bank_name][user_id];
    }
    accounts_[bank_name][user_id] = {};
    return accounts_[bank_name][user_id];
  }

 private:

  std::unordered_map<std::string, std::unordered_map<size_t, std::vector<Account*>>> accounts_;

};


#endif //BANK_SYSTEM_DATABASES_VECTORDBACCOUNTS_H_
