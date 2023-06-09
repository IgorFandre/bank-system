#pragma once

#include "../../Filesystem/Filesystem.h"
#include "../../JsonParser/json.h"
#include "../Interfaces/DataBaseClients.h"

class JsonDBClients : public DataBaseClients {
  using json = nlohmann::json;

public:
  JsonDBClients() = default;
  ~JsonDBClients() override = default;

  JsonDBClients(const JsonDBClients &) = delete;
  void operator=(const JsonDBClients &) = delete;

  void WriteClient(const std::string &bank_name, const Client &client) override;
  void WriteClients(const std::string &bank_name,
                    const std::vector<Client> &clients) override;
  void DeleteClient(const std::string &bank_name, size_t user_id) override;
  std::shared_ptr<Client> GetClient(const std::string &bank_name,
                                    size_t user_id) override;

private:
  static std::string GetClientsFileName(size_t id);
};
