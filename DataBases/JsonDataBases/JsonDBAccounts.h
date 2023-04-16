#pragma once

#include <vector>

#include "../Interfaces/DataBaseAccounts.h"
#include "../../Account/CreditAccount.h"
#include "../../Account/DebitAccount.h"
#include "../../Account/DepositAccount.h"
#include "../../JsonParser/json.h"
#include "../../Filesystem/Filesystem.h"

class JsonDBAccounts : public DataBaseAccounts {
  using json = nlohmann::json;
 public:

  JsonDBAccounts() = default;
  ~JsonDBAccounts() override = default;

  JsonDBAccounts(const JsonDBAccounts&) = delete;
  void operator=(const JsonDBAccounts&) = delete;

  void WriteAccount(const std::string& bank_name, size_t user_id, Account* account) override;
  void WriteAccounts(const std::string& bank_name, size_t user_id, const std::vector<Account*>& accounts) override;
  void DeleteClientAccounts(const std::string& bank_name, size_t user_id) override;
  Account* GetAccount(const std::string& bank_name, size_t user_id, size_t account_id) override;
  std::vector<Account*> GetUserAccounts(const std::string& bank_name, size_t user_id) override;
};
