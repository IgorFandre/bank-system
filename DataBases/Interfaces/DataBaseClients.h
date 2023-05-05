#pragma once

#include "../../Client/Client.h"

class DataBaseClients {
 public:
  DataBaseClients() = default;
  virtual ~DataBaseClients() = default;

  DataBaseClients(const DataBaseClients&) = delete;
  void operator=(const DataBaseClients&) = delete;

  virtual void WriteClient(const std::string& bank_name, const Client& client) = 0;
  virtual void WriteClients(const std::string& bank_name, const std::vector<Client>& clients) = 0;
  virtual void DeleteClient(const std::string& bank_name, size_t user_id) = 0;
  virtual std::shared_ptr<Client> GetClient(const std::string& bank_name, size_t user_id) = 0;

};