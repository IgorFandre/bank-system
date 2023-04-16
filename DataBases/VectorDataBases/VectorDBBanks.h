#pragma once

#include <unordered_map>
#include <vector>

#include "DataBaseBanks.h"

class VectorDBBanks : public DataBaseBanks {

 public:

  VectorDBBanks() : banks_() {};

  VectorDBBanks(const VectorDBBanks&) = delete;
  void operator=(const VectorDBBanks&) = delete;

  void WriteBank(const Bank& bank) override {
    banks_[bank.GetName()] = bank;
  }
  bool FindBank(const std::string& bank_name) override {
    return banks_.contains(bank_name);
  }
  Bank* GetBank(const std::string& bank_name) override {
    for (const auto& bank : banks_) {
      if (bank.second.GetName() == bank_name) {
        return new Bank(bank.second);
      }
    }
    return nullptr;
  }
  std::vector<Bank*> GetBanks() override {
    std::vector<Bank*> banks(banks_.size());
    for (const auto& bank : banks_) {
      banks.push_back(new Bank(bank.second));
    }
    return banks;
  }


 private:
  std::unordered_map<std::string, Bank> banks_;
};