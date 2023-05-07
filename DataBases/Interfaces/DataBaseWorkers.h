#pragma once

#include <vector>

#include "../../Worker/Worker.h"

class DataBaseWorkers {
 public:
  DataBaseWorkers() = default;
  virtual ~DataBaseWorkers() = default;

  DataBaseWorkers(const DataBaseWorkers&) = delete;
  void operator=(const DataBaseWorkers&) = delete;

  virtual void AddNewBank(const std::string& bank_name, const std::string& sudo_pas) = 0;
  virtual bool WriteWorker(const std::string& bank_name, const std::string& sudo_pas, const Worker& worker) = 0;
  virtual bool DeleteWorker(const std::string& bank_name, const std::string& sudo_pas, size_t worker_id) = 0;
  virtual std::shared_ptr<Worker> GetWorker(const std::string& bank_name, size_t worker_id) = 0;

};