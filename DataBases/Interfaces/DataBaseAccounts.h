#ifndef BANK_SYSTEM_DATABASES_INTERFACES_DATABASEACCOUNTS_H_
#define BANK_SYSTEM_DATABASES_INTERFACES_DATABASEACCOUNTS_H_


#include <vector>

#include "../../Account/Account.h"

class DataBaseAccounts {

 public:

  DataBaseAccounts() = default;

  DataBaseAccounts(const DataBaseAccounts&) = delete;
  void operator=(const DataBaseAccounts&) = delete;

  virtual void WriteAccount(const std::string& bank_name, size_t user_id, Account* account) = 0;
  virtual void WriteAccounts(const std::string& bank_name, size_t user_id, const std::vector<Account*>& accounts) = 0;
  virtual void DeleteClientAccounts(const std::string& bank_name, size_t user_id) = 0;
  virtual Account* GetAccount(const std::string& bank_name, size_t user_id, size_t account_id) = 0;
  virtual const std::vector<Account*>& GetUserAccounts(const std::string& bank_name, size_t user_id) = 0;

};


#endif //BANK_SYSTEM_DATABASES_INTERFACES_DATABASEACCOUNTS_H_
