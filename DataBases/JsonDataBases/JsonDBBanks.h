#pragma once

#include <filesystem>
#include <vector>

#include "../Interfaces/DataBaseBanks.h"
#include "../../Filesystem/Filesystem.h"
#include "../../JsonParser/json.h"

class JsonDBBanks : public DataBaseBanks {
  using json = nlohmann::json;
 public:
  JsonDBBanks() = default;
  ~JsonDBBanks() override = default;

  JsonDBBanks(const JsonDBBanks&) = delete;
  void operator=(const JsonDBBanks&) = delete;

  void WriteBank(const Bank& bank) override;
  bool FindBank(const std::string& bank_name) override;
  std::shared_ptr<Bank> GetBank(const std::string& bank_name) override;
  std::vector<std::shared_ptr<Bank>> GetBanks() override;

};
