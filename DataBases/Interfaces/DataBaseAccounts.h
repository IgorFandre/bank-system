#pragma once

#include <vector>

#include "../../Account/Account.h"

class DataBaseAccounts {
public:
  DataBaseAccounts() = default;
  virtual ~DataBaseAccounts() = default;

  DataBaseAccounts(const DataBaseAccounts &) = delete;
  void operator=(const DataBaseAccounts &) = delete;

  virtual void WriteAccount(const std::string &bank_name,
                            size_t user_id,
                            std::shared_ptr<Account> account) = 0;
  virtual void
  WriteAccounts(const std::string &bank_name,
                size_t user_id,
                const std::vector<std::shared_ptr<Account>> &accounts) = 0;
  virtual void DeleteClientAccounts(const std::string &bank_name,
                                    size_t user_id) = 0;
  virtual std::shared_ptr<Account> GetAccount(const std::string &bank_name,
                                              size_t user_id,
                                              size_t account_id) = 0;
  virtual std::vector<std::shared_ptr<Account>>
  GetUserAccounts(const std::string &bank_name, size_t user_id) = 0;
};