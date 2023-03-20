#ifndef BANK_SYSTEM_DATABASES_INTERFACES_DATABASEBANKS_H_
#define BANK_SYSTEM_DATABASES_INTERFACES_DATABASEBANKS_H_


#include <iostream>

#include "../Bank/Bank.h"

class DataBaseBanks {

 public:

  DataBaseBanks() = default;
  virtual ~DataBaseBanks() = default;

  DataBaseBanks(const DataBaseBanks&) = delete;
  void operator=(const DataBaseBanks&) = delete;

  virtual void WriteBank(const Bank& bank) = 0;
  virtual bool FindBank(const std::string& bank_name) = 0;
  virtual Bank GetBank(const std::string& bank_name) = 0;
  virtual std::vector<Bank> GetBanks() = 0;

};


#endif //BANK_SYSTEM_DATABASES_INTERFACES_DATABASEBANKS_H_
