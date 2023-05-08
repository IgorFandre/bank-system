#ifndef BANK_SYSTEM_DATABASES_VECTORDBBANKS_H_
#define BANK_SYSTEM_DATABASES_VECTORDBBANKS_H_


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
  Bank GetBank(const std::string& bank_name) override {
    for (auto bank : banks_) {
      if (bank.second.GetName() == bank_name) {
        return bank.second;
      }
    }
    return {bank_name};
  }
  bool FindBank(const std::string& bank_name) override {
    return banks_.contains(bank_name);
  }
  std::vector<Bank> GetBanks() override {
    std::vector<Bank> banks(banks_.size());
    for (auto bank : banks_) {
      banks.push_back(bank.second);
    }
    return banks;
  }


 private:
  std::unordered_map<std::string, Bank> banks_;
};


#endif //BANK_SYSTEM_DATABASES_VECTORDBBANKS_H_
