#pragma once

#include <fstream>

#include "../../Filesystem/Filesystem.h"
#include "../../JsonParser/json.h"
#include "../Interfaces/DataBaseWorkers.h"

class JsonDBWorkers : public DataBaseWorkers {
  using json = nlohmann::json;

public:
  JsonDBWorkers() = default;
  ~JsonDBWorkers() override = default;

  JsonDBWorkers(const JsonDBWorkers &) = delete;
  void operator=(const JsonDBWorkers &) = delete;

  void AddNewBank(const std::string &bank_name,
                  const std::string &sudo_pas) override;
  bool WriteWorker(const std::string &bank_name, const std::string &sudo_pas,
                   const Worker &worker) override;
  bool DeleteWorker(const std::string &bank_name, const std::string &sudo_pas,
                    size_t worker_id) override;
  std::shared_ptr<Worker> GetWorker(const std::string &bank_name,
                                    size_t worker_id) override;
};