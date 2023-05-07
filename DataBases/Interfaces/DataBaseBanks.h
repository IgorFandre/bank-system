#pragma once

#include <iostream>
#include <vector>

#include "../../Bank/Bank.h"

class DataBaseBanks {
 public:
  DataBaseBanks() = default;
  virtual ~DataBaseBanks() = default;

  DataBaseBanks(const DataBaseBanks&) = delete;
  void operator=(const DataBaseBanks&) = delete;

  virtual void WriteBank(const Bank& bank) = 0;
  virtual bool FindBank(const std::string& bank_name) = 0;
  virtual std::shared_ptr<Bank> GetBank(const std::string& bank_name) = 0;
  virtual std::vector<std::shared_ptr<Bank>> GetBanks() = 0;

};